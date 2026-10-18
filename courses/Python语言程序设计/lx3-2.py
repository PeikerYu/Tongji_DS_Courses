def f(x):
    return 2*x*x*x-4*x*x+3*x-6
x1,x2,x3=-10,10,0
count=0
while abs(x1-x2)>1e-6 and count<100:
    if f(x3)==0:
        break
    x3=(x1+x2)/2
    if f(x1)*f(x3)<0:
        x2=x3
    elif f(x2)*f(x3)<0:
        x1=x3
    else:
        break
    print(f"第{count}次求解为{x3:.15f}")
    count+=1
print(f"解为{x3:.10f}，满足精度")
