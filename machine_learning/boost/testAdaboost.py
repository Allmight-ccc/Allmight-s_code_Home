import numpy as np

class DecisionTreeStump:
    def __init__(self):
        """
            feature_index: 划分特征的索引
            feature_value: 划分特征的值
            threshold_type: 阈值类型，'<' 或者 '>'
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
            weak_classifier = DecisionTreeStump()
            # 记录最小误差
            min_error = np.inf

            # 遍历每一维特征，找到最佳的划分特征，并且生成一个弱分类器
            for i in range(num_feature):
                # 取出数据集中第i列所有可能的取值
                feature_value = np.unique(X[:, i])
                # 遍历这维特征所有可能的取值
                for fea_val in feature_value:
                    for threshold_type in ["less", "great"]:
                        # 获取决策树桩的预测结果
                        y_pred = self.stump_classifier(X, i, fea_val, threshold_type)

                        error_sample = np.ones(num_sample)
                        error_sample[y_pred == y] = 0

                        # 错误率是样本权重的和
                        error = np.dot(weights, error_sample)

                        # 选出最小的错误率
                        if error < min_error:
                            min_error = error
                            # 为弱分类器属性赋值
                            weak_classifier.feature_index = i
                            weak_classifier.feature_value = fea_val
                            weak_classifier.threshold_type = threshold_type

            # 通过最佳的弱分类器，预测的y值
            y_pred = self.stump_classifier(X, weak_classifier.feature_index, weak_classifier.feature_value, weak_classifier.threshold_type)
            # 更新弱分类器的权重(8.11 in machine learning et. zhou)
            weak_classifier.alpha = 0.5 * np.log((1 - min_error) / (min_error + 1e-15))

            # 更新样本的权重
            weights *= np.exp(weak_classifier.alpha * y * y_pred)
            weights /= np.sum(weights)

            # 保存生成的弱分类器
            self.classifiers.append(weak_classifier)
    
    # 决策树桩分类器
    def stump_classifier(self, X, feature_index, feature_value, threshold_type):
        y_pred = np.ones(X.shape[0])
        if threshold_type == "less":
            # 如果这一维的数据小于feature_value，就设为-1
            y_pred[X[:, feature_index] <= feature_value] = -1
        else:
            y_pred[X[:, feature_index] >  feature_value] = -1
        return y_pred

    def predict(self, x):
        """ 预测函数 """
        y_pred = 0
        for cls in self.classifiers:
            pred = 1
            if cls.threshold_type == "less":
                if x[cls.feature_index] <= cls.feature_value:
                    pred = -1
            else:
                if x[cls.feature_index] > cls.feature_value:
                    pred = -1
            y_pred += cls.alpha * pred
        return np.sign(y_pred)



def main():
    model = Adaboost(100)
    model.fit()

if __name__ == "__main__":
    main()