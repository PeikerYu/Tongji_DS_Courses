# 功能: ID3 决策树算法，带预剪枝和扩大网格搜索调优，用于寻找最高交叉验证准确率

import math
import csv
from collections import Counter
import random
import matplotlib.pyplot as plt
from matplotlib import rcParams
import time
import itertools # 用于生成网格搜索的参数组合

# 全局配置：解决 Matplotlib 中文显示和负号问题
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False

# 1. 数据处理函数

# 读取 CSV 文件，加载数据集
def load_data(filename):
    """从 CSV 文件中读取数据，Car Evaluation 特征名已预设。"""
    data = []
    headers = ['buying','maint','doors','persons','lug_boot','safety','class']
    try:
        # 使用用户提供的绝对路径
        with open(filename, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            for row in reader:
                data.append(row)
    except FileNotFoundError:
        print(f"错误：文件路径未找到或不正确: {filename}")
        return headers, []
    
    return headers, data

# 2. 核心算法：信息论计算及特征选择

# 计算信息熵 (Entropy)
def calc_entropy(data):
    """计算数据集的信息熵。"""
    total = len(data)
    if total == 0:
        return 0 
    
    label_count = Counter(row[-1] for row in data)
    entropy = 0
    for count in label_count.values():
        p = count / total 
        # 防止 log2(0) 错误，尽管 p 理论上不会是 0，但在浮点计算中是 good practice
        if p > 0:
            entropy -= p * math.log2(p)
        
    return entropy

# 按特征划分数据
def split_data(data, index, value):
    """根据指定特征的特定取值，划分数据集并移除该特征列。"""
    new_data = []
    for row in data:
        if row[index] == value:
            # 移除已用于划分的特征列，保留剩余特征和类别标签
            reduced = row[:index] + row[index+1:]
            new_data.append(reduced)
    return new_data

# 计算信息增益 (Information Gain)
def calc_info_gain(data, index):
    """计算指定特征的信息增益。"""
    base_entropy = calc_entropy(data)
    total = len(data)
    
    unique_values = set(row[index] for row in data)
    new_entropy = 0
    
    for value in unique_values:
        sub_data = split_data(data, index, value)
        p = len(sub_data) / total
        new_entropy += p * calc_entropy(sub_data)
        
    return base_entropy - new_entropy

# 多数类别 (用于叶节点决策)
def majority_label(data):
    """返回数据集中出现次数最多的类别标签（众数）。"""
    labels = [row[-1] for row in data]
    return Counter(labels).most_common(1)[0][0]

# 选择最佳特征（同时返回最佳增益值）
def choose_best_feature(data):
    """选择信息增益最大的特征。输出：best_index (int), best_gain (float)"""
    if len(data[0]) == 1:
        return -1, 0.0
        
    best_gain = 0.0
    best_index = -1
    
    # 遍历所有特征列（除了最后一列的类别标签）
    for i in range(len(data[0])-1):
        gain = calc_info_gain(data, i)
        
        if gain > best_gain:
            best_gain = gain
            best_index = i
            
    return best_index, best_gain

# 3. 决策树构建函数（核心：预剪枝版）

def create_tree(data, labels, max_depth=None, min_samples_split=2, min_gain=0.0, current_depth=0):
    """递归地构建决策树模型，加入了预剪枝参数。"""
    class_list = [row[-1] for row in data]

    # 1. 纯度终止
    if class_list.count(class_list[0]) == len(class_list):
        return class_list[0]

    # 预剪枝条件 1：最小样本数终止
    if len(data) < min_samples_split:
        return majority_label(data)

    # 预剪枝条件 2：最大深度终止
    if max_depth is not None and current_depth >= max_depth:
        return majority_label(data)
        
    # 3. 特征用尽终止
    if len(data[0]) == 1:
        return majority_label(data)

    # 选择最佳特征，并接收最佳增益值
    best_feature, best_gain = choose_best_feature(data) 
    
    # 预剪枝条件 3：最小信息增益终止
    if best_gain < min_gain:
        return majority_label(data)

    best_label = labels[best_feature]
    tree = {best_label: {}}

    feature_values = set(row[best_feature] for row in data)
    for value in feature_values:
        sub_labels = labels[:]
        sub_labels.pop(best_feature)
        sub_data = split_data(data, best_feature, value)
        
        # 递归调用：深度 + 1，并传递所有剪枝参数
        tree[best_label][value] = create_tree(
            sub_data, sub_labels, 
            max_depth=max_depth, 
            min_samples_split=min_samples_split, 
            min_gain=min_gain,
            current_depth=current_depth + 1
        )

    return tree

# 4. 预测与评估函数

# 使用树进行分类预测
def classify(tree, labels, test):
    """给定一个样本，利用决策树进行预测。"""
    if not isinstance(tree, dict):
        return tree
        
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
        # 处理未见过的取值：返回当前子树的多数类别
        all_labels = []
        def collect_labels(t):
            if isinstance(t, dict):
                for v in t.values():
                    collect_labels(v)
            else:
                all_labels.append(t)
        collect_labels(tree)
        # 稳健性返回
        return Counter(all_labels).most_common(1)[0][0] if all_labels else 'unacc'

# 计算准确率
def calc_accuracy(tree, labels, dataset):
    """计算模型在给定数据集上的准确率。"""
    correct = 0
    if not dataset:
        return 0.0
        
    for row in dataset:
        pred = classify(tree, labels, row[:-1])
        if pred == row[-1]:
            correct += 1
            
    return correct / len(dataset)

# k折交叉验证（网格搜索专用版：只返回平均准确率）
def cross_validation(data, labels, k=5, max_depth=None, min_samples_split=2, min_gain=0.0):
    """执行 K 折交叉验证，返回平均准确率，用于参数调优。"""
    # 确保每次调用时数据都被随机打乱以保证折叠的随机性
    temp_data = data[:]
    random.shuffle(temp_data)
    fold_size = len(temp_data) // k 
    accuracies = []
    
    for i in range(k):
        test_fold = temp_data[i*fold_size : (i+1)*fold_size]
        train_fold = temp_data[:i*fold_size] + temp_data[(i+1)*fold_size:]
        
        # 训练时传入剪枝参数
        tree = create_tree(
            train_fold, labels[:], 
            max_depth=max_depth, 
            min_samples_split=min_samples_split, 
            min_gain=min_gain
        )
        acc = calc_accuracy(tree, labels, test_fold)
        accuracies.append(acc)
        
    avg_acc = sum(accuracies)/k
    return avg_acc

# 5. 主程序执行：扩大网格搜索调优
if __name__ == "__main__":
    file_path = r"C:\Users\Peiker\Desktop\大数据导论课\决策树ID3_2451951_于沛可\car_evaluation.csv" 
    
    headers, data = load_data(file_path)
    if not data:
         print("数据加载失败，程序退出。")
         exit()
         
    labels = headers[:-1]
    print(f"数据条数: {len(data)}")

    
    # 树的最大深度：None 代表无限制
    depth_values = [None, 10, 15, 20, 30] 
    
    # 最小样本分裂数
    samples_values = [2, 5, 10, 20] 
    
    # 最小信息增益阈值
    gain_values = [0.0001, 0.001, 0.005, 0.01] 

    # 生成所有参数组合
    param_combinations = list(itertools.product(depth_values, samples_values, gain_values))

    best_acc = 0.0
    best_params = {}
    
    total_searches = len(param_combinations)
    current_run = 0
    start_time = time.time()

    print(f"\n开始【扩大】网格搜索调优。总运行次数: {total_searches}...")

    # 网格搜索循环
    for d, s, g in param_combinations:
        current_run += 1
        
        depth_str = '无限制' if d is None else str(d)
        
        print(f"\n--- 运行 {current_run}/{total_searches} ---")
        print(f"参数组合: MaxDepth={depth_str}, MinSamples={s}, MinGain={g}")
        
        # 执行 5 折交叉验证，获取平均准确率
        avg_acc = cross_validation(
            data, labels, k=5,
            max_depth=d, 
            min_samples_split=s, 
            min_gain=g
        )
        print(f"平均交叉验证准确率: {avg_acc:.4f}")
        
        # 更新最佳结果
        if avg_acc > best_acc:
            best_acc = avg_acc
            best_params = {'max_depth': d, 'min_samples_split': s, 'min_gain': g}

    end_time = time.time()
    
    
    print("网格搜索调优完成！")
    print(f"总耗时: {end_time - start_time:.2f} 秒")
    print(f"找到的最佳平均交叉验证准确率: {best_acc:.4f}")
    print("最佳参数组合:")
    best_params_display = {k: ('无限制' if v is None else v) for k, v in best_params.items()}
    print(best_params_display)
