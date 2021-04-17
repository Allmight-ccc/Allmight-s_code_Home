import numpy as np

class Node:
    def __init__(self, feature_name=None, feature_index=None, node_value=None, child=None):
        """
            feature_index：特征的索引
            feature_name：特证名
            node_value：叶子结点的值
            child：该节点的子树，是一个字典
        """
        self.feature_index = feature_index
        self.feature_name = feature_name
        self.node_value = node_value
        self.child = child


class DecisionTreeDemo:
    def __init__(self, feature_index=None, etype="gain", epsilon=0.1):
        """
            root：代表这个决策树
        """
        self.root = None
        self.feature_index = feature_index
        self.etype = etype
        self.epsilon = epsilon


    def fit(self, X, y):
        pass

    def predict(self, x):
        pass

    def treeGenerate(self, X, y):
        """生成决策树"""

        # 处理边界条件
        if X.shape[1] == 1:
            node_value = self.vote_label(y)
            return Node(node_value=node_value)
        if np.unique(y).shape[0] == 1:
            return Node(node_value=y[0])

        #ToDo here
        if self.etype=="gain":
            pass

    def vote_label(self, y):
        """投票选出合适的label"""
        label_val, num_label = np.unique(y, return_counts=True)
        return label_val[np.argmax(num_label)]


    def calc_entropy(self, y):
        """计算信息熵"""
        _, num_y = np.unique(y, return_counts=True)
        p = num_y / y.shape[0]
        return -np.sum(p * np.log2(p))

    def calc_condition_entropy(self, x, y):
        """计算条件熵"""
        condition_entropy = 0
        
        for val in np.unique(x):
            sub_y = y[x==val]
            weight = sub_y.shape[0]/y.shape[0]
            condition_entropy += weight * self.calc_entropy(sub_y)
        return condition_entropy

    def gain(self, x, y):
        """计算信息增益"""
        return self.calc_entropy(y) - self.calc_condition_entropy(x, y)

    def gain_ratio(self, x, y):
        """计算信息增益比"""
        return self.gain(x, y) / self.calc_entropy(x)

    def calc_gini(self, y):
        """计算基尼值"""
        _, num_y = np.unique(y, return_counts=True)
        p = num_y / y.shape[0]
        return 1 - np.sum(p**2)

    def calc_gini_index(self, x, y):
        """计算基尼指数"""
        gini_index = 0

        for val in np.unique(x):
            sub_y = y[x==val]
            weight = sub_y.shape[0] / y.shape[0]
            gini_index += weight * self.calc_gini(sub_y)
        return gini_index