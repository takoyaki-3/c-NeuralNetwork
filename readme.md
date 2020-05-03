# C++ Neural Network

This repo is c++ Neural Network made with only c++ STL.

![](https://gyazo.com/dbc69790775131bcfdb18bf2c05c53a9.png)

## How to RUN

1. Download sample dataset

```
cd sample_date
./getdata.bat
```

2. Compile with Visual Studio and run it.

if you want to run hand iris breed estimation, you should change code.

#### HandwrittenNumbers.cpp

```cpp
/*   // add this code
#include "NeuralNetwork.h"
#include "loadcsv.h"

//#define MODE_USE_TRAINED_DATA
//#define MODE_OUTPUT_ON

void loadfile(string fname, vector<matrix>* inputs, vector<matrix>* outputs, int input_nodesize, int output_nodesize) {
```

#### IrisBreedEstimation.cpp

```cpp
///*      // add '//' into first
#include "NeuralNetwork.h"
#include "loadcsv.h"

//#define MODE_USE_TRAINED_DATA
//#define MODE_OUTPUT_ON

void loadfile(string fname, vector<matrix>* inputs, vector<matrix>* outputs, int input_nodesize, int output_nodesize) {
    {
```