def func3(path1,path2):
    from matplotlib import pyplot as plt
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.rcParams['axes.unicode_minus'] = False
    fp=open(path1,"r",encoding="ANSI")
    name_list=fp.read().strip().split(" ")
    fp.close()
    fp=open(path2,"r",encoding="ANSI")
    text = fp.read()
    fp.close()
    freq_list=[]
    for i in name_list:
        count=text.count(i)
        freq_list.append(count)
    plt.figure(figsize=(20, 15), dpi=100)
    plt.bar(name_list,freq_list,color="cyan")
    plt.title("三国人名出现次数统计图",fontsize=16)
    plt.xlabel("人名", fontsize=16)
    plt.xticks(rotation=45)
    plt.ylabel("次数",fontsize=16)
    for i in range(len(name_list)):
        if freq_list[i]>100:
            plt.text(i, freq_list[i], f'{freq_list[i]}', ha='center', va='bottom', fontsize=10)
    plt.savefig("sg.jpg",bbox_inches='tight')
    plt.show()

if __name__=="__main__":
    func3("三国人名汇总.txt","三国演义.txt")