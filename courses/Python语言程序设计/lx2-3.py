import math
a=int(input("请输入第一个系数："))
b=int(input("请输入第二个系数："))
c=int(input("请输入第三个系数："))
if b**2-4*a*c>0:
    x1=(-b+math.sqrt(b**2-4*a*c))/2/a
    x2=(-b-math.sqrt(b**2-4*a*c))/2/a
    print(f"方程{a}*x^2+{b}*x+{c}=0的解为{x1:.4f}和{x2:.4f}")
elif b**2-4*a*c==0:
    x=(-b+math.sqrt(b**2-4*a*c))/2/a
    print(f"方程{a}*x^2+{b}*x+{c}=0的二重解为{x:.4f}")
else:
    print(f"方程{a}*x^2+{b}*x+{c}=0无实根")
