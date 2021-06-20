import numpy as np
import sympy as sp
import matplotlib.pyplot as plt


class Hard_SVM:
    # # 目标函数(hook)
    def objective_func(self, weights):
        return np.sum([weight**2 for weight in weights]) / 2

    # 约束函数(hook)
    def subject_to_func(self, X, y, weights, b):
        return [1-yi*(np.sum(weights*Xi)+b) for yi, Xi in zip(y, X)]

    # TODO 有问题，没有处理约束条件的kkt条件，需要嵌套进去
    # 拉格朗日乘子式
    def lagrange_func(self, lambdas, X, y, weights, b):
        return self.objective_func(weights) + \
            np.sum([lam*st for lam, st in zip(lambdas, self.subject_to_func(X, y, weights, b))])

    # kkt条件
    def kkt_condition(self, lambdas, X, y, weights, b):
        lam_st_kkts = [kkt for kkt in lambdas*self.subject_to_func(X, y, weights, b)]
        lam_kkts = [max(lam, 0) for lam in lambdas]
        st_kkts = [min(st, 0) for st in self.subject_to_func(X, y, weights, b)]
        return lam_st_kkts, lam_kkts, st_kkts

    # 拉格朗日函数的导数，返回对weights和b的偏导数
    def diff_lagrange_func(self, lambdas, X, y, weights):
        diff_w = weights - [np.sum(lambdas*y*Xi) for Xi in X]   #TODO 难说是不是正确的
        diff_b = -np.sum([lam*yi for lam, yi in zip(lambdas, y)])
        return diff_w, diff_b

    def fit(self, X, y):
        lambdas = 1 / np.ones(X.shape[0])
        weights = 1 / np.ones(X.shape[0])
        diff_w, diff_b = self.diff_lagrange_func(lambdas, X, y, weights)
        lam_st_kkts, _, _ = self.kkt_condition(lambdas, X, y, diff_w, diff_b)
        
        # 怎么样更新参数使得满足kkt条件，并且找到使目标函数最小的解,换句话说，需要求解一个齐次矩阵的平凡解
        # 然后将所有的平凡解都存储起来，再在其中找到违背kkt条件最小的解
        # 这是之后要做的工作，现在还做不了，没有解决办法
        # 当然，sympy是可以解决的，它可以直接给你求函数

# 这个版本用sympy解决，之后再自己想办法
class SVM:
    def dual_lagrange():
        pass



def test_svm():
    x = np.array([[3, 4, 1], [3, 3, 1]])
    y = np.array([1, 1, -1])

    N, M = x.shape
    w = np.ones(M)
    b = 0.0

    # 定义变量
    w1, w2, B, lam1, lam2, lam3 = sp.symbols('w1 w2 B lam1 lam2 lam3')

    # 最小函数
    f = (w1**2 + w2**2) / 2

    # 约束条件
    st1 = 1 - y[0] * (w1*3 + w2*3 + B)
    st2 = 1 - y[1] * (w1*4 + w2*3 + B)
    st3 = 1 - y[2] * (w1*1 + w2*1 + B)

    # 定义拉格朗日乘子式
    lagrange = f + lam1*st1 + lam2*st2 + lam3*st3

    sp.pprint_use_unicode(lagrange)

def main():
    weights = np.array([1, 1])
    X = np.array([[3, 4, 1], [3, 3, 1]]).T
    y = np.array([1, 1, -1])
    lambdas = np.array([1, 1, 1])
    svm = Hard_SVM()
    # print(svm.subject_to_func(X, y, weights, 0))
    # print(svm.kkt_condition(lambdas, X, y, weights, 0))
    # for a, b, c in zip(lambdas, X.T, y):
    #     print(a, b, c)
    # for yi, Xi in zip(y, X):
    #     print(Xi, yi)
    plt.figure()
    for i in range(3):
        for j in range(2):
            plt.scatter(X[i][j], X[i][j], c="b", s=10)
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
