import sympy as sp
import numpy as np

class SVM:
    def __init__(self, X, y):
        self.alphas = sp.Matrix([sp.symbols('alpha_0:%d' % X.shape[0])])
        self.weights = sp.Matrix([sp.symbols('w_0:%d' % X.shape[1])])
        self.b = sp.symbols('b')

        self.X = X;
        self.y = y;

    def __objective_func(self):
        return np.sum([weight**2 for weight in self.weights]) / 2

    def __subject_to_func(self):
        return sp.Matrix([1-yi*(np.sum(self.weights*Xi) + self.b) for yi, Xi in zip(self.y, self.X)])
    
    def __lagrange_func(self):
        return self.__objective_func() + np.sum([alpha*st for alpha, st in zip(self.alphas, self.__subject_to_func())])

    def __diff_func(self):
        diff_w = sp.Matrix([sp.diff(self.__lagrange_func(), self.weights[i]) for i in range(self.weights.shape[1])])
        diff_b = sp.diff(self.__lagrange_func(), self.b)
        return diff_w, diff_b

    def __kkts(self):
        alpha_st_kkts = sp.Matrix([item for item in np.diag(np.array([elem for elem in sp.Matrix(self.alphas.T * self.__subject_to_func().T)]).reshape(3, 3))])
        alpha_kkts = sp.Matrix([sp.Ge(alpha, 0) for alpha in self.alphas])
        st_kkts = sp.Matrix([sp.Le(st, 0) for st in self.__subject_to_func()])
        return alpha_st_kkts, alpha_kkts, st_kkts

    def __solve(self):
        diff_w, diff_b = self.__diff_func()
        alpha_st_kkts, _, _ = self.__kkts()
        return sp.Matrix(sp.solve([*diff_w, diff_b, *alpha_st_kkts], [*self.weights, self.b, *self.alphas]))

    def dispay_func(self):
        sp.pprint(self.__objective_func())
        sp.pprint(self.__subject_to_func())
        sp.pprint(self.__lagrange_func())

    def dispay_diff_func(self):
        diff_w, diff_b = self.__diff_func()
        sp.pprint(diff_w)
        sp.pprint(diff_b)
    
    def display_kkts(self):
        alpha_st_kkts, alpha_kkts, st_kkts = self.__kkts()
        sp.pprint(alpha_st_kkts)
        sp.pprint(alpha_kkts)
        sp.pprint(st_kkts)
    
    def display_solve(self):
        sp.pprint(self.__solve())

def main():
    X = np.array([[3, 3], [4, 3], [1, 1]])
    y = np.array([1, 1, -1])
    svm = SVM(X, y)
    svm.dispay_func()
    svm.dispay_diff_func()
    svm.display_kkts()
    svm.display_solve()

if __name__ == "__main__":
    main()
    