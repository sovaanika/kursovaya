// gauss.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "complex.cpp"
#include "matrix.cpp"

using namespace std;

class Sole : public Matrix < Complex > {
	void set_last_column() {
		cout << "Enter " << str_size << " complex numbers" << endl;
		for (unsigned int i = 0; i < get_str_size(); i++)
			cin >> mtrx[i][column_size];
	}
public:
	Sole(unsigned int size_m = 0, unsigned int size_n = 0) :Matrix(size_m, size_n) {
		for (unsigned int i = 0;i < mtrx.size();i++)
			mtrx[i].push_back(0);
	}
	Complex& operator()(unsigned int idx1, unsigned int idx2) {
		return mtrx[idx1][idx2];
	}
	void printmtrx() {
		for (unsigned int i = 0; i < mtrx.size();i++) {
			for (unsigned int j = 0;j < mtrx[i].size();j++)
				cout << mtrx[i][j];
			cout << endl;
		}
	}
	void printansw() {
		for (unsigned int i = 0; i < mtrx.size();i++) {
			cout << "x" << i << "= " << mtrx[i][column_size] << endl;
		}
	}
	void straightstep() {
		set_last_column();
		printmtrx();
		Complex b(0, 0);
		for (unsigned int i = 0;i < column_size /*&& i < str_size*/;i++) {
			unsigned int k = i;
			unsigned int tmp = k;
			while (k < str_size - 1 && mtrx[k][i] == b) {
				k++;
			}
			if (k != i) {
				vector <Complex> tmp = mtrx[i];
				mtrx[i] = mtrx[k];
				mtrx[k] = tmp;
			}
			for (k = i;k < str_size;k++) {
				if (mtrx[k][i] != b) {
					for (unsigned int j = column_size + 1;j > i;j--) {
						if (mtrx[k][j - 1] != b) {
							mtrx[k][j - 1] = mtrx[k][j - 1] / mtrx[k][i];
						}
					}
					//mtrx[k] = mtrx[k] / mtrx[k][i];
				}
			}
			for (k = i + 1;k < str_size;k++) {
				if (mtrx[k][i] != b) {
					mtrx[k] -= mtrx[i];
				}
			}
		}
	}
	void reversestep() {
		Complex b(0, 0);
		unsigned int t = column_size;
		unsigned int k = str_size - 1;
		for (unsigned int i = k;i > 0;i--) {
			unsigned int h = t - 1;
			for (unsigned int j = k;(j > i - 1);j--) {
				mtrx[i - 1][t] = mtrx[i - 1][t] - (mtrx[j][t] * mtrx[i - 1][h]);
				mtrx[i - 1][h] = b;
				h--;
			}
		}
		printansw();
	}
	void gauss() {
		Complex b(0, 0);
		Complex d(1, 0);
		straightstep();
		for (unsigned int n = 0;n < str_size;n++) {
			int m = n;
			for (unsigned int j = 0;j < column_size;j++) {
				if (mtrx[n][j] == b) {
					m++;
				}
			}
			if (m == column_size - 1 && mtrx[n][column_size] != b) {
				cout << "System hasn't got any solution" << endl;
				return;
			}
		}
		int t = 0;
		for (unsigned int i = 0;i < str_size;i++) {
			if (mtrx[i][column_size] == 0) { t++; }
		}
		if (t == str_size) {
			for (unsigned int l = str_size;l > 0;l--) {
				int m = 0;
				unsigned int o;
				for (unsigned int j = 0;j < column_size;j++) {
					if (mtrx[l - 1][j] != b) {
						if (m == 0) { o = j; }
						m++;
					}
				}
				if (m == 1) {
					for (unsigned int i = 0;i < str_size;i++) {
						mtrx[i][o] = b;
					}
					cout << "x" << l - 1 << "-any complex number" << endl;
				}
				if (m > 1) {
					cout << "x" << o << "=";
					int x = 0;
					for (unsigned int d = o + 1;d < column_size;d++) {
						if (mtrx[l - 1][d] != b) {
							if (x > 0) { cout << "+"; }
							cout << (-1)*mtrx[l - 1][d] << "*x" << d;
							x++;
						}
					}
					cout << endl;
					for (unsigned int i = 0;i < str_size;i++) {
						mtrx[i] = mtrx[i] - mtrx[l - 1] * mtrx[i][o];
					}
				}
			}
		}
		else {
			reversestep();
		}
		printmtrx();
		cout << "res1=" << -2 * 3.18217 - 9 * 1.54651 - 3 * (-0.418605) + 7 * (-0.996124) << endl;
		cout << "res2=" << -7 * 3.18217 + 2 * 1.54651 + 2 * (-0.418605) + 5 * (-0.996124) << endl;
		cout << "res3=" << -6 * 3.18217 +2 * 1.54651 - 0 * (-0.418605) + 0 * (-0.996124) << endl;
		cout << "res4=" << 0 * 3.18217 - 3 * 1.54651 + 8 * (-0.418605) - 3 * (-0.996124) << endl;
	}
	friend ostream& operator<<(ostream&, const Sole&);
	friend istream& operator >> (istream&, Sole&);
};

ostream& operator<<(ostream &output, const Sole &op) {
	for (unsigned int i = 0;i < op.get_str_size();i++) {
		for (unsigned int j = 0;j < op.get_column_size();j++)
			cout << op.mtrx[i][j] << " ";
		cout << endl;
	}
	return output;
}

istream& operator >> (istream &input, Sole &op) {
	for (unsigned int i = 0; i < op.get_str_size();i++)
		for (unsigned int j = 0; j < op.get_column_size(); j++)
			input >> op(i, j);
	return input;
}

/* Input matrix from file, input last column from stdin */

int main() {
	ifstream input("input.txt");
	if (!input) {
		cout << "File does not exist" << endl;
		return 0;
	}

	unsigned int m;
	unsigned int n;
	input >> m;
	input >> n;
	if (m == 0 || n == 0) {
		cout << "Wrong size of matrix" << endl;
		return 0;
	}
	Sole a(m, n);
	input >> a;
	a.gauss();
	return 0;
}
