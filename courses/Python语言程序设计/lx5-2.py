def func2(text):
    import pandas as pd
    import matplotlib.pyplot as plt
    plt.rcParams['font.sans-serif'] = ['SimHei']
    score_df=pd.read_excel(text,"score")
    c_list=[0,0,0,0,0]
    for index, row in score_df.iterrows():
        if row["C语言"]<60:
            c_list[4]+=1
        elif 60<=row["C语言"]<70:
            c_list[3]+=1
        elif 70<=row["C语言"]<80:
            c_list[2]+=1
        elif 80<= row["C语言"]<90:
            c_list[1]+=1
        else:
            c_list[0]+=1
    p_list=[0,0,0,0,0]
    for index, row in score_df.iterrows():
        if row["Python"]<60:
            p_list[4]+=1
        elif 60<=row["Python"]<70:
            p_list[3]+=1
        elif 70<=row["Python"]<80:
            p_list[2]+=1
        elif 80<= row["Python"]<90:
            p_list[1]+=1
        else:
            p_list[0]+=1
    c_percent=[x/sum(c_list)*100 for x in c_list]
    p_percent=[x/sum(p_list)*100 for x in p_list]
    labels = ['优秀', '良好', '中等', '及格', '不及格']
    colors = ['#ff9999', '#66b3ff', '#99ff99', '#ffcc99', '#c2c2f0']
    explode=(0.2,0,0,0,0)
    plt.figure(figsize=(12, 6))
    plt.subplot(1, 2, 1)
    patches, texts, autotexts = plt.pie(c_percent, explode=explode,colors=colors, autopct='%1.1f%%', startangle=90)
    plt.title('C语言成绩分布图')
    plt.legend(patches, labels, loc='lower left')
    plt.subplot(1, 2, 2)
    patches, texts, autotexts = plt.pie(p_percent, explode=explode,colors=colors, autopct='%1.1f%%', startangle=90)
    plt.title('Python成绩分布图')
    plt.legend(patches, labels, loc='lower left')
    plt.tight_layout()
    plt.savefig('pie_2451951.jpg', dpi=300)
    plt.show()
if __name__=="__main__":
    func2("st_data.xlsx")
