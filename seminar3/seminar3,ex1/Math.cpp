#define _CRT_SECURE_NO_WARNINGS
#include "Math.h"
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <cstring>
int Math::Add(int a, int b) {
    return a+b;
}

int Math::Add(int a, int b, int c) {
    return a+b+c;
}

int Math::Add(double a, double b) {
    return a+b;
}

int Math::Add(double a, double b, double c) {
    return a+b+c;
}

int Math::Mul(int a, int b) {
    return a*b;
}

int Math::Mul(int a, int b, int c) {
    return a*b*c;
}

int Math::Mul(double a, double b) {
    return a*b;
}

int Math::Mul(double a, double b, double c) {
    return a*b*c;
}

int Math::Add(int count, ...) {
    int sum = 0;
    std::va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);
        sum += num;
    }
    va_end(args);
    return sum;
}

char* Math::Add(const char* a, const char* b) {
    char* concat= new char;
    if (a == nullptr || b == nullptr)
        return nullptr;
    else {
        strcpy(concat, a);
        strcat(concat, b);
        return concat;
        delete concat;
    }
 
}
