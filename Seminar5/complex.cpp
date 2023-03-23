#include "complex.h"

Complex::Complex() : Complex(0, 0) {
}

Complex::Complex(double real, double imag) {
    real_data = real;
    imag_data = imag;
}
bool Complex::is_real() const {
    return imag() == 0;
}

double Complex::real() const {
    return real_data;
}

double Complex::imag() const {
    return imag_data;
}

double Complex::abs() const {
    return sqrt(real() * real() + imag() * imag());
}

Complex Complex::conjugate() const {
    return { real(), -imag() };
}

Complex& Complex::operator()(double real, double imag) {
    real_data = real;
    imag_data = imag;
    return *this;
}

Complex& Complex::operator++() {
    this->real_data++;
    return *(this);
}

Complex Complex::operator++(int) {
    Complex tmp(*this);
    operator++();
    return tmp;
}

Complex& Complex::operator--() {
    this->real_data--;
    return *this;
}

Complex Complex::operator--(int) {
    Complex tmp(*this);
    operator--();
    return tmp;
}

Complex operator+(const Complex& l, const Complex& r) {
        auto a = l.imag() + r.imag();
        auto b = l.real() + r.real();
        Complex result(b, a);
        return result;
}

Complex operator+(const Complex& l, double r) {
    Complex result(0,r);
    auto a = l.real() + r;
    auto b = l.imag();
    return result(a,b);
}

Complex operator+(double l, const Complex& r) {
    Complex result(l, 0);
    auto a = l + r.real();
    auto b = r.imag();
    return result(a, b);
}

Complex operator-(const Complex& l, const Complex& r) {
    auto a = l.imag() - r.imag();
    auto b = l.real() - r.real();
    Complex result(b, a);
    return result;
}

Complex operator-(const Complex& l, double r) {
    Complex result(r, 0);
    auto a = l.real() - r;
    auto b = l.imag();
    return result(a, b);
}

Complex operator-(double l, const Complex& r) {
    Complex result(l, 0);
    auto a = l - r.real();
    auto b = r.imag();
    return result(a, b);
}

Complex operator-(const Complex& obj) {
   
    return Complex(-obj.real(),-obj.imag());
}

Complex operator*(const Complex& l, const Complex& r) {
    auto a = (l.real() * r.real() - l.imag() * r.imag());
    auto b = (l.real() * r.imag() + l.imag() * r.real());
    Complex result(a, b);
    return result;
}

Complex operator*(double l, const Complex& r) {
    Complex result(l, 0);
    auto a = l * r.real();
    auto b = r.imag();
    return result(a, b);
}

Complex operator*(const Complex& l, double r) {
    Complex result(r, 0);
    auto a = l.real() * r;
    auto b = l.imag();
    return result(a, b);
}

bool operator==(const Complex& l, const Complex& r) {
    if ((l.real() == r.real()) && (l.imag() == r.imag()))
        return true;
    return false;
}

bool operator!=(const Complex& l, const Complex& r) {
    if ((l.real() != r.real()) || (l.imag() != r.imag()))
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, const Complex& complex) {
    if (complex.is_real()) {
        out << complex.real();
    } else 
    { 
        out << complex.real() << (complex.imag() < 0 ? "" : "+") << complex.imag() << "i";
    }
    return out;
}
