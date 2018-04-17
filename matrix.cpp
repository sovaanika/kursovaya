#include <vector>
#include <iostream>

using namespace std;

template < class T >
class Matrix{
protected:
    vector < vector < T > >  mtrx;
    unsigned int str_size;
    unsigned int column_size;
public:
    Matrix(unsigned int size_m = 0 , unsigned int size_n = 0){
        mtrx.resize(size_m);
        for(unsigned int i = 0; i < mtrx.size();i++)
            mtrx[i].resize(size_n);
        str_size = size_m;
        column_size = size_n;
    }
    Matrix(const Matrix& op){
        mtrx = op.mtrx;
        str_size = op.str_size;
        column_size = op.column_size;
    }
    unsigned int get_str_size() const {
        return str_size;
    }
    virtual unsigned int get_column_size() const {
        return column_size;
    }
    virtual void printmtrx(){
        for(unsigned int i = 0; i < mtrx.size();i++){
            for(unsigned int j = 0;j < mtrx[i].size();j++)
                cout << mtrx[i][j];
            cout << endl;
        }
    }
    T& operator()(unsigned int idx1 , unsigned int idx2){
        return mtrx[idx1][idx2];
    }
    bool operator==(const Matrix& op) const {
        return (mtrx == op.mtrx)? 1 : 0;
    }
    bool operator!=(const Matrix& op) const {
        return (mtrx == op.mtrx)? 0 : 1;
    }
    void operator=(const Matrix& op){
        mtrx = op.mtrx;
        str_size = op.str_size;
        column_size = op.column_size;
    }
    Matrix operator+(const Matrix &op) const {
        Matrix tmp;
        tmp.mtrx = mtrx;
        tmp.str_size = str_size;
        tmp.column_size = column_size;
        for(unsigned int i = 0; i < tmp.mtrx.size();i++)
            for(unsigned int j = 0;j < tmp.mtrx[i].size();j++)
                tmp.mtrx[i][j] += op.mtrx[i][j];
        return tmp;
    }
    Matrix operator-(const Matrix &op) const {
        Matrix tmp;
        tmp.mtrx = mtrx;
        tmp.str_size = str_size;
        tmp.column_size = column_size;
        for(int i = 0;i < tmp.mtrx.size();i++)
            for(int j = 0;j < tmp.mtrx.size();j++)
                tmp.mtrx[i][j] -= op.mtrx[i][j];
        return tmp;
    }
    Matrix operator*(const Matrix &op) const {
        Matrix tmp(mtrx.size(), op.mtrx[0].size());
            for(unsigned int i = 0;i < mtrx.size();i++)
                for(unsigned int j = 0;j < op.mtrx[0].size();j++)
                    for(unsigned int k = 0;k < op.mtrx.size();k++)
                        tmp.mtrx[i][j] += mtrx[i][k] * op.mtrx[k][j];
        return tmp;
    }
    template < class T1 > friend ostream& operator<<(ostream& output , const Matrix < T1 > &op);
    template < class T1 > friend istream& operator>>(istream& input , Matrix < T1 > &op);
};

/* input and output matrix */

template < class T >
ostream& operator<<(ostream &output , const Matrix < T > &op){
    for(unsigned int i = 0;i < op.get_str_size();i++){
        for(unsigned int j = 0;j < op.get_column_size();j++)
            cout << op.mtrx[i][j] << " ";
        cout << endl;
    }
    return output;
}


template < class T >
istream& operator>>(istream &input, Matrix < T > &op){
    for(unsigned int i = 0; i <  op.get_str_size();i++)
        for(unsigned int j = 0; j < op.get_column_size(); j++)
            input >> op(i,j);
    return input;
}


/*     It's additional functions for working with vectors    */


/* vector - vector
    Functions for addition and subtraction vectors;
*/

template < class T >
vector < T > operator+=(vector < T > &op1 , const vector < T > &op2){
    for(unsigned int i = 0; i < op1.size();i++)
        op1[i] += op2[i];
    return op1;
}
template < class T >
vector < T > operator-=(vector < T > &op1 , const vector < T > &op2){
    for(unsigned int i = 0; i < op1.size();i++){
        op1[i] -= op2[i];
    }
    return op1;
}
template < class T >
vector < T > operator+(const vector < T > &op1 , const vector < T > &op2){
    vector < T > tmp = op1;
    for(unsigned int i = 0; i < op1.size();i++){
        tmp[i] += op2[i];
    }
    return tmp;
}
template < class T >
vector < T > operator-(const vector < T > &op1 , const vector < T > &op2){
    vector < T > tmp = op1;
    for(unsigned int i = 0; i < op1.size();i++){
        tmp[i] -= op2[i];
    }
    return tmp;
}

/* vector - T , T - vector .
    Functions for multiplication
    and division vectors by numbers.
*/

template < class T >
vector < T > operator * (const vector < T > &op1 , const T &op2){
    vector < T > tmp = op1;
    for(unsigned int i = 0; i < op1.size();i++)
        tmp[i] *= op2;
    return tmp;
}
template < class T >
vector < T > operator * (const T &op1 , const vector < T > &op2){
    vector < T > tmp = op2;
    for(unsigned int i = 0; i < op2.size();i++)
        tmp[i] *= op1;
    return tmp;
}
template < class T >
vector < T > operator *=(vector < T > &op1, const T &op2){
    for(unsigned int i = 0; i < op1.size();i++)
        op1[i] *= op2;
    return op1;
}
template < class T >
vector < T > operator/(const vector < T > &op1, const T &op2){
    vector < T > tmp = op1;
    for(unsigned int i = 0;i < tmp.size();i++){
        tmp[i] /= op2;
    }
    return tmp;
}
template < class T >
vector < T > operator/=(vector < T >& op1 ,const T &op2){
    for(unsigned int i = 0;i < op1.size();i++){
        op1[i] /= op2;
    }
    return op1;
}

/* Input and output functions */

template < class T >
istream& operator>>(istream& input , vector < T > &op){
    for(int i = 0; i < op.size(); i++){
        input >> op[i];
    }
    return input;
}

template < class T >
ostream& operator<<(ostream& output , vector < T > &op){
    for(int i = 0; i < op.size();i++){
        output << op[i] << " ";
    }
    return output;
}
