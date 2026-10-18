# 2451951 大数据 于沛可
# 决策树 ID3 算法（Car Evaluation 数据集 ）

import math
import csv
from collections import Counter
import random
import matplotlib.pyplot as plt
from matplotlib import rcParams
from graphviz import Digraph

rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体
rcParams['axes.unicode_minus'] = False    # 解决负号显示问题

# 读取 CSV 文件
def load_data(filename):
    data = []
    headers = ['buying','maint','doors','persons','lug_boot','safety','class']
    with open(filename, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        for row in reader:
            data.append(row)
    return headers, data

# 计算信息熵
def calc_entropy(data):

    total = len(data)
    if total == 0:
        return 0 # 空数据集的熵为 0
    
    # 统计类别标签（数据集的最后一列）的出现次数
    label_count = Counter(row[-1] for row in data)
    entropy = 0
    # 遍历每个类别及其对应的计数
    for count in label_count.values():
        p = count / total # 计算当前类别的概率 p_i
        entropy -= p * math.log2(p) # 根据信息熵公式累加
    return entropy

# 按特征划分数据
def split_data(data, index, value):
    new_data = []
    for row in data:
        if row[index] == value:
            reduced = row[:index] + row[index+1:]
            new_data.append(reduced)
    return new_data

# 计算信息增益
def calc_info_gain(data, index):
    # 计算划分前的基准熵 H(S)
    base_entropy = calc_entropy(data)
    total = len(data)
    # 获取该特征的所有唯一取值 
    unique_values = set(row[index] for row in data)
    new_entropy = 0
    # 遍历该特征的每个取值，计算划分后的加权平均熵
    for value in unique_values:
        # 1. 划分数据：根据取值 value 得到子数据集 S_v
        sub_data = split_data(data, index, value)
        # 2. 计算权重：子数据集的比例 P(|S_v|/|S|)
        p = len(sub_data) / total
        # 3. 累加加权熵：Σ P(|S_v|/|S|) * H(S_v)
        new_entropy += p * calc_entropy(sub_data)
    # 信息增益 Gain(S, A) = H(S) - H_new
    return base_entropy - new_entropy

# 选择最佳特征
def choose_best_feature(data):
    # 如果只剩类别标签一列，则特征用尽
    if len(data[0]) == 1:
        return -1
    best_gain = 0
    best_index = -1
    # 遍历所有特征（除了最后一列的类别标签）
    for i in range(len(data[0])-1):
        gain = calc_info_gain(data, i) # 计算当前特征的信息增益
        # 寻找信息增益最大的特征
        if gain > best_gain:
            best_gain = gain
            best_index = i
    return best_index

# 多数类别
def majority_label(data):
    labels = [row[-1] for row in data]
    return Counter(labels).most_common(1)[0][0]

# 创建决策树
def create_tree(data, labels):

    class_list = [row[-1] for row in data]

    # 终止条件 1：纯度终止
    # 如果所有样本的类别相同，则返回该类别作为叶节点
    if class_list.count(class_list[0]) == len(class_list):
        return class_list[0]
    
    # 终止条件 2：特征用尽终止
    # 如果数据集只剩下一列（即只剩类别标签），则返回多数类别作为叶节点
    if len(data[0]) == 1:
        return majority_label(data)
    
    # 递归划分：选择最佳特征
    best_feature = choose_best_feature(data)
    best_label = labels[best_feature]
    # 创建树节点，节点名为最佳特征名
    tree = {best_label: {}}

    # 下一层递归
    feature_values = set(row[best_feature] for row in data)
    
    # 遍历最佳特征的每个取值，创建分支
    for value in feature_values:
        # 1. 准备子特征名列表：移除当前已用特征
        sub_labels = labels[:]
        sub_labels.pop(best_feature)
        
        # 2. 准备子数据集：根据取值 value 划分数据
        sub_data = split_data(data, best_feature, value)
        
        # 3. 递归调用：对子数据集和子特征名列表继续建树
        tree[best_label][value] = create_tree(sub_data, sub_labels)

    return tree
    

# 用树预测
def classify(tree, labels, test):
    first_key = list(tree.keys())[0]
    second_dict = tree[first_key]
    index = labels.index(first_key)
    value = test[index]
    if value in second_dict:
        if isinstance(second_dict[value], dict):
            return classify(second_dict[value], labels, test)
        else:
            return second_dict[value]
    else:
        # 未见过的取值返回当前子树多数类别
        all_labels = []
        def collect_labels(t):
            if isinstance(t, dict):
                for v in t.values():
                    collect_labels(v)
            else:
                all_labels.append(t)
        collect_labels(tree)
        return Counter(all_labels).most_common(1)[0][0]

# 计算准确率
def calc_accuracy(tree, labels, dataset):
    correct = 0
    for row in dataset:
        pred = classify(tree, labels, row[:-1])
        if pred == row[-1]:
            correct += 1
    return correct / len(dataset)

# k折交叉验证
def cross_validation(data, labels, k=5):
    random.shuffle(data)
    fold_size = len(data) // k
    accuracies = []
    for i in range(k):
        test_fold = data[i*fold_size : (i+1)*fold_size]
        train_fold = data[:i*fold_size] + data[(i+1)*fold_size:]
        tree = create_tree(train_fold, labels[:])
        acc = calc_accuracy(tree, labels, test_fold)
        print(f"折 {i+1} 准确率: {acc:.4f}")
        accuracies.append(acc)
    avg_acc = sum(accuracies)/k
    print(f"平均交叉验证准确率: {avg_acc:.4f}")
    return accuracies


# 主函数
if __name__ == "__main__":
    file_path = r"C:\Users\Peiker\Desktop\大数据导论课\决策树ID3_2451951_于沛可\car_evaluation.csv"
    headers, data = load_data(file_path)
    print("数据条数：", len(data))

    labels = headers[:-1]

    # 训练/测试集划分
    random.shuffle(data)
    train_size = int(len(data)*0.8)
    train_data = data[:train_size]
    test_data = data[train_size:]
    print(f"训练集大小: {len(train_data)}, 测试集大小: {len(test_data)}")

    # 建树
    print("开始构建决策树...")
    tree = create_tree(train_data, labels[:])

    # 训练和测试集准确率
    train_acc = calc_accuracy(tree, labels, train_data)
    test_acc = calc_accuracy(tree, labels, test_data)
    print(f"\n训练集准确率: {train_acc:.4f}")
    print(f"测试集准确率: {test_acc:.4f}")

    # 5折交叉验证
    print("\n开始5折交叉验证...")
    cv_acc = cross_validation(data, labels, k=5)

    # 可视化折线
    plt.figure(figsize=(6,4))
    plt.plot(range(1,6), cv_acc, marker='o', label='每折准确率')
    plt.axhline(y=sum(cv_acc)/5, color='r', linestyle='--', label='平均准确率')
    plt.title("ID3 决策树 5折交叉验证准确率")
    plt.xlabel("折数")
    plt.ylabel("准确率")
    plt.ylim(0,1)
    plt.grid(True)
    plt.legend()
    plt.show()
