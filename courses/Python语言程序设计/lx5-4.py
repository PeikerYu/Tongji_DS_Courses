def func4():
    import math
    import matplotlib.pyplot as plt
    W0=H0=200
    plt.rcParams['font.sans-serif']=['SimHei']
    plt.rcParams['axes.unicode_minus']=False
    plt.figure(figsize=(15, 12), dpi=100)
    plt.title("参数方程曲线",fontsize=16)
    t=0
    x=[];y=[]
    while t<=2*math.pi:
        x.append(2/3*W0*(math.cos(t)**3+math.sin(t)))
        y.append(2/3*H0*(math.sin(t)**3+math.cos(t)))
        t+=0.01
    plt.plot(x,y,"k.",linewidth=2,label="参数曲线")
    plt.xlabel("x坐标",fontsize=16)
    plt.ylabel("y坐标",fontsize=16)
    plt.legend(loc="best")
    plt.savefig("curve.jpg")
    plt.show()
if __name__=="__main__":
    func4()