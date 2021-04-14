import numpy as np
from sklearn import datasets, model_selection
import argparse
from loguru import logger


class TreeNode:
    def __init__(self, feature_index=None, feature_value=None, feature_name=None, node_value=None, child=None):
        """
            初始化节点：
                feature_index：生成节点的特征索引
                feature_value：生成节点的特征值
                feature_name：生成节点的特证名
                node_value：生成节点的值（只有叶节点有值）
                child：只用中间节点才有子节点
        """
        self.feature_index = feature_index
        self.feature_name = feature_name
        self.feature_value = feature_value
        self.node_value = node_value
        self.child = child

class DecisionTreeClassifier:
    def __init__(self, feature_name, etype, epsilon=0.1):
        """
            feature_name：特征名
            etype：划分节点的依据类型
            epsilon：阈值，小于这个阈值就直接生成为叶节点
        """
        self.root = None
        self.feature_name = feature_name
        self.etype = etype
        self.epsilon = epsilon

    def fit(self, X, y):
        """模型训练：训练的过程就是构建决策树的过程"""
        self.root = self.build_tree(X, y)

    def predict(self, x):
        """预测样本类别"""
        return self.predict_help(x, self.root)

    def predict_help(self, x, tree=None):
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
                    return self.predict_help(x, child_node)

    def build_tree(self, X, y):
        """构建决策树"""

        if X.shape[1] == 1:  # X中的特征只剩下最后一列了，直接将其设置为叶节点，设置方式为投票
            node_value = self.vote_label(y)
            return TreeNode(node_value=node_value)
        if np.unique(y).shape[0] == 1:  # y只有一种类别
            return TreeNode(node_value=y[0])

        num_feature = X.shape[1] #?
        max_gain = -np.inf
        max_feature_index = 0
        for i in range(num_feature):
            if self.etype == "gain":
                gain = self.calc_gain(X[:, i], y)
            else:
                gain = self.calc_gain_ratio(X[:, i], y)
            
            if gain > max_gain:
                max_gain = gain
                max_feature_index = i

        if max_gain < self.epsilon:
            node_value = self.vote_label(y)
            return TreeNode(node_value=node_value)
        
        # 划分特征名，也就是gain最大的那一列特征
        feature_name = self.feature_name[max_feature_index]
        # 子树字典，用于存储划分特征不同取值的子树
        child_tree = dict()
        # 遍历生成划分点的所有子树
        for fea_val in np.unique(X[:, max_feature_index]):
            # 找到对应的子集
            child_X = X[X[:, max_feature_index]==fea_val]
            child_y = y[X[:, max_feature_index]==fea_val]
            # 去除划分特征的那一列
            child_X = np.delete(child_X, max_feature_index, 1)
            # 构建子树，并存入字典，fea_val作为key，子树作为value
            child_tree[fea_val] = self.build_tree(child_X, child_y)

        # 最终返回的是根节点，包含了特征名和所有的子树
        return TreeNode(max_feature_index, feature_name=feature_name, child=child_tree)

    def vote_label(self, y):
        """统计剩余样本中类别出现次数最后的样本的类别"""
        label, num_label = np.unique(y, return_counts=True)
        return label[np.argmax(num_label)]
    
    def calc_entropy(self, y):
        """计算熵：y为标签集，根据标签集计算熵"""
        entropy = 0
        # 计算y可能的取值（不关系，令其为_），以及不同值的数量
        _, num_ck = np.unique(y, return_counts=True)
        # 计算熵
        for n in num_ck:
            p = n / y.shape[0]  # y.size
            entropy -= p * np.log2(p)
        return entropy

    def calc_condition_entropy(self, x, y):
        """计算条件熵， x为训练集中的某一列的特征，是一个向量"""
        condition_entropy = 0
        # x所有可能的取值以及每一个值出现的次数
        xval, num_x = np.unique(x, return_counts=True)
        # zip将xval和num_x对象的元素打包成元组
        for v, n in zip(xval, num_x):
            # [x==v]返回是一个bool序列，y按照这个bool序列的真假取值，再将这个list赋值给y_sub
            sub_y = y[x==v]
            sub_entropy = self.calc_entropy(sub_y)
            # 条件熵的权重，n为y_sub对应的长度
            p = n / y.shape[0]
            condition_entropy += p * sub_entropy
        return condition_entropy

    def calc_gain(self, x, y):
        """计算信息增益"""
        return self.calc_entropy(y) - self.calc_condition_entropy(x, y)

    def calc_gain_ratio(self, x, y):
        """计算信息增益比"""
        return self.calc_gain(x, y) / self.calc_entropy(x)

def main():
    parser = argparse.ArgumentParser(description="决策树算法命令参数")
    parser.add_argument("--epsilon", type=float, default=0.1, help="housholder")
    parser.add_argument("--etype", type=str, default="gain", help="gain or gain_ratio")
    args = parser.parse_args()

    iris = datasets.load_iris()
    feature_name = iris["feature_names"]

    xtrain, _, ytrain, _ = model_selection.train_test_split(iris["data"], iris["target"], train_size=0.8, shuffle=True)

    model = DecisionTreeClassifier(feature_name, args.etype, args.epsilon)
    model.fit(xtrain, ytrain)

    n_test = xtrain.shape[0]
    n_right = 0
    for i in range(n_test):
        y_pred = model.predict(xtrain[i])
        if y_pred == ytrain[i]:
            n_right += 1
        else:
            logger.info("该样本真实标签为：{}，但决策树模型的预测标签为：{}".format(ytrain[i], y_pred))
    logger.info("决策树模型的准确率为：{}%".format(n_right * 100 / n_test))

if __name__ == "__main__":
    main()