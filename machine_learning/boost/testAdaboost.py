import numpy as np

class DecisionTreeStump:
    def __init__(self):
        """
            feature_index: 划分特征的索引
            feature_value: 划分特征的值
            threshold_type: 阈值类型，< 或者 >
            alpha: 弱分类器的权重
        """
        self.feature_index = None
        self.feature_value = None
        self.threshold_type = None
        self.alpha = None

class Adaboost:
    def __init__(self, ncls):
        """
            ncls: 弱分类器的数量
            classifiers: 存储所有的弱分类器
        """
        self.ncls = ncls
        self.classifiers = list()

    def fit(self, X, y):
        """ 训练函数 """

        num_sample, num_feature = X.shape
        # 初始化样本的权重
        weights = np.ones(num_sample) / num_sample

        # 训练弱分类器
        for _ in range(self.ncls):
            tree_stem = DecisionTreeStump()
            # 记录最小误差
            min_error = np.inf

            # 遍历每一维特征
            for i in range(num_feature):
                # 取出数据集中第i列所有可能的取值
                feature_value = np.unique(X[:, i])
                # 遍历这维特征所有可能的取值
                for fea_val in feature_value:
                    for threshold_type in ["less", "great"]:
                        pass

    def stump_classifier(self, X, feature_index, feature_value, threshold_type):
        y_pred = np.ones(X.shape[0])
        if threshold_type == "less":
            y_pred[X[:, feature_index] <= feature_value] = -1
        else:
            y_pred[X[:, feature_index] >  feature_value] = -1

    def predict(self, x):
        """ 预测函数 """
        pass



def main():
    Adaboost(100)
    print("Adaboost")
    DecisionTreeStump()
    print("DecisionTreeStump")

if __name__ == "__main__":
    main()