import numpy as np


class WeakClassifier:
    def __init__(self):
        self.feature_index = None
        self.feature_value = None
        self.threshold_type = None
        self.alpha = None

    # 可以直接做一个最优决策树桩
    def stump_classifier(self, X, feature_index, feature_value, threshold_type="less"):
        y_pred = np.ones(X.shape[0])

        if threshold_type == "less":
            y_pred = X[X[:, feature_index] <= feature_value] = -1
        else:
            y_pred = X[X[:, feature_index] > feature_value] = -1

        return y_pred


class Adaboost:
    def __init__(self, ncls):
        self.ncls = ncls
        self.classifiers = list()

    def fit(self, X, y):
        num_sample, num_feature = X.shape
        weights = np.ones(num_sample) / num_sample  # 更新的时候，也要保证weights的和为1
        for _ in range(self.ncls):  # 迭代出ncls个弱分类器的
            tree_stump = WeakClassifier()
            min_error = np.inf
            for i in range(num_feature):
                for fea_val in np.unique(X[:, i]):
                    y_pred = tree_stump.stump_classifier(X, i, fea_val)
                    error_sample = np.ones(num_sample)
                    error_sample[y == y_pred] = 0
                    error = np.dot(weights, error_sample)
                    if error < min_error:
                        min_error = error
                        tree_stump.feature_index = i
                        tree_stump.feature_value = fea_val
            y_pred = tree_stump.stump_classifier(
                X, tree_stump.feature_index, tree_stump.feature_value)
            tree_stump.alpha = 0.5 * \
                np.log((1 - min_error) / (min_error + 1e-15))
            weights *= np.exp(-tree_stump.alpha * y * y_pred)
            weights /= np.sum(weights)
            self.classifiers.append(tree_stump)

        pass
