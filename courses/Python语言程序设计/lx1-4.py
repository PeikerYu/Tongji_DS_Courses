num = input("请输入一个四位数：")
while num != "6174":
    small_list = sorted(num)
    big_list = sorted(num, reverse=True)
    small_str = "".join(small_list)
    big_str = "".join(big_list)
    small = int(small_str)
    big = int(big_str)
    num = big - small
    print(f"{big}-{small:04d}={num:04d}")
    num = f"{num:04d}"
