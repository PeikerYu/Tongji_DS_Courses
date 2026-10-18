M=int(input("请输入总头数："))
N=int(input("请输入总脚数："))
if N%2!=0:
    print("总脚数必须为偶数！")
else:
    y=N/2-M
    x=M-y
    if x<0:
        print("输入数据有误，导致解不合理，鸡的头数为负")
    elif y<0:
        print("输入数据有误，导致解不合理，兔的头数为负")
    else:
        print(f"鸡有{int(x)}只，兔有{int(y)}只")


