import numpy as np
from sklearn.model_selection import train_test_split
from sklearn import datasets

class Node:
    def __init__(self, feature_index=None, feature_name=None, node_value=None, child=None):
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
    def __init__(self, feature_name, etype="gain", epsilon=0.1):
        """
            root：代表这个决策树
        """
        self.root = None
        self.feature_name = feature_name
        self.etype = etype
        self.epsilon = epsilon


    def fit(self, X, y):
        """决策树训练"""
        self.root = self.treeGenerate(X, y)

    def predict(self, x):
        """预测函数"""
        return self.predict_impl(x, self.root)

    def predict_impl(self, x, tree=None):
        """预测函数辅助函数, 递归实现"""

        if tree is None:
            tree = self.root
        if tree.node_value is not None:
            return tree.node_value
        
        feature_index = tree.feature_index
        for fea_val, child_node in tree.child.items():
            if x[feature_index] == fea_val:
                if child_node.node_value is not None:
                    return child_node.node_value
                else:
                    return self.predict_impl(x, child_node)

    def treeGenerate(self, X, y):
        """生成决策树"""

        # 处理边界条件
        if X.shape[1] == 1:
            node_value = self.vote_label(y)
            return Node(node_value=node_value)
        if np.unique(y).shape[0] == 1:
            return Node(node_value=y[0])

        # 选取最优属性，划分数据集
        max_gain = -np.inf
        num_feature = X.shape[1]
        max_feature_index = 0

        for i in range(num_feature):
            if self.etype=="gain":
                gain = self.gain(X[:, i], y)
            elif self.etype=="gain_ratio":
                gain = self.gain_ratio(X[:, i], y)
            else:
                gain = -self.calc_gini_index(X[:, i], y)
            
            if max_gain < gain:
                max_gain = gain
                max_feature_index = i
        
        # 特殊情况，不划分数据结构
        if max_gain < self.epsilon:
            node_value = self.vote_label(y)
            return Node(node_value=node_value)
        
        feature_name = self.feature_name[max_feature_index]
        child_tree = dict()

        for fea_val in np.unique(X[:, max_feature_index]):
            child_X = X[X[:, max_feature_index] == fea_val]
            child_y = y[X[:, max_feature_index] == fea_val]
            child_X = np.delete(child_X, max_feature_index, 1)
            child_tree[fea_val] = self.treeGenerate(child_X, child_y)
        return Node(max_feature_index, feature_name=feature_name, child=child_tree)

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

def main():
    iris = datasets.load_iris()
    feature_name = iris["feature_names"]

    xtrain, _, ytrain, _ = train_test_split(iris["data"], iris["target"], train_size=0.8, shuffle=True)

    model = DecisionTreeDemo(feature_name)
    model.fit(xtrain, ytrain)

    n_test = xtrain.shape[0]
    n_right = 0
    for i in range(n_test):
        y_pred = model.predict(xtrain[i])
        if y_pred == ytrain[i]:
            n_right += 1
        else:
            print("the sample's real label is: {}，but the predicted label of model is: {}".format(ytrain[i], y_pred))
    print("the decisionDemo model's accuracy is: {}%".format(n_right * 100 / n_test))


if __name__ == "__main__":
    main()