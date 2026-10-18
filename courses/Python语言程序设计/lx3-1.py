prime_list=[x for x in range(2,1000) if 0 not in [x%y for y in range(2,x)]]

while True:
    num=int(input("请输入一个1000内的偶数："))
    if num>1000 or num%2!=0:
        print("无效输入")
        continue
    else:
        break

for x in prime_list:
    y=num-x
    if x>y:
        break
    if y in prime_list:
        print(f"{x}+{y}={num}")
