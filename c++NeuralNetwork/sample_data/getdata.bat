curl https://raw.githubusercontent.com/pandas-dev/pandas/master/pandas/tests/data/iris.csv -o iris.csv
curl https://www.pjreddie.com/media/files/mnist_train.csv -o mnist_train.csv
curl https://www.pjreddie.com/media/files/mnist_test.csv -o mnist_test.csv
py split.py
