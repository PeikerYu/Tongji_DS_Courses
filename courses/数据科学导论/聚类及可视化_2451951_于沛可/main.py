import os
import argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

import kagglehub
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.metrics import silhouette_score

"""
使用 kagglehub 下载 ccdata 数据集并返回数据文件路径
"""
# 1. 数据下载与读取
def download_ccdata() -> str:
    
    dataset_dir = kagglehub.dataset_download("arjunbhasin2013/ccdata")

    # 数据集中一般包含 CC GENERAL.csv（注意文件名含空格）
    # kagglehub 下载后路径可能变化，所以做一次遍历查找更稳妥
    target_name = "CC GENERAL.csv"
    for root, _, files in os.walk(dataset_dir):
        for f in files:
            if f == target_name:
                return os.path.join(root, f)

    raise FileNotFoundError(f"Cannot find '{target_name}' under: {dataset_dir}")

"""
读取并预处理数据：
1) 删除 CUST_ID（如果存在）
2) 仅保留数值列
3) 缺失值：用中位数填充
4) 可选：log1p 缓解偏态和极端值影响
5) 标准化：均值0方差1（K-Means必须）
返回：
- df_num: 预处理后的 DataFrame（未标准化、用于特征名）
- X: 标准化后的 numpy 矩阵（用于聚类）
"""
def load_and_preprocess(csv_path: str, use_log1p: bool = True):
    
    df = pd.read_csv(csv_path)

    if "CUST_ID" in df.columns:
        df = df.drop(columns=["CUST_ID"])

    # 确保只保留数值特征
    df = df.select_dtypes(include=[np.number]).copy()

    # 缺失值填充：中位数（更抗异常值）
    df = df.fillna(df.median(numeric_only=True))

    # 可选：对偏态明显的金额/次数类特征做 log1p
    if use_log1p:
        df = np.log1p(df)

    scaler = StandardScaler()
    X = scaler.fit_transform(df.values)

    return df, X


# 2. K-Mean++ 核心模块
"""
使用 K-Means++ 初始化聚类中心
参数：
X   : (n_samples, n_features) 的数据矩阵
k   : 聚类数
rng : np.random.Generator 随机数生成器，用于保证可复现
返回：
centroids : (k, n_features) 初始化后的中心点
"""
def kmeans_plus_plus_init(X, k, rng):

    # 样本数、特征数
    n_samples = X.shape[0]
    n_features = X.shape[1]

    # 用来存放 k 个中心点
    centroids = np.zeros((k, n_features), dtype=float)

    # 1）随机选择第一个中心点
    first_index = rng.integers(0, n_samples)
    centroids[0] = X[first_index]

    # 2）计算每个点到“最近中心”的距离平方
    #    一开始只有一个中心，就是到 centroids[0] 的距离平方
    closest_dist_sq = np.zeros(n_samples, dtype=float)
    for i in range(n_samples):
        diff = X[i] - centroids[0]
        closest_dist_sq[i] = float(np.dot(diff, diff))

    # 3）依次选择剩余的中心点
    for c in range(1, k):
        # 距离平方的总和，用于归一化成概率
        total = float(np.sum(closest_dist_sq))

        # 如果 total 为 0，说明所有点和中心重合（极端情况），直接随机选一个点
        if total == 0.0:
            rand_index = rng.integers(0, n_samples)
            centroids[c] = X[rand_index]
            continue

        # 计算概率分布：距离平方越大，被选为新中心的概率越大
        probs = closest_dist_sq / total

        # 按照 probs 概率采样一个新中心点
        new_index = rng.choice(n_samples, p=probs)
        centroids[c] = X[new_index]

        # 4）更新每个点到最近中心的距离平方（取更小的那个）
        for i in range(n_samples):
            diff = X[i] - centroids[c]
            dist_sq = float(np.dot(diff, diff))
            if dist_sq < closest_dist_sq[i]:
                closest_dist_sq[i] = dist_sq

    return centroids

"""
将每个样本分配给最近的聚类中心
返回：
labels : (n_samples,) 每个样本所属簇编号
"""
def assign_labels(X, centroids):
    n_samples = X.shape[0]
    k = centroids.shape[0]
    labels = np.zeros(n_samples, dtype=int)
    for i in range(n_samples):
        best_j = 0
        best_dist = None
        # 遍历所有中心，找距离最小的
        for j in range(k):
            diff = X[i] - centroids[j]
            dist_sq = float(np.dot(diff, diff))  # 用平方距离即可，不用开根号
            if (best_dist is None) or (dist_sq < best_dist):
                best_dist = dist_sq
                best_j = j
        labels[i] = best_j
    return labels


"""
根据当前 labels 更新聚类中心（每个簇取均值）
若出现空簇（某一簇没有任何样本），则随机选一个样本作为该簇中心，避免后续计算出错
"""
def update_centroids(X, labels, k, rng):
    n_features = X.shape[1]
    centroids = np.zeros((k, n_features), dtype=float)
    for j in range(k):
        # 找出属于第 j 类的样本下标
        idx_list = []
        for i in range(X.shape[0]):
            if labels[i] == j:
                idx_list.append(i)
        # 空簇处理
        if len(idx_list) == 0:
            rand_index = rng.integers(0, X.shape[0])
            centroids[j] = X[rand_index]
            continue
        # 计算均值作为新中心
        for f in range(n_features):
            s = 0.0
            for idx in idx_list:
                s += float(X[idx, f])
            centroids[j, f] = s / len(idx_list)
    return centroids



# 计算簇内平方和（SSE / inertia）
def compute_inertia(X, labels, centroids):
    
    sse = 0.0
    for i in range(X.shape[0]):
        c = labels[i]
        diff = X[i] - centroids[c]
        sse += float(np.dot(diff, diff))
    return sse

"""
训练 K-Means，并使用 n_init 次初始化选择 SSE 最小的结果
返回：
best_labels, best_centroids, best_inertia
"""
def kmeans_fit(X, k, max_iter=300, tol=1e-4, n_init=10, random_state=42):
    rng = np.random.default_rng(random_state)
    best_labels = None
    best_centroids = None
    best_inertia = None
    # 多次初始化，选择最优
    for run in range(n_init):
        # 初始化中心
        centroids = kmeans_plus_plus_init(X, k, rng)
        # 迭代更新
        for it in range(max_iter):
            labels = assign_labels(X, centroids)
            new_centroids = update_centroids(X, labels, k, rng)
            # 判断中心是否收敛（移动距离很小）
            shift = float(np.linalg.norm(new_centroids - centroids))
            centroids = new_centroids
            if shift < tol:
                break
        inertia = compute_inertia(X, labels, centroids)
        # 记录最优结果
        if (best_inertia is None) or (inertia < best_inertia):
            best_inertia = inertia
            best_labels = labels.copy()
            best_centroids = centroids.copy()
    return best_labels, best_centroids, best_inertia



# 3. 可视化模块
def plot_elbow(ks, inertias, save_path=None):
    plt.figure()
    plt.plot(ks, inertias, marker="o")
    plt.xlabel("K (number of clusters)")
    plt.ylabel("Inertia / SSE")
    plt.title("Elbow Method (K vs SSE)")
    plt.grid(True, alpha=0.3)
    if save_path:
        plt.savefig(save_path, dpi=200, bbox_inches="tight")
    plt.show()


def plot_silhouette(ks, sils, save_path=None):
    plt.figure()
    plt.plot(ks, sils, marker="o")
    plt.xlabel("K (number of clusters)")
    plt.ylabel("Silhouette Score")
    plt.title("Silhouette Score vs K")
    plt.grid(True, alpha=0.3)
    if save_path:
        plt.savefig(save_path, dpi=200, bbox_inches="tight")
    plt.show()


# PCA 降到2维后散点图展示聚类
def plot_pca_clusters(X, labels, centroids, save_path=None):
    
    pca = PCA(n_components=2, random_state=42)
    X2 = pca.fit_transform(X)
    C2 = pca.transform(centroids)

    plt.figure()
    plt.scatter(X2[:, 0], X2[:, 1], c=labels, s=10)
    plt.scatter(C2[:, 0], C2[:, 1], marker="X", s=180)
    plt.xlabel("PC1")
    plt.ylabel("PC2")
    plt.title("K-Means Clustering (PCA 2D Projection)")
    plt.grid(True, alpha=0.25)

    if save_path:
        plt.savefig(save_path, dpi=200, bbox_inches="tight")
    plt.show()

# 聚类中心画像：每个簇在各特征维度上的中心值走势，用于结果解释
def plot_centroid_profile(feature_names, centroids, save_path=None):
    # 1) 画布拉大一点，给长标签留空间
    plt.figure(figsize=(14, 5))

    # 2) 逐簇画中心曲线
    for i in range(centroids.shape[0]):
        plt.plot(range(len(feature_names)), centroids[i], marker="o", linewidth=1)

    # 3) 横坐标标签：旋转 + 对齐
    plt.xticks(range(len(feature_names)), feature_names, rotation=60, ha="right")

    plt.xlabel("Features")
    plt.ylabel("Centroid value (standardized space)")
    plt.title("Cluster Centroid Profiles")
    plt.grid(True, alpha=0.25)

    # 4) 自动调整边距（关键！）
    plt.tight_layout()

    # 5) 保存时紧贴边界（关键！）
    if save_path:
        plt.savefig(save_path, dpi=250, bbox_inches="tight")

    plt.show()



# 4. 主程序
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--csv", type=str, default="", help="path to CC GENERAL.csv (optional)")
    parser.add_argument("--k_min", type=int, default=2)
    parser.add_argument("--k_max", type=int, default=10)
    parser.add_argument("--n_init", type=int, default=10)
    parser.add_argument("--max_iter", type=int, default=300)
    parser.add_argument("--use_log1p", action="store_true")
    parser.add_argument("--save_fig", action="store_true", help="save figures to ./outputs")
    args = parser.parse_args()

    # 1) 获取数据路径
    if args.csv and os.path.exists(args.csv):
        csv_path = args.csv
    else:
        csv_path = download_ccdata()

    print("Using CSV:", csv_path)

    # 2) 预处理
    df_num, X = load_and_preprocess(csv_path, use_log1p=args.use_log1p)
    print("Data shape (rows, features):", X.shape)

    # 输出目录
    out_dir = "outputs"
    if args.save_fig:
        os.makedirs(out_dir, exist_ok=True)

    # 3) 多 K 测试
    ks = list(range(args.k_min, args.k_max + 1))
    inertias, sils = [], []
    models = {}

    for k in ks:
        labels, centroids, inertia = kmeans_fit(
            X, k,
            max_iter=args.max_iter,
            tol=1e-4,
            n_init=args.n_init,
            random_state=42
        )
        inertias.append(inertia)

        sil = silhouette_score(X, labels) if len(np.unique(labels)) > 1 else np.nan
        sils.append(sil)

        models[k] = (labels, centroids, inertia, sil)
        print(f"[K={k}] inertia={inertia:.2f}, silhouette={sil:.4f}")

    # 4) 画 Elbow / Silhouette
    plot_elbow(ks, inertias, save_path=os.path.join(out_dir, "elbow.png") if args.save_fig else None)
    plot_silhouette(ks, sils, save_path=os.path.join(out_dir, "silhouette.png") if args.save_fig else None)

    # 5) 推荐 K：轮廓系数最大（你也可以结合 elbow 再定）
    best_k = ks[int(np.nanargmax(sils))]
    labels, centroids, inertia, sil = models[best_k]
    print(f"\nRecommended K by silhouette: K={best_k}, silhouette={sil:.4f}, inertia={inertia:.2f}")

    # 6) 可视化聚类结果 + 中心画像
    plot_pca_clusters(X, labels, centroids,
                      save_path=os.path.join(out_dir, f"pca_k{best_k}.png") if args.save_fig else None)
    plot_centroid_profile(df_num.columns.tolist(), centroids,
                          save_path=os.path.join(out_dir, f"centroid_profile_k{best_k}.png") if args.save_fig else None)

    # 7) 保存一个结果文件，方便写报告和复现
    result_df = df_num.copy()
    result_df["cluster"] = labels
    result_path = os.path.join(out_dir, f"cluster_result_k{best_k}.csv")
    result_df.to_csv(result_path, index=False)
    print("Cluster result saved to:", result_path)


if __name__ == "__main__":
    main()
