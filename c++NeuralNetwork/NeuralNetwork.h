#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <cmath>
#include "Matrix.h"

using namespace std;

class NeuralNetwork {
public:
	int input_nodes;
	int hidden_nodes;
	int output_nodes;
	int hidden_layer;

	vector<matrix> w;
	matrix wo;

	void save(string fname) {
		FILE* fp = fopen(fname.c_str(), "wb");
		fwrite(&input_nodes, sizeof(int), 1, fp);
		fwrite(&hidden_nodes, sizeof(int), 1, fp);
		fwrite(&output_nodes, sizeof(int), 1, fp);
		fwrite(&hidden_layer, sizeof(int), 1, fp);
		for (int i = 0; i < w.size(); i++) {
			fwrite(&w[i].n, sizeof(int), 1, fp);
			fwrite(&w[i].m, sizeof(int), 1, fp);
			fwrite(w[i].mat, sizeof(matrixelement), w[i].n * w[i].m, fp);
		}
		fwrite(&wo.n, sizeof(int), 1, fp);
		fwrite(&wo.m, sizeof(int), 1, fp);
		fwrite(wo.mat, sizeof(matrixelement), wo.n * wo.m, fp);
		fclose(fp);
	}
	void load(string fname) {
		FILE* fp = fopen(fname.c_str(), "rb");
		fread(&input_nodes, sizeof(int), 1, fp);
		fread(&hidden_nodes, sizeof(int), 1, fp);
		fread(&output_nodes, sizeof(int), 1, fp);
		fread(&hidden_layer, sizeof(int), 1, fp);
		for (int i = 0; i < hidden_layer; i++) {
			w.push_back(matrix());
			fread(&w[i].n, sizeof(int), 1, fp);
			fread(&w[i].m, sizeof(int), 1, fp);
			w[i].newmat(w[i].n, w[i].m);
			fread(w[i].mat, sizeof(matrixelement), w[i].n * w[i].m, fp);
		}
		fread(&wo.n, sizeof(int), 1, fp);
		fread(&wo.m, sizeof(int), 1, fp);
		wo.newmat(wo.n, wo.m);
		fread(wo.mat, sizeof(matrixelement), wo.n * wo.m, fp);
	}
	void init() {
		int bef = input_nodes;
		for (int k = 0; k < hidden_layer; k++) {
			w.push_back(matrix());
			w[k].newmat(hidden_nodes, bef);
			bef = hidden_nodes;
			w[k].random_m05to05();
		}
		wo.newmat(output_nodes, hidden_nodes);
		wo.random_m05to05();
	}
	void train(matrix* input, matrix* ans, float rate) {
		matrix final_outputs;
		vector<matrix> hidden_inputs;
		vector<matrix> hidden_outputs;
		hidden_inputs.push_back(matrix());
		hidden_inputs[0].copy(input);
		for (int i = 0; i < w.size(); i++) {
			hidden_outputs.push_back(matrix());
			hidden_outputs[i].dot(w[i], hidden_inputs[i]);
			hidden_outputs[i].sigmoid();
			hidden_inputs.push_back(matrix());
			hidden_inputs[i + 1].copy(&hidden_outputs[i]);
		}
		final_outputs.dot(wo, hidden_inputs[w.size()]);
		final_outputs.sigmoid();

		matrix output_errors(ans);
		output_errors.minus(final_outputs);

		output_errors.multiplication(&final_outputs);
		matrix s(ans->n, ans->m), t, u;
		s.scalar_plus(1.0f);
		s.minus(final_outputs);
		output_errors.multiplication(&s);
		t.t_set(&hidden_outputs[w.size() - 1]);
		u.dot(output_errors, t);

		final_outputs.clear();
		s.clear();

		wo.plus(u);
		t.clear();
		u.clear();

		// Backpropagation
		for (int i = w.size() - 1; i >= 0; i--) {
			matrix hidden_errors;
			matrix wt;
			wt.t_set(&w[i]);
			hidden_errors.dot(wt, output_errors);
			output_errors.copy(&hidden_errors);

			matrix as(hidden_errors.n, hidden_errors.m);
			as.scalar_plus(1.0f);
			as.minus(hidden_outputs[i]);
			matrix at(&hidden_errors);
			at.multiplication(&hidden_outputs[i]);
			at.multiplication(&as);
			matrix au;
			au.t_set(&hidden_inputs[i]);
			matrix av;
			av.dot(au, av);
			av.scalar(rate);

			w[i].plus(av);
			wt.clear();
			as.clear();
			at.clear();
			au.clear();
			av.clear();
		}

		for (int i = 0; i < w.size(); i++) {
			hidden_inputs[i].clear();
			hidden_outputs[i].clear();
		}
		hidden_inputs[w.size()].clear();
		output_errors.clear();
	}
	void query(matrix* input, matrix* output) {
		matrix x(input);
		for (int i = 0; i < w.size(); i++) {
			matrix o;
			o.dot(w[i], x);
			o.sigmoid();
			x.copy(&o);
			o.clear();
		}
		output->dot(wo, x);
		output->sigmoid();
		x.clear();
	}
};

#endif // !NEURALNETWORK_H
