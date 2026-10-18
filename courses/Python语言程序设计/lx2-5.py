m_dict=dict(zip([str(i) for i in range(10)],["zero","one","two","three","four","five","six","seven","eight","nine"]))
m_num=input("请输入您的电话号码：")
m_str=""
for i in m_num:
    m_str+=(m_dict[i]+"-")
print(m_str.strip("-"))

