import numpy as np
import argparse

class WeakClassifier:
    def __init__(self):
        self.feature_index = None
        self.feature_value = None
        self.threshold_type = None
        self.alpha = None


class Adaboost:
    def __init__(self, ncls):
        self.ncls = ncls
        # the weakclassifier list
        self.classifiers = list()

    def fit(self, X, y):
        """training of model"""
        num_sample, num_feature = X.shape
        weights = np.ones(num_sample) / num_sample
        print(weights, num_feature)

    def predict(self, x):
        """predicting of model"""
        pass

def main():
    parser = argparse.ArgumentParser(description="Adaboost algorithm")
    parser.add_argument("--ncls", type=int, default=300, help="the number of weakclassifiers")


if __name__ == "__main__":
    main()