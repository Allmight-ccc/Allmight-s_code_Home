import argparse
import random

import numpy as np
from sklearn.svm import SVC
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from loguru import logger


class SVMScratch():
    """SVM算法Scratch实现"""
    def __init__(self, C=1.0, kernel="rbf", degree=3, coef0=0.0, epsilon=0.001, n_epoch=3000):
        """
        C:
            由松弛变量引入的正则化项系数
        kernel:
            核函数类型，可取的值有
            linear: 线性核函数
            poly: 多项式核函数
            rbf: 高斯核函数
        degree:
            多项式核函数的次数
        coef0:
            多项式核函数中的系数
        epsilon:
            SMO算法在检验第一个变量对应的样本是否违反KKT条件时，在epsilon范围内检验
        n_epoch:
            训练迭代多少个epoch后终止训练
        """
        self._C = C
        self._kernel = kernel
        self._degree = degree
        self._coef0 = coef0
        self._epsilon = epsilon
        self._n_epoch = n_epoch

    def fit(self, X, y):
        """
        模型训练
        X:
            训练集，每一行表示一个样本，每一列表示一个特征或属性
        y:
            训练集标签
        """
        self._init_params(X, y)

        self._smo_outer(y)

        # 存储支持向量对应的索引
        self._sv_idx = np.squeeze(np.argwhere(self._alpha > 0))
        # 存储支持向量
        self._sv = X[self._sv_idx]
        # 存储支持向量对应的标签
        self._sv_y = y[self._sv_idx]
        # 存储支持向量对应的alpha
        self._sv_alpha = self._alpha[self._sv_idx]

    def predict(self, x):
        """给定输入样本，预测其类别，注意模型是由支持向量决定的"""
        n_sv = self._sv.shape[0]
        x_kernel = np.zeros(n_sv)
        for i in range(n_sv):
            x_kernel[i] = self._kernel_trasform(self._sv[i], x)
        y_pred = np.dot(self._sv_alpha * self._sv_y, x_kernel) + self._b
        return 1 if y_pred > 0 else -1

    def _smo_outer(self, y):
        """
        SMO外层循环
        X:
            训练集，每一行表示一个样本，每一列表示一个特征或属性
        y:
            训练集标签
        **统一用下标i标识第一个变量，下标j标识第二个变量**
        """
        num_epoch = 0
        # 是否遍历整个训练集
        traverse_trainset = True
        # 标识alpha是否已经进行了更新，大于0表示alpha已经更新
        alpha_change = 0
        while alpha_change > 0 or traverse_trainset:
            alpha_change = 0
            if traverse_trainset:
                # 遍历整个训练集
                for i in range(self._m):
                    alpha_change += self._smo_inner(i, y)
            else:
                # 获取间隔边界上支持向量的索引，即 0 < alpha < C对应的支持向量索引
                bound_sv_idx = np.nonzero(np.logical_and(self._alpha > 0, self._alpha < self._C))[0]
                for i in bound_sv_idx:
                    alpha_change += self._smo_inner(i, y)

            num_epoch += 1
            if num_epoch >= self._n_epoch:
                break
            if traverse_trainset:
                # 如果这轮遍历了整个训练集，下一轮遍历间隔边界上的支持向量
                traverse_trainset = False
            elif alpha_change == 0:
                # 如果在间隔边界上未能优化这两个变量(未找到合适的alpha)，则遍历整个训练集重新选择变量
                traverse_trainset = True

    def _smo_inner(self, i, y):
        """
        SMO内层循环
        i:
            第一个变量的索引
        y:
            训练集标签
        **统一用下标i标识第一个变量，下标j标识第二个变量**
        """
        # if (self._alpha[i]>0 and y[i]*self._g(i, y)-1>self._epsilon) or (self._alpha[i]<self._C and y[i]*self._g(i, y)-1<self._epsilon):
        if (self._violate_kkt(i, y)):
            Ei = self._g(i, y) - y[i]
            j, Ej = self._select_j(i, y)

            alpha_i_old = self._alpha[i].copy()
            alpha_j_old = self._alpha[j].copy()

            if y[i] != y[j]:
                # y[i]与y[j]异号
                L = max(0, self._alpha[j] - self._alpha[i])
                H = min(self._C, self._C + self._alpha[j] - self._alpha[i])
            else:
                # y[i]与y[j]同号
                L = max(0, self._alpha[j] + self._alpha[i] - self._C)
                H = min(self._C, self._alpha[j] + self._alpha[i])

            if L == H:
                return 0

            eta = self._K[i,i] + self._K[j,j] - 2 * self._K[i,j]
            # eta表达式本身是完全平方，且eta作为分母不能等于0，所以必须大于0
            if eta <= 0:
                return 0

            # 更新并裁剪第二个变量
            self._alpha[j] += y[j] * (Ei - Ej) / eta
            self._alpha[j] = np.clip(self._alpha[j], L, H)
            self._updateE(j, y)
            # 第二个变量选择的标准是更新后能使自身有足够大的变化
            if abs(self._alpha[j] - alpha_j_old) < 0.00001:
                return 0

            # 更新第一个变量
            self._alpha[i] += y[i] * y[j] * (alpha_j_old - self._alpha[j])
            self._updateE(i, y)

            # 更新b
            b1_new = self._b - Ei - y[i]*self._K[i,i]*(self._alpha[i]-alpha_i_old) - y[j]*self._K[i,j]*(self._alpha[j]-alpha_j_old)
            b2_new = self._b - Ej - y[i]*self._K[i,j]*(self._alpha[i]-alpha_i_old) - y[j]*self._K[j,j]*(self._alpha[j]-alpha_j_old)

            if self._alpha[i] > 0 and self._alpha[i] < self._C:
                self._b = b1_new
            elif self._alpha[j] > 0 and self._alpha[j] < self._C:
                self._b = b2_new
            else:
                self._b = (b1_new + b2_new) / 2
            return 1
        else:
            return 0

    def _violate_kkt(self, i, y):
        """
        在选择第一个变量时我们选择违反KKT条件的样本所对应的变量，且在epsilon范围内检验
        外层循环先遍历间隔边界上的支持向量，并检验这些间隔边界上的支持向量是否满足KKT条件，
        如果全都满足KKT条件，再去遍历整个训练集检验
        间隔边界上的支持向量对应于 0 < alpha < C
        i:
            待检验样本的索引
        y:
            训练集标签
        """
        if self._alpha[i] > 0 and self._alpha[i] < self._C:
            return abs(y[i] * self._g(i, y) - 1) > self._epsilon
        return True

    def _g(self, i, y):
        """
        计算第i个样本的预测值
        i:
            第i个样本索引
        y:
            训练集标签
        """
        return np.dot(self._alpha * y, self._K[i]) + self._b

    def _updateE(self, i, y):
        """更新第i个样本对应的缓存"""
        Ei = self._calc_E(i, y)
        self._ECache[i] = [1, Ei]

    def _calc_E(self, i, y):
        """计算预测值与真实标签之差"""
        return self._g(i, y) - y[i]

    def _select_j(self, i, y):
        """
        给定第一个变量之后寻找第二个变量，我们选择的是使|Ei - Ej|最大的变量
        i:
            第一个变量的索引
        y:
            训练集标签
        **统一用下标i标识第一个变量，下标j标识第二个变量**
        """
        Ei = self._calc_E(i, y)
        self._ECache[i] = [1, Ei]
        # 保存最大的|Ei - Ej|
        max_diff = -np.inf
        # 使|Ei - Ej|最大的索引j
        max_j = -1
        max_Ej = -np.inf

        ecache_idx = np.nonzero(self._ECache[:, 0])[0]
        if len(ecache_idx) > 1:
            # 选择使|Ei - Ej|最大的第二个变量
            for j in ecache_idx:
                if j == i:
                    continue
                Ej = self._calc_E(j, y)
                diff = abs(Ei - Ej)
                if diff > max_diff:
                    max_diff = diff
                    max_j = j
                    max_Ej = Ej
            return max_j, max_Ej
        else:
            # 否则先随机选择一个
            j = i
            while j == i:
                j = random.randint(0, self._m-1)
            Ej = self._calc_E(j, y)
            return j, Ej

    def _init_params(self, X, y):
        """
        初始化参数
        X:
            训练集，每一行表示一个样本，每一列表示一个特征或属性
        y:
            训练集标签
        """
        # 训练集样本个数
        self._m = X.shape[0]
        # 样本维度
        self._n = X.shape[1]
        # 存储变量alpha
        self._alpha = np.zeros(self._m)
        # 存储参数b
        self._b = 0
        # 缓存预测值与真实值之间的误差，第1列标识是否已经更新变量，0标识未更新，1标识已经更新，第2列为误差值
        self._ECache = np.zeros((self._m, 2))
        self._K = np.zeros((self._m, self._m))
        for i in range(self._m):
            for j in range(self._m):
                self._K[i, j] = self._kernel_trasform(X[i], X[j])

    def _kernel_trasform(self, x1, x2):
        """
        对原始数据做kernel映射
        gamma参数参考https://github.com/cjlin1/libsvm
        x1，x2: 训练样本
        """
        gamma = 1 / self._n

        if self._kernel == "linear":
            return np.dot(x1, x2)
        elif self._kernel == "poly":
            return np.power(gamma * np.dot(x1, x2) + self._coef0, self._degree)
        else:
            # 默认高斯核函数
            return np.exp(-gamma * np.dot(x1-x2, x1-x2))


def main():
    parser = argparse.ArgumentParser(description="SVM算法Scratch代码命令行参数")
    parser.add_argument("--nepoch", type=int, default=3000, help="训练多少个epoch后终止训练")
    parser.add_argument("--C", type=float, default=1.0, help="由松弛变量引入的正则化项系数")
    parser.add_argument("--kernel", type=str, default="rbf", help="核函数类型，可取的值有linear, poly, rbf")
    parser.add_argument("--degree", type=int, default=3, help="多项式核函数的次数")
    parser.add_argument("--coef0", type=float, default=0, help="多项式核函数中的系数")
    parser.add_argument("--epsilon", type=float, default=0.001, help="检验第一个变量对应的样本是否违反KKT条件的检验范围")
    args = parser.parse_args()

    X, y = load_iris(return_X_y=True)
    y[:50] = -1
    xtrain, xtest, ytrain, ytest = train_test_split(X[:100], y[:100], train_size=0.8, shuffle=True)

    model = SVMScratch(args.C, args.kernel, args.degree, args.coef0, args.epsilon, args.nepoch)
    model.fit(xtrain, ytrain)

    n_test = xtest.shape[0]
    n_right = 0
    for i in range(n_test):
        y_pred = model.predict(xtest[i])
        if y_pred == ytest[i]:
            n_right += 1
        else:
            logger.info("该样本真实标签为：{}，但是Scratch模型预测标签为：{}".format(ytest[i], y_pred))
    logger.info("Scratch模型在测试集上的准确率为：{}%".format(n_right * 100 / n_test))

    skmodel = SVC(C=args.C, kernel=args.kernel, degree=args.degree, coef0=args.coef0, max_iter=args.nepoch)
    skmodel.fit(xtrain, ytrain)
    logger.info("sklearn模型在测试集上准确率为：{}%".format(100 * skmodel.score(xtest, ytest)))

if __name__ == "__main__":
    main()