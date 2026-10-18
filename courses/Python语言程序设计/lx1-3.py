def func(num):
    a = num // 100
    b = (num % 100) // 10
    c = num % 10
    return (a, b, c)


num = 101
while num < 1000:
    a, b, c = func(num)
    if a ** 3 + b ** 3 + c ** 3 == num:
        print(num)
    num += 1
