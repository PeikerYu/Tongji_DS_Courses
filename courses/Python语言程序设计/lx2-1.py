n = 64
def my_chr():
    global n
    n += 1
    if n == 91:
        n = 65
    return (chr(n))

line = int(input("请输入三角形行数："))
for i in range(line):
    print(" " * (line - 1 - i), end="")
    for j in range(2 * i + 1):
        print(my_chr(), end="")
    print()
