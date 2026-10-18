import os
import argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

import kagglehub
from sklearn.preprocessing import StandardScaler, RobustScaler
from sklearn.decomposition import PCA
from sklearn.metrics import silhouette_score, silhouette_samples


# 1. 数据下载与读取
def download_ccdata():
    """
    使用 kagglehub 下载 ccdata 数据集并返回 CC GENERAL.csv 的路径
    """
    dataset_dir = kagglehub.dataset_download("arjunbhasin2013/ccdata")

    target_name = "CC GENERAL.csv"
    for root, _, files in os.walk(dataset_dir):
        for f in files:
            if f == target_name:
                return os.path.join(root, f)

    raise FileNotFoundError("Cannot find 'CC GENERAL.csv' under: {}".format(dataset_dir))


def load_and_preprocess(csv_path, use_log1p=True, use_robust=True):
    """
    读取并预处理数据：
    1) 删除 CUST_ID（如果存在）
    2) 仅保留数值列
    3) 缺失值：用中位数填充
    4) 可选：log1p 缓解偏态（降低极端值影响）
    5) 缩放：StandardScaler 或 RobustScaler（改进点）

    返回：
    df_num : 预处理后的数值型 DataFrame（用于特征名）
    X      : 缩放后的 numpy 矩阵（用于聚类）
    """
    df = pd.read_csv(csv_path)

    # 1) 删除无关 ID 列
    if "CUST_ID" in df.columns:
        df = df.drop(columns=["CUST_ID"])

    # 2) 只保留数值列
    df = df.select_dtypes(include=[np.number]).copy()

    # 3) 缺失值用中位数填充（比均值更抗异常值）
    df = df.fillna(df.median(numeric_only=True))

    # 4) 可选：log1p 缓解偏态（金额/次数类常偏态）
    if use_log1p:
        df = np.log1p(df)

    #  改进点 1：RobustScaler 抗异常值 
    # RobustScaler 使用中位数与四分位距缩放，异常值不会像 StandardScaler 那样强烈影响尺度
    if use_robust:
        scaler = RobustScaler()
    else:
        scaler = StandardScaler()

    X = scaler.fit_transform(df.values)
    return df, X


# 2. K-Means 核心实现（K-Means++ + n_init）
def kmeans_plus_plus_init(X, k, rng):
    """
    K-Means++ 初始化：
    - 第一个中心随机选
    - 后续中心按照“到最近中心距离平方”作为概率选择
    目的：让初始中心更分散，提升稳定性（比纯随机更好）
    """
    n_samples = X.shape[0]
    n_features = X.shape[1]

    centroids = np.zeros((k, n_features), dtype=float)

    # (1) 第一个中心：随机选
    first_index = rng.integers(0, n_samples)
    centroids[0] = X[first_index]

    # (2) 记录每个点到最近中心的距离平方
    closest_dist_sq = np.zeros(n_samples, dtype=float)
    for i in range(n_samples):
        diff = X[i] - centroids[0]
        closest_dist_sq[i] = float(np.dot(diff, diff))

    # (3) 依次选择剩余中心
    for c in range(1, k):
        total = float(np.sum(closest_dist_sq))
        if total == 0.0:
            # 极端情况：所有点都一样
            rand_index = rng.integers(0, n_samples)
            centroids[c] = X[rand_index]
            continue

        probs = closest_dist_sq / total
        new_index = rng.choice(n_samples, p=probs)
        centroids[c] = X[new_index]

        # 更新每个点到最近中心的距离平方
        for i in range(n_samples):
            diff = X[i] - centroids[c]
            dist_sq = float(np.dot(diff, diff))
            if dist_sq < closest_dist_sq[i]:
                closest_dist_sq[i] = dist_sq

    return centroids


def assign_labels(X, centroids):
    """
    分配步骤：把每个样本分配给最近的中心
    这里采用朴素写法（循环），便于报告说明
    """
    n_samples = X.shape[0]
    k = centroids.shape[0]
    labels = np.zeros(n_samples, dtype=int)

    for i in range(n_samples):
        best_j = 0
        best_dist = None
        for j in range(k):
            diff = X[i] - centroids[j]
            dist_sq = float(np.dot(diff, diff))  # 用平方距离即可
            if (best_dist is None) or (dist_sq < best_dist):
                best_dist = dist_sq
                best_j = j
        labels[i] = best_j

    return labels


def update_centroids(X, labels, k, rng):
    """
    更新步骤：每个簇的中心 = 簇内样本均值
    若出现空簇：随机选一个样本作为该簇中心，避免算法崩溃
    """
    n_features = X.shape[1]
    centroids = np.zeros((k, n_features), dtype=float)

    for j in range(k):
        idx_list = []
        for i in range(X.shape[0]):
            if labels[i] == j:
                idx_list.append(i)

        if len(idx_list) == 0:
            rand_index = rng.integers(0, X.shape[0])
            centroids[j] = X[rand_index]
            continue

        for f in range(n_features):
            s = 0.0
            for idx in idx_list:
                s += float(X[idx, f])
            centroids[j, f] = s / len(idx_list)

    return centroids


def compute_inertia(X, labels, centroids):
    """
    计算 SSE / inertia：簇内平方和
    """
    sse = 0.0
    for i in range(X.shape[0]):
        c = labels[i]
        diff = X[i] - centroids[c]
        sse += float(np.dot(diff, diff))
    return sse


def kmeans_fit(X, k, max_iter=300, tol=1e-4, n_init=10, random_state=42):
    """
    训练 K-Means，并用 n_init 次初始化选择 SSE 最小的结果（提升稳定性）
    返回：best_labels, best_centroids, best_inertia
    """
    rng = np.random.default_rng(random_state)

    best_labels = None
    best_centroids = None
    best_inertia = None

    for run in range(n_init):
        centroids = kmeans_plus_plus_init(X, k, rng)

        for it in range(max_iter):
            labels = assign_labels(X, centroids)
            new_centroids = update_centroids(X, labels, k, rng)

            shift = float(np.linalg.norm(new_centroids - centroids))
            centroids = new_centroids

            if shift < tol:
                break

        inertia = compute_inertia(X, labels, centroids)

        if (best_inertia is None) or (inertia < best_inertia):
            best_inertia = inertia
            best_labels = labels.copy()
            best_centroids = centroids.copy()

    return best_labels, best_centroids, best_inertia


# 3. 改进点 2：PCA-KMeans（先降维再聚类）
def pca_preprocess(X, var_ratio=0.95, random_state=42):
    """
    PCA 降维：保留 var_ratio 的累计方差（如 0.95）
    用于“先 PCA 再 K-Means”的流程优化
    """
    pca = PCA(n_components=var_ratio, random_state=random_state)
    X_pca = pca.fit_transform(X)
    return X_pca, pca


# 4. 可视化模块
def plot_elbow(ks, inertias, save_path=None):
    plt.figure()
    plt.plot(ks, inertias, marker="o")
    plt.xlabel("K (number of clusters)")
    plt.ylabel("Inertia / SSE")
    plt.title("Elbow Method (K vs SSE)")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    if save_path:
        plt.savefig(save_path, dpi=250, bbox_inches="tight")
    plt.show()


def plot_silhouette_curve(ks, sils, save_path=None):
    plt.figure()
    plt.plot(ks, sils, marker="o")
    plt.xlabel("K (number of clusters)")
    plt.ylabel("Silhouette Score")
    plt.title("Silhouette Score vs K")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    if save_path:
        plt.savefig(save_path, dpi=250, bbox_inches="tight")
    plt.show()


def plot_pca_clusters(X, labels, centroids, save_path=None):
    """
    PCA 仅用于可视化（降到2维），与 K 的选择无关
    """
    pca2 = PCA(n_components=2, random_state=42)
    X2 = pca2.fit_transform(X)
    C2 = pca2.transform(centroids)

    plt.figure()
    plt.scatter(X2[:, 0], X2[:, 1], c=labels, s=10)
    plt.scatter(C2[:, 0], C2[:, 1], marker="X", s=180)
    plt.xlabel("PC1")
    plt.ylabel("PC2")
    plt.title("K-Means Clustering (PCA 2D Projection)")
    plt.grid(True, alpha=0.25)
    plt.tight_layout()
    if save_path:
        plt.savefig(save_path, dpi=250, bbox_inches="tight")
    plt.show()


def plot_centroid_profile(feature_names, centroids, save_path=None):
    """
    聚类中心画像：展示每个簇在各特征维度上的中心值（标准化空间）
    """
    plt.figure(figsize=(14, 5))

    for i in range(centroids.shape[0]):
        plt.plot(range(len(feature_names)), centroids[i], marker="o", linewidth=1)

    plt.xticks(range(len(feature_names)), feature_names, rotation=60, ha="right")
    plt.xlabel("Features")
    plt.ylabel("Centroid value (standardized space)")
    plt.title("Cluster Centroid Profiles")
    plt.grid(True, alpha=0.25)

    plt.tight_layout()
    if save_path:
        plt.savefig(save_path, dpi=250, bbox_inches="tight")
    plt.show()


# 3：Silhouette Plot（样本级分布）
def plot_silhouette_detail(X, labels, save_path=None):
    """
    轮廓系数分布图（Silhouette Plot）：
    - 平均 silhouette 只有一个数，这张图能看到每个簇内部的“好/坏样本”分布
    """
    s_values = silhouette_samples(X, labels)

    plt.figure(figsize=(8, 5))
    y_lower = 10

    unique_labels = np.unique(labels)
    for c in unique_labels:
        c_values = s_values[labels == c]
        c_values.sort()

        y_upper = y_lower + len(c_values)
        plt.fill_betweenx(range(y_lower, y_upper), 0, c_values)

        # 标注簇编号
        plt.text(-0.05, (y_lower + y_upper) / 2.0, str(c))
        y_lower = y_upper + 10

    plt.xlabel("Silhouette value")
    plt.ylabel("Samples")
    plt.title("Silhouette Plot (per-sample distribution)")
    plt.grid(True, alpha=0.2)
    plt.tight_layout()

    if save_path:
        plt.savefig(save_path, dpi=250, bbox_inches="tight")
    plt.show()


# 5. 主程序
def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("--csv", type=str, default="", help="path to CC GENERAL.csv (optional)")
    parser.add_argument("--k_min", type=int, default=2)
    parser.add_argument("--k_max", type=int, default=12)  # 默认扩展到 12，方便你回应“肘部是否在10之后”
    parser.add_argument("--n_init", type=int, default=10)
    parser.add_argument("--max_iter", type=int, default=300)

    parser.add_argument("--use_log1p", action="store_true")
    parser.add_argument("--use_robust", action="store_true")          # 改进点1开关
    parser.add_argument("--cluster_on_pca", action="store_true")      # 改进点2开关
    parser.add_argument("--pca_var", type=float, default=0.95)        # PCA保留方差比例
    parser.add_argument("--sil_detail", action="store_true")          # 改进点3开关

    parser.add_argument("--save_fig", action="store_true")
    args = parser.parse_args()

    # 1) 获取数据路径
    if args.csv and os.path.exists(args.csv):
        csv_path = args.csv
    else:
        csv_path = download_ccdata()

    print("Using CSV:", csv_path)

    # 2) 预处理
    df_num, X = load_and_preprocess(
        csv_path,
        use_log1p=args.use_log1p,
        use_robust=args.use_robust
    )
    print("Data shape (rows, features):", X.shape)

    # 输出目录
    out_dir = "outputs"
    if args.save_fig:
        os.makedirs(out_dir, exist_ok=True)

    # 改进点2：PCA-KMeans（先降维再聚类）
    # 这里 X_for_kmeans 用于“聚类计算”
    # 可视化时仍可以用原始 X 再做2维PCA展示
    if args.cluster_on_pca:
        X_for_kmeans, pca_model = pca_preprocess(X, var_ratio=args.pca_var, random_state=42)
        print("PCA for K-Means: {} -> {} dims (var_ratio={})".format(
            X.shape[1], X_for_kmeans.shape[1], args.pca_var
        ))
    else:
        X_for_kmeans = X

    # 3) 多 K 测试
    ks = list(range(args.k_min, args.k_max + 1))
    inertias = []
    sils = []
    models = {}

    for k in ks:
        labels, centroids, inertia = kmeans_fit(
            X_for_kmeans, k,
            max_iter=args.max_iter,
            tol=1e-4,
            n_init=args.n_init,
            random_state=42
        )

        inertias.append(inertia)

        # silhouette_score 需要至少2个簇
        if len(np.unique(labels)) > 1:
            sil = silhouette_score(X_for_kmeans, labels)
        else:
            sil = np.nan

        sils.append(sil)
        models[k] = (labels, centroids, inertia, sil)
        print("[K={}] inertia={:.2f}, silhouette={:.4f}".format(k, inertia, sil))

    # 4) Elbow / Silhouette 曲线
    plot_elbow(ks, inertias, save_path=os.path.join(out_dir, "elbow.png") if args.save_fig else None)
    plot_silhouette_curve(ks, sils, save_path=os.path.join(out_dir, "silhouette.png") if args.save_fig else None)

    # 5) 推荐 K（以 silhouette 最大为准）
    best_k = ks[int(np.nanargmax(sils))]
    labels, centroids, inertia, sil = models[best_k]
    print("\nRecommended K by silhouette: K={}, silhouette={:.4f}, inertia={:.2f}".format(best_k, sil, inertia))

    # 6) 可视化：PCA散点 + 中心画像
    # centroids 是在 X_for_kmeans 空间中的中心
    if args.cluster_on_pca:
        # 在 PCA 空间再降到2维可视化（如果 PCA维度>2）
        plot_pca_clusters(X_for_kmeans, labels, centroids,
                          save_path=os.path.join(out_dir, "pca_k{}.png".format(best_k)) if args.save_fig else None)

        # 中心画像：此时特征是 PCA 主成分，不再是原始17列
        pca_feature_names = ["PC{}".format(i + 1) for i in range(centroids.shape[1])]
        plot_centroid_profile(pca_feature_names, centroids,
                              save_path=os.path.join(out_dir, "centroid_profile_k{}.png".format(best_k)) if args.save_fig else None)
    else:
        # 在原始缩放后的特征空间可视化
        plot_pca_clusters(X, labels, centroids,
                          save_path=os.path.join(out_dir, "pca_k{}.png".format(best_k)) if args.save_fig else None)
        plot_centroid_profile(df_num.columns.tolist(), centroids,
                              save_path=os.path.join(out_dir, "centroid_profile_k{}.png".format(best_k)) if args.save_fig else None)

    # 改进点3：Silhouette Plot 
    if args.sil_detail:
        plot_silhouette_detail(
            X_for_kmeans, labels,
            save_path=os.path.join(out_dir, "silhouette_detail_k{}.png".format(best_k)) if args.save_fig else None
        )

    # 7) 保存结果（cluster标签）
    # 这里保存的是“预处理后的 df_num + cluster”
    result_df = df_num.copy()
    result_df["cluster"] = labels
    result_path = os.path.join(out_dir, "cluster_result_k{}.csv".format(best_k))
    result_df.to_csv(result_path, index=False)
    print("Cluster result saved to:", result_path)


if __name__ == "__main__":
    main()
