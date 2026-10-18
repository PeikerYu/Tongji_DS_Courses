def func1(text):
    import pandas as pd
    from matplotlib import pyplot as plt
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.rcParams['axes.unicode_minus'] = False
    score_df=pd.read_excel(text,"score")
    info_df=pd.read_excel(text,"info")
    f_list=[]
    m_list=[]
    for index,row in info_df.iterrows():
        if row["性别"]=="女":
            f_list.append(row["学号"])
        elif row["性别"]=="男":
            m_list.append(row["学号"])
    f_score=m_score=0
    for index,row in score_df.iterrows():
        if row["学号"] in f_list:
            f_score+=row["高数"]
        elif row["学号"] in m_list:
            m_score += row["高数"]
    f_ave=f_score/len(f_list)
    m_ave=m_score/len(m_list)
    plt.figure(figsize=(15, 12), dpi=100)
    plt.bar(["女生","男生"],[f_ave,m_ave],color=["red","blue"])
    plt.title("高数男女生平均分对比柱状图",fontsize=16)
    plt.xlabel("性别", fontsize=16)
    plt.ylabel("平均分",fontsize=16)
    plt.tick_params(axis='both', labelsize=14)
    plt.savefig("2451951.jpg")
    plt.ylim(min(f_ave, m_ave) * 0.95, max(f_ave, m_ave) * 1.05)
    plt.text(0, f_ave, f'{f_ave:.2f}', ha='center', va='bottom',fontsize=16)
    plt.text(1, m_ave, f'{m_ave:.2f}', ha='center', va='bottom',fontsize=16)
    plt.show()
if __name__=="__main__":
    func1("st_data.xlsx")


