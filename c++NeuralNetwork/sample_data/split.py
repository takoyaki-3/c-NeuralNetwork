import pandas as pd
import numpy as np

df = pd.read_csv('iris.csv')
df = df.sample(frac=1)

df = df.replace('Iris-setosa', '0')
df = df.replace('Iris-versicolor', '1')
df = df.replace('Iris-virginica', '2')

df.insert(0, 'IrisName', df['Name'])

ratio = 0.7
p = int(ratio * len(df))
df1 = df.iloc[:p, :]
df2 = df.iloc[p:, :]

df1.to_csv("iris_train.csv", index=False, header=None)
df2.to_csv("iris_test.csv", index=False, header=None)