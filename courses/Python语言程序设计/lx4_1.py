def count_name(text):
    try:
        fp=open(text,"r",encoding="UTF-8")
        text=fp.read()
        name1="黛玉"
        name2="宝玉"
        count1=text.count(name1)
        count2=text.count(name2)
        fp.close()
        print(f"林黛玉出现{count1}次，贾宝玉出现{count2}次")
        return count1,count2
    except:
        print("读取文件出现异常")
if __name__=='__main__':
    text="红楼梦.txt"
    count1,count2=count_name(text)
    print(f"林黛玉出现{count1}次，贾宝玉出现{count2}次")
