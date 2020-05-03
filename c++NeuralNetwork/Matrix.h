#ifndef MATRIX_H
#define MATRIX_H

#include <cstdio>
#include <random>
#include <cmath>
#include <iostream>

using namespace std;

typedef float matrixelement;

const float ZERO = 0.00001f;
const float ONE = 0.99999f;
const int RAND = 1 << 20;

float sigmoidfunction(float x) {
	return 1 / (1 + expf(-x));
}

class matrix {
private:
public:
	// Matrix body
	matrixelement* mat;

	// Matrix size
	int n, m;

	// Init matrix
	matrix() {
		n = m = 1;
		mat = new matrixelement[n * m];
		memset(mat, 0, sizeof(matrixelement) * n * m);
	}
	matrix(int nn, int mm) {
		mat = new matrixelement[nn * mm];
		memset(mat, 0, sizeof(matrixelement) * nn * mm);
		n = nn;
		m = mm;
	}
	matrix(matrix* a) {
		mat = new matrixelement[a->n * a->m];
		n = a->n;
		m = a->m;
		memcpy(mat, a->mat, m * n * sizeof(matrixelement));
	}
	void newmat(int nn, int mm) {
		n = nn;
		m = mm;
		mat = new matrixelement[n * m];
		memset(mat, 0, sizeof(matrixelement) * n * m);
	}
	void copy(matrix* a) {
		n = a->n;
		m = a->m;
		delete[] mat;
		mat = new matrixelement[a->n * a->m];
		memcpy(mat, a->mat, m * n * sizeof(matrixelement));
	}
	void put(int i, int j, matrixelement e) {
		if (i >= n || j >= m || i < 0 || j < 0) return;
		mat[i * m + j] = e;
	}
	matrixelement get(int i, int j) {
		if (i >= n || j >= m || i < 0 || j < 0) return -1;
		return mat[i * m + j];
	}
	void random_m05to05() {
		std::random_device rnd;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] = (matrixelement)(rnd() % RAND) / (matrixelement)RAND - 0.5f;
	}
	bool plus(matrix a) {
		if (a.n != n || a.m != m) return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] += a.mat[i * m + j];
		return true;
	}
	bool minus(matrix a) {
		if (a.n != n || a.m != m) return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] -= a.mat[i * m + j];
		return true;
	}
	bool dot(matrix a, matrix b) {
		if (a.m != b.n) return false;
		n = a.n;
		m = b.m;
		delete[] mat;
		mat = new matrixelement[n * m];
		memset(mat, 0, sizeof(matrixelement) * n * m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < a.m; k++) {
					put(i, j, get(i, j) + a.get(i, k) * b.get(k, j));
				}
			}
		}
		return true;
	}
	void output() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("[%f]	", get(i, j));
			}
			cout << "\n";
		}
		cout << "\n";
	}
	void sigmoid() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] = sigmoidfunction(mat[i * m + j]);
	}
	void t_set(matrix* a) {
		n = a->m;
		m = a->n;
		delete[] mat;
		mat = new matrixelement[n * m];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] = a->mat[j * a->m + i];
	}
	void scalar(matrixelement k) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] *= k;
	}
	void scalar_plus(matrixelement k) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] += k;
	}
	void scalar_division(matrixelement k) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] /= k;
	}
	bool multiplication(matrix* a) {
		if (n != a->n) return false;
		if (m != a->m) return false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				mat[i * m + j] *= a->mat[i * m + j];
	}
	void clear() {
		delete[] mat;
	}
};

#endif // !MATRIX_H
