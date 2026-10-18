def gdp_func(text):
    try:
        year_list=[]
        gdp_list=[]
        rate_list=[]
        fp=open(text,"r",encoding="ANSI")
        for line in fp.readlines():
            line=line.replace(" ","")
            line_list=line.split("年")
            year_list.append(int(line_list[0]))
            gdp_list.append(int(line_list[1]))
        for i in range(1,len(year_list)):
            rate=(gdp_list[i]-gdp_list[i-1])/gdp_list[i-1]*100
            print(f"{year_list[i]}年的GDP增长率：{rate:.2f}%")
        fp.close()
    except:
        print("文件读取失败")
if __name__=="__main__":
    text="GDP.txt"
    gdp_func(text)