s=input("请输入一个英文句子：")
m_s=[c.upper() for c in s if c.isalpha()]
num_list=[0 for x in range(26)]
for i in m_s:
    num_list[ord(i)-65]+=1
alp_list=[chr(x) for x in range(65,91)]
final_list=zip(alp_list,num_list)
print("每个字母出现频次：")
for key,value in dict(final_list).items():
    if value>0:
        print(f"{key}:{value}")