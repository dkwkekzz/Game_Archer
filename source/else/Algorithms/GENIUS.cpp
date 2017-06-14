#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, k, m;
int L[50], Q[10];
double T[50][50];
double C[50][5];

class Matrix {
public:
	int row, column;
	double matrix[50][50];
public:
	Matrix(int row, int column) {
		this->row = row;
		this->column = column;
		memset(matrix, 0, sizeof(matrix));
	}

};

class SquareMatrix : Matrix{
public:
	SquareMatrix(int n) : Matrix(n, n){
		for (int i = 0; i < n; i++)
			matrix[i][i] = 1;
	}
};

void genius2() {
	double c[1][3] = { {1, 0, 0} };
	double w[3][3], subW[4][3][3];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			subW[L[i]][i][j] = T[i][j];
	}
}

void genius() {
	C[0][0] = 1.0;
	C[1][0] = 0.0;
	C[2][0] = 0.0;

	for (int time = 1; time <= k; time++ ) {
		int realTime = time % 5;
		for (int i = 0; i < n; i++)
			C[i][realTime] = 0;

		for (int song = 0; song < n; song++) {
			if (time%L[song] == 0) {
				for (int nextSong = 0; nextSong < n; nextSong++) {
					C[nextSong][realTime] += C[song][(time - 1)%5] * T[song][nextSong];
				}
			}
			else {
				C[song][realTime] += C[song][(time - 1)%5];
			}
		}
		if (time == k) {
			for (int like = 0; like < m; like++)
				cout << C[Q[like]][realTime] << " ";
			cout << endl;
		}
	}
}

vector<double> getProb1() {
	double c[5][50];
	memset(c, 0, sizeof(c));
	c[0][0] = 1.0;
	for (int time = 1; time <= k; time++) {
		for (int song = 0; song < n; song++) {
			double &prob = c[time % 5][song];
			prob = 0;
			for (int last = 0; last < n; last++)
				prob += c[(time - L[last] + 5) % 5][last] * T[last][song];
		}
	}
	vector<double> ret(n);
	for (int song = 0; song < n; song++) {
		for (int start = k - L[song] + 1; start <= k; start++)
			ret[song] += c[start % 5][song];
	}
	return ret;
}

/*class SquareMatrix {
public:
	int n;
	double matrix[200][200];
	SquareMatrix(int n) {
		memset(matrix, 0, sizeof(matrix));
		this->n = n;
		for (int i = 0; i < n; i++) {
			matrix[i][i] = 1;
		}
	}
	void AddElement(int i, int j, double k) {
		matrix[i][j] += k;
	}
	SquareMatrix multiply(const SquareMatrix &m) {
		SquareMatrix newMatrix(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					newMatrix.AddElement(i, j, matrix[i][k] * m[k][j]);
		return newMatrix;
	}
	SquareMatrix pow(int m) {
		if (m == 0) return *this;
		if (m % 2 == 1) return this->multiply(pow(m-1));
		SquareMatrix half = pow(m / 2);
		return half.multiply(half);
	}
};

vector<double> getProb2() {
	SquareMatrix w(4*n);
	for (int i = 0; i < 3 * n; i++)
		w[i][i + n] = 1.0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			w[3 * n + i][(4 - L[j])*n + j] = T[j][i];
	SquareMatrix wk = w.pow(k);
	vector<double> ret(n);
	for (int song = 0; song < n; song++) {
		for (int start = 0; start < L[song]; start++)
			ret[song] += wk[(3 - start)*n + song][3 * n];
	}
	return ret;
}*/


int main() {
	cin >> n >> k >> m;
	for (int i = 0; i < n; i++)
		cin >> L[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> T[i][j];
	for (int i = 0; i < m; i++)
		cin >> Q[i];

	//genius();
	for (int i = 0; i < n; i++)
		cout << getProb1()[i] << " ";
	cout << endl;
}