from jieba.analyse import extract_tags
def count_func(text):
    try:
        fp=open(text,"r",encoding="UTF-8")
        text_content=fp.read()
        keywords = extract_tags(text_content, topK=10, withWeight=False, allowPOS=('n','v','a'))
        print("使用 extract_tags 提取的10个关键词：", keywords)
        word_dict={}
        for word in keywords:
            num=text_content.count(word)
            word_dict[word]=num
        sorted_items = sorted(word_dict.items(), key=lambda x: x[1], reverse=True)
        print("这10个关键词中出现频率最高的3个：")
        for item in sorted_items[:3]:
            print(f"{item[0]}:{item[1]}")
        fp.close()
    except:
        print("读取文件失败")

if __name__ == "__main__":
    count_func("tj.txt")
