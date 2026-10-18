s = input("请输入一个字符串：")
print("*" * 50)
print("*" + " " * 48 + "*")
print("*" + " " * 48 + "*")
s_len = 0
for char in s:
    if ord(char) >= 0x4E00 and ord(char) <= 0x9FFF:
        s_len += 2
    else:
        s_len += 1
left = (48 - s_len) // 2
right = 48 - left - s_len
print("*" + " " * left + s + " " * right + "*")
print("*" + " " * 48 + "*")
print("*" + " " * 48 + "*")
print("*" * 50)
