def func1(x):
    id = str(2451951)
    length = len(id)
    res = []
    current_index=0
    if x>100 or x<1:
        print("非法输入")
    elif 1<=x<=100:
        for i in range(1,x+1):
            line=(" "*(x-i))
            for j in range(2*i-1):
                line+=id[(current_index)%length]
                current_index+=1
            res.append(line)
        for i in range(x-1,0,-1):
            line=(" "*(x-i))
            for j in range(2*i-1):
                line+=id[(current_index)%length]
                current_index+=1
            res.append(line)
        return "\n".join(res)
if __name__=="__main__":
    try:
        print(func1(input("请输入一个1至100的数字：")))
    except:
        print("非法输入")
