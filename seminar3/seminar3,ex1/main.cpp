#include <cstdio>
#include <cstdarg>
#include <iostream>
#include "Math.h"


int main() {
    Math m;
    const char* W = "Proiectare";
    const char* V = "Orientata";
	printf("%d \n", m.Add(10,5));
    printf("%d \n", m.Add(10,5,1));
    printf("%d \n", m.Add(10.5,5.1));
    printf("%d \n", m.Add(10.5,5.1,2.2));
    printf("%d \n", m.Mul(10,5));
    printf("%d \n", m.Mul(10,5,2));
    printf("%d \n", m.Mul(10.5,5.2));
    printf("%d \n", m.Mul(10.3,5.1,3.2));
    printf("%d \n", m.Add(1,2,3));
    std::cout<< m.Add(W,V);
    
    return 0;
}