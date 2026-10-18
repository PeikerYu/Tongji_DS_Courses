import requests
import re
# 调用requests拿到页面源代码
# 通过re提取有效信息
import time
from html import unescape # 导入这个库来处理HTML实体
import pandas as pd
base_url = "https://see.tongji.edu.cn/info/1143/"
start_url = "https://see.tongji.edu.cn/info/1143/14085.htm"
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36'
}
# 使用一个集合来存储已经访问过的URL，防止重复爬取
crawled_urls = set()
# 使用一个列表作为待爬取的队列
urls_to_crawl = [start_url]
# 用于存储所有文章数据的列表
all_articles = []
while urls_to_crawl:
    current_url = urls_to_crawl.pop(0)
    # 如果这个URL已经爬取过，就跳过
    if current_url in crawled_urls:
        continue
    print(f"正在抓取页面: {current_url}")
    crawled_urls.add(current_url)
    time.sleep(0.5)
    try:
        resp = requests.get(current_url, headers=headers, timeout=10)
        resp.encoding = "UTF-8"
        if resp.status_code != 200:
            print(f"请求失败，状态码: {resp.status_code}")
            continue
    except requests.exceptions.RequestException as e:
        print(f"请求失败: {e}")
        continue
    # 同时提取“上一条”和“下一条”链接
    obj = re.compile(r'<div class="title">.*?<h3>(?P<title>.*?)</h3>.*?'
                     r'<em>编辑：(?P<edit>.*?)</em>.*?'
                     r'<em>发表时间：(?P<time>.*?) </em>.*?'
                     r'<em>浏览次数：<script>_showDynClicks\("(?P<param1>.*?)", (?P<param2>\d+), (?P<id>\d+)\)</script></em></div>.*?</div>.*?'
                     r'<div id="vsb_content" class="single-content"><div class="v_news_content">(?P<content>.*?)</div></div>.*?'
                     r'<p align="right" style="margin-top:15px;">.*?上一条：<a href="(?P<former_page>.*?)">.*?</a>.*?下一条：<a href="(?P<next_page>.*?)">.*?</a>.*?<p.*?>',
                     re.S)
    res = obj.finditer(resp.text)
    if_found = False
    for it in res:
        if_found = True
        param1 = it.group("param1")
        param2 = it.group("param2")
        article_id = it.group("id")
        click_url = "https://see.tongji.edu.cn/system/resource/code/news/click/dynclicks.jsp"
        params = {'clickid': article_id, 'owner': param2, 'clicktype': param1} # 处理提取浏览次数动态的问题
        try:
            click_resp = requests.get(click_url, params=params, headers={'User-Agent': headers['User-Agent'], 'Referer': current_url}, timeout=5)
            clicks = click_resp.text.strip() if click_resp.status_code == 200 else f"请求失败，状态码: {click_resp.status_code}"
        except requests.exceptions.RequestException as e:
            clicks = f"获取失败: {e}"
        print(f"标题: {it.group('title')}")
        print(f"编辑: {it.group('edit')}")
        print(f"发表时间: {it.group('time')}")
        print(f"浏览次数: {clicks}")
        print("----------------------------------------")
        print("文章内容:")
        # 清洗爬取出的文章内容
        raw_content = it.group("content")
        clean_content = unescape(raw_content)
        clean_content = re.sub(r'<[^>]+>', '', clean_content)
        clean_content = re.sub(r'[\n\s]+', '\n', clean_content)
        clean_content = '\n'.join([line.strip() for line in clean_content.split('\n')])
        clean_content = clean_content.strip()
        print(clean_content+"\n")
        # 将所有信息保存到字典中
        article_info = {
            "标题": it.group("title").strip(),
            "编辑": it.group("edit").strip(),
            "发表时间": it.group("time").strip(),
            "浏览次数": clicks,
            "正文": clean_content
        }
        all_articles.append(article_info)
        # 将“上一条”和“下一条”链接加入待爬取队列
        former_page = it.group("former_page")
        if former_page and former_page != "javascript:void(0);" and (base_url + former_page) not in crawled_urls:
            urls_to_crawl.append(base_url + former_page)
        next_page = it.group("next_page")
        if next_page and next_page != "javascript:void(0);" and (base_url + next_page) not in crawled_urls:
            urls_to_crawl.append(base_url + next_page)
    # 增加一个检查，如果正则没有匹配到任何内容，说明页面结构可能发生了变化
    if not if_found:
        print(f"在页面 {current_url} 中未找到匹配内容，可能已到达终点或页面结构有变。")
print("所有相关文章已爬取完毕。")
# 将数据保存到Excel文件
df = pd.DataFrame(all_articles)
df.to_excel("tjnews.xlsx", index=False)
print("数据已成功保存到 tjnews.xlsx 文件中。")
