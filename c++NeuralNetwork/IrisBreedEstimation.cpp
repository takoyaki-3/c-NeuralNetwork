/*
#include "NeuralNetwork.h"
#include "loadcsv.h"

//#define MODE_USE_TRAINED_DATA
//#define MODE_OUTPUT_ON

void loadfile(string fname, vector<matrix>* inputs, vector<matrix>* outputs, int input_nodesize, int output_nodesize) {
    {
        // Load file
        mycsv csv(fname);
        while (!csv.eof())
        {
            vector<string> cells = csv.loadnextline();
            if (cells.size() < input_nodesize + 1) continue;

            matrix input(input_nodesize, 1), output(output_nodesize, 1);
            for (int i = 0; i < input_nodesize; i++) {
                input.put(i, 0, atof(cells[i + 1].c_str()));
            }
            //      input.scalar_division(255.0f);
            //      input.scalar(0.999f);

            output.scalar_plus(ZERO);
            output.put(atoi(cells[0].c_str()), 0, ONE);
            inputs->push_back(input);
            outputs->push_back(output);
        }
    }
    cout << "aa";
}

int main() {

    // Setting neural network
    NeuralNetwork nn;
    nn.input_nodes = 4;
    nn.hidden_nodes = 84;
    nn.hidden_layer = 1;
    nn.output_nodes = 3;
    int epochs = 200;

    vector<matrix> inputs;
    vector<matrix> outputs;

    nn.init();

    // Load or training network 
#ifdef MODE_USE_TRAINED_DATA
    nn.load("w");
#else
    loadfile("./sample_data/iris_train.csv", &inputs, &outputs, nn.input_nodes, nn.output_nodes);
    cout << "Start training" << endl;
    for (int i = 0; i < epochs; i++) {
        cout << "epoch: " << i << endl;
        for (int j = 0; j < inputs.size(); j++) {
            nn.train(&inputs[j], &outputs[j], 0.01);
        }
    }
    cout << "Training Done !" << endl;
    nn.save("w");
    cout << "Saved." << endl;
#endif

    // Test network
    inputs.clear();
    outputs.clear();

    loadfile("./sample_data/iris_test.csv", &inputs, &outputs, nn.input_nodes, nn.output_nodes);

    int cou = 0;
    int sum = 0;
    for (int j = 0; j < inputs.size(); j++) {
        int ans = 0;
        for (int i = 1; i < nn.output_nodes; i++) {
            if (outputs[j].get(i, 0) > outputs[j].get(ans, 0)) ans = i;
        }

        nn.query(&inputs[j], &outputs[j]);
        int mindex = 0;
        for (int i = 1; i < nn.output_nodes; i++) {
            if (outputs[j].get(i, 0) > outputs[j].get(mindex, 0)) mindex = i;
        }
#ifdef MODE_OUTPUT_ON
        outputs[j].output();
        cout << "Answer:" << ans << endl;
        if (ans == mindex) cout << "success" << endl;
        else cout << "failed" << endl;
#endif
        if (ans == mindex) cou++;
        sum++;
    }
    cout << "Correct answerF" << cou << endl;
    cout << "Fialed answerF" << sum - cou << endl;
    cout << "Success rateF" << (float)cou / (float)(sum) << endl;
}
//*/