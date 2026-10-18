def func4(path):
    import matplotlib.pyplot as plt
    import pandas as pd
    a_total=0;b_total=0;c_total=0
    total_percent=[]
    a_list=[];b_list=[];c_list=[]  #读取北上广三地的客户ID
    a_dict={};b_dict={};c_dict={}  #读取北上广客户的产品ID:数量
    product_df=pd.read_excel(path,"产品信息")
    info_df=pd.read_excel(path,"客户信息")
    sales_df=pd.read_excel(path,"销售记录")
    for index, row in info_df.iterrows():
        if row["城市"]=="北京":
            a_list.append(row["客户ID"])
        elif row["城市"]=="上海":
            b_list.append(row["客户ID"])
        elif row["城市"]=="广州":
            c_list.append(row["客户ID"])
    for index, row in sales_df.iterrows():
        if row["客户ID"] in a_list:
            a_dict[row["产品ID"]]=row["数量"]
        elif row["客户ID"] in b_list:
            b_dict[row["产品ID"]]=row["数量"]
        elif row["客户ID"] in c_list:
            c_dict[row["产品ID"]]=row["数量"]
    for key,value in a_dict.items():
        a_total+=value*product_df.loc[product_df["产品ID"]==key,"售价"].iloc[0]
    for key, value in b_dict.items():
        b_total += value * product_df.loc[product_df["产品ID"] == key, "售价"].iloc[0]
    for key, value in c_dict.items():
        c_total += value * product_df.loc[product_df["产品ID"] == key, "售价"].iloc[0]
    total=a_total+b_total+c_total
    total_percent.append(a_total/total*100)
    total_percent.append(b_total/total*100)
    total_percent.append(c_total/total*100)
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.figure(figsize=(12, 6))
    colors = ["cyan", "orange", "green"]
    labels=["北京","上海","广州"]
    patches, texts, autotexts = plt.pie(total_percent, colors=colors, autopct='%1.2f%%', startangle=90,textprops={'fontsize': 14})
    plt.title("2025-7-30 三地消费总量对比",fontsize=16)
    plt.axis('equal')
    plt.legend(patches, labels, loc=0,fontsize=12)
    plt.savefig('sales.jpg', dpi=300)
    plt.show()
if __name__=="__main__":
    func4("销售数据.xlsx")


