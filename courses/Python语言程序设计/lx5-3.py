def func3(text):
    import json
    import matplotlib.pyplot as plt
    plt.rcParams['font.sans-serif']=['SimHei']
    plt.rcParams['axes.unicode_minus']=False
    fp=open(text,"r",encoding="UTF-8")
    data=json.load(fp)
    m_data=data["wether data"]
    days = range(1, len(m_data) + 1)
    low_temp=[day[0] for day in m_data]
    high_temp=[day[1] for day in m_data]
    plt.figure(figsize=(15,12))
    plt.plot(high_temp,color="r",linewidth=2,marker="*",label="最高温度")
    plt.plot(low_temp,color="b",linewidth=2,marker="D",label="最低温度")
    plt.title("温度变化折线图",fontsize=16)
    plt.xlabel("日期",fontsize=16)
    plt.ylabel("温度（℃）",fontsize=16)
    plt.legend(loc="best")
    plt.savefig("weather.jpg")
    plt.show()
if __name__=="__main__":
    func3("json_sh_wether.txt")