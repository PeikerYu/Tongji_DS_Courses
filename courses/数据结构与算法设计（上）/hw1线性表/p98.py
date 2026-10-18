import numpy as np
import pandas as pd

class cards: # 扑克牌栈类
    types = ['Spade', 'Heart', 'Club', 'Diamond']
    numbers = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
    data = pd.DataFrame({'type':[],'number':[]})
    def __init__(self):
        pass
    
    def Append(self, type_, number_) : #插入一张牌
        new_data = pd.DataFrame({'type':[type_],'number':[number_]},index=[0])
        # 修复点 1：使用 pd.concat() 替代 append()
        # 注意：要实现“栈”的插入效果（新元素在顶/前面），new_data 必须放在列表的第一位
        self.data = pd.concat([new_data, self.data], ignore_index=True)
        
    def Extract(self, type_) : # 抽取一类牌
        t = self.data.loc[self.data['type'] == type_]
        if t.shape[0] == 0 :
            return
        self.data = self.data.drop(t.index)
        t = t.sort_values(by='number', ascending=False)
        # 修复点 2：使用 pd.concat() 替代 append()
        # 这里是将抽取出来的牌 (t) 放到牌堆底部，所以 t 放在后面
        self.data = pd.concat([self.data, t], ignore_index = True)
    
    def Revert(self) : # 反转牌堆
        self.data = self.data.iloc[::-1]
        self.data.reset_index(drop=True, inplace=True)
        
    def Pop(self) : # 弹出排队顶的牌
        if self.data.shape[0] == 0 : # 没有则跳过
            return
        # 牌堆的“顶”是第 0 行，但因为你的 Append 是把新牌插入到前面，所以 Pop 应该弹出最后一张（栈底）
        # 但从你的代码逻辑来看，Append 插入到前面，Pop 弹出最后一张，这个行为是反直觉的。
        # 你的 Pop 逻辑：self.data.tail(1).index 弹出最后一行
        # 保持你的原有逻辑：弹出最后一行
        self.data = self.data.drop(self.data.tail(1).index)
    
    def Top(self) : # 查找牌堆顶的牌
        # 牌堆的“顶”在你现在的实现中是最后一行（栈顶），保持原有逻辑
        return self.data.tail(1)
    
    # def Display(self) :
    #     print(self.data) # 展示牌堆

n = 10 # 测试点个数
for i in range(1, n + 1) :
    input_file = 'input' + str(i) + '.txt'
    output_file = 'output' + str(i) + '.txt'
    
    if i <= n * 0.2 :
        E = False # 是否有Extract操作
        R = False # 是否有Revert操作
        num = 20    # 测试指令数
    elif i <= n * 0.4 :
        E = False
        R = True
        num = 50
    else :
        E = True
        R = True
        num = 200

    test_data = str(num) + '\n'
    ans_data = ''
    c = cards()
    for j in range(0, num) :
        type_ = np.random.randint(0, 4) # 生成类型
        number_ =np.random.randint(0, 13) # 生成点数
        if E == True and np.random.uniform(0, 1) <= min(j / num, 0.15) : # 生成Extract操作
            test_data += 'Extract ' + c.types[type_] + '\n'
            c.Extract(c.types[type_]) # 注意：Extract 方法接收的是 type_ 字符串，不是数字索引
        elif R == True and np.random.uniform(0, 1) <= min(j / num, 0.15) : # 生成Revert操作
            test_data += 'Revert' + '\n'
            c.Revert()
        elif np.random.uniform(0, 1) <= max(min(1 - j / num, 0.4),0.2) : # 生成pop操作
            test_data += 'Pop' + '\n'
            # 你的 Pop 逻辑是从“栈底”弹出，所以 Top 也是“栈底”
            if c.data.shape[0] == 0 :
                ans_data += 'NULL\n' 
            else :
                # Top() 返回的是 DataFrame，需要取值
                top_card = c.Top().iloc[0]
                ans_data += c.types[int(top_card['type'])] + ' ' + c.numbers[int(top_card['number'])] + '\n'
            c.Pop()
        else : # 生成Append操作
            test_data += 'Append ' + c.types[type_] + ' ' + c.numbers[number_] + '\n'
            c.Append(type_, number_) # Append 接收的是数字索引，这里保持不变
    
    if c.data.shape[0] == 0 :
        ans_data += 'NULL\n'
    else :
        # 你的输出是倒序打印（从栈顶到栈底），所以要从第 0 行打印到最后一行（如果用 append 插入到前面）
        for j in range(0, c.data.shape[0]) :
            ans_data += c.types[int(c.data.values[j][0])] + ' ' + c.numbers[int(c.data.values[j][1])] + '\n'
    
    with open(input_file, 'w') as fin :
        fin.write(test_data)
    with open(output_file, 'w') as fout:
        fout.write(ans_data)