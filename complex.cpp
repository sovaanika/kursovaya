#include <iostream>

using namespace std;

class Complex{
    double re,im;
    public:
    Complex(double re = 0, double im = 0){
        Complex::re = re;
        Complex::im = im;
    }

    double get_abs2() const {
        return (re * re + im * im);
    }

    friend Complex operator+(const Complex&, const Complex&);
    friend Complex operator-(const Complex&, const Complex&);
    friend Complex operator*(const Complex&, const Complex&);
    friend Complex operator/(const Complex&, const Complex&);
    friend Complex operator+=(Complex&, const Complex&);
    friend Complex operator-=(Complex&, const Complex&);
    friend Complex operator*=(Complex&, const Complex&);
    friend Complex operator/=(Complex&, const Complex&);
    friend bool operator==(const Complex&, const Complex&);
    friend bool operator!=(const Complex& ,const Complex&);
    friend istream& operator>>(istream& ,Complex&);
    friend ostream& operator<<(ostream&, const Complex&);
};

bool operator==(const Complex& op1, const Complex& op2){
	return((op1.re == op2.re) && (op1.im == op2.im));
}
bool operator!=(const Complex& op1, const Complex& op2){
	return((op1.re != op2.re) || (op1.im != op2.im));
}
Complex operator+(const Complex& op1, const Complex& op2){
    return Complex(op1.re + op2.re , op1.im + op2.im);
}
Complex operator-(const Complex& op1, const Complex& op2){
    return Complex(op1.re - op2.re , op1.im - op2.im);
}
Complex operator*(const Complex& op1, const Complex& op2){
    return Complex(op1.re * op2.re - op1.im * op2.im , op1.re * op2.im + op2.re  * op1.im);
}
Complex operator/(const Complex& op1, const Complex& op2){
    return Complex((op1.re * op2.re + op1.im * op2.im )/ op2.get_abs2() ,
                   (op1.im * op2.re - op1.re * op2.im ) / op2.get_abs2());
}
Complex operator+=(Complex& op1, const Complex& op2){
    return Complex(op1.re += op2.re , op1.im += op2.im);
}
Complex operator-=(Complex& op1, const Complex& op2){
    return Complex(op1.re -= op2.re , op1.im -= op2.im);
}
Complex operator*=(Complex& op1, const Complex& op2){
    double new_re = op1.re * op2.re - op1.im * op2.im;
    double new_im = op1.re * op2.im + op2.re  * op1.im;
    op1.re = new_re;
    op1.im = new_im;
    return Complex (op1.re, op1.im);

}
Complex operator/=(Complex& op1, const Complex& op2){
    double new_re = (op1.re * op2.re + op1.im * op2.im) / op2.get_abs2();
    double new_im = (op1.im * op2.re - op1.re * op2.im) / op2.get_abs2();
    op1.re = new_re;
    op1.im = new_im;
    return Complex(op1.re , op1.im);
}

istream& operator>>(istream& input, Complex &op){
    input >> op.re >> op.im;
    return input;
}

ostream& operator<<(ostream& output, const Complex &op){
    output << "( " <<  op.re << " " << op.im << " )" ;
    return output;
}
