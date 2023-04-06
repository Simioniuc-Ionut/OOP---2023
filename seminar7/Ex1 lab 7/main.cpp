#include <iostream>
float operator""_Fahrenheit(unsigned long long int x) {
    return (x - 32) / 1.8;
}
float operator""_Kelvin(unsigned long long int x) {
    return x - 273.15;
}
    int main() {
    float a = 300_Kelvin;

    float b = 120_Fahrenheit;
    std::cout << a << " " << b;
    return 0;
}