import sympy as sp
import numpy as np


class SVM:
    def __init__(self, X, y):
        self.alphas = sp.Matrix([sp.symbols('alpha_0:%d' % X.shape[0])])
        self.weights = sp.Matrix([sp.symbols('w_0:%d' % X.shape[1])])
        self.b = sp.symbols('b')

        self.X = X
        self.y = y

    def __objective_func(self):
        return np.sum([weight**2 for weight in self.weights]) / 2

    def __subject_to_func(self):
        return sp.Matrix([1-yi*(np.sum(self.weights*Xi) + self.b) for yi, Xi in zip(self.y, self.X)])

    def __lagrange_func(self):
        return self.__objective_func() + np.sum(self.alphas * self.__subject_to_func())

    def __diff_func(self):
        diff_w = sp.Matrix(sp.diff(self.__lagrange_func(), self.weights))
        diff_b = sp.diff(self.__lagrange_func(), self.b)
        return diff_w, diff_b

    def __kkts(self):
        alpha_st_kkts = sp.Matrix(
            np.diag(np.array(self.alphas.T * self.__subject_to_func().T)))
        alpha_kkts = sp.Matrix([sp.Ge(alpha, 0) for alpha in self.alphas])
        st_kkts = sp.Matrix([sp.Le(st, 0) for st in self.__subject_to_func()])
        return alpha_st_kkts, alpha_kkts, st_kkts

    def __solve(self):
        diff_w, diff_b = self.__diff_func()
        alpha_st_kkts, _, _ = self.__kkts()
        return sp.Matrix(sp.solve([*diff_w, diff_b, *alpha_st_kkts], [*self.weights, self.b, *self.alphas]))

    def fit(self):
        min_solve = 0
        min_subs = 1e20

        solve = self.__solve()
        _, alpha_kkts, st_kkts = self.__kkts()
        w = solve[:, 0:self.weights.shape[1]]
        b = solve[:, self.weights.shape[1]]
        a = solve[:, self.weights.shape[1]+1:solve.shape[1]]
        r = sp.Matrix([{'w': j[0], 'b': j[1], 'a': j[2]} for j in [
                      [w[i, :], b[i], a[i, :]] for i in range(b.shape[0])]])

        # 带入计算
        for i in range(r.shape[0]):
            param_dict = dict()
            for j in range(self.alphas.shape[1]):
                param_dict[str(self.alphas[j])] = r[i]['a'][j]
            param_dict['b'] = r[i]['b']
            for j in range(self.weights.shape[1]):
                param_dict[str(self.weights[j])] = r[i]['w'][j]
            print(param_dict)

            # 比对kkt条件
            for j in range(alpha_kkts.shape[0]):
                if not alpha_kkts[j].subs(param_dict):
                    continue
            for j in range(st_kkts.shape[0]):
                if 
        
        # 求得结果

    def dispay_func(self):
        print("目标函数："), sp.pprint(self.__objective_func())
        print("约束函数："), sp.pprint(self.__subject_to_func())
        print("拉格朗日乘子式："), sp.pprint(self.__lagrange_func())

    def dispay_diff_func(self):
        diff_w, diff_b = self.__diff_func()
        print("拉格朗日乘子式w偏导数："), sp.pprint(diff_w)
        print("拉格朗日乘子式b偏导数："), sp.pprint(diff_b)

    def display_kkts(self):
        alpha_st_kkts, alpha_kkts, st_kkts = self.__kkts()
        print("kkt约束a*(st)："), sp.pprint(alpha_st_kkts)
        print("kkt约束a："), sp.pprint(alpha_kkts)
        print("kkt约束st："), sp.pprint(st_kkts)

    def display_solve(self):
        print("结果："), sp.pprint(self.__solve())


def main():
    X = np.array([[3, 3], [4, 3], [1, 1]])
    y = np.array([1, 1, -1])
    svm = SVM(X, y)
    # svm.dispay_func()
    # svm.dispay_diff_func()
    # svm.display_kkts()
    # svm.display_solve()
    svm.fit()


if __name__ == "__main__":
    main()
