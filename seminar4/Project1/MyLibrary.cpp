#define _CRT_VA_START
#define _CRT_SECURE_NO_WARNINGS
#include "MyLibrary.h"
#include <cstring>
#include <stdio.h>
#include <string>
#include <cstdarg>
#include <time.h>
#include <iostream>
#include <fstream>
#include <random>

MyLibrary::MyLibrary(std::ostream& output_stream) : output_stream(output_stream), books_count(0) {
    this->books = nullptr;
}
MyLibrary::MyLibrary(const MyLibrary& other) : output_stream(other.output_stream), books_count(other.books_count) {
         books = new int;
        *books = *other.books;
}
MyLibrary::MyLibrary(std::ostream& output_stream, unsigned books_count, int* books)
    : output_stream(output_stream), books_count(books_count) {
    this->books = new int[books_count];
    for (int i=0; i<books_count;i++) {
        this->books[i] = books[i];
    }
}

MyLibrary::MyLibrary(std::ostream& output_stream, unsigned books_count, int min, int max)
    : output_stream(output_stream), books_count(books_count) { 
   // alocam spatiu pentru vectorul de id-uri
    this->books = new int[books_count];
   srand(time(NULL));
   for (int i=0; i<books_count; ++i) {
        books[i] = min + (rand() % (max - min + 1));
   }
}
MyLibrary::MyLibrary(std::ostream& output_stream, const char* books_values)
    : output_stream(output_stream), books_count(0) {
    // alocam spatiu pentru vectorul de id-uri
    this->books = new int[500];
    const char* idul;
    int nr;
    char chr[300];
    strcpy(chr, books_values);
    idul = strtok(chr,";");
    while (idul != NULL) {
        nr = std::stoi(idul);
        this->books[this->books_count] = nr;
        this->books_count++;
        idul = strtok(NULL, ";");
    }
}
MyLibrary::MyLibrary(std::ostream& output_stream, unsigned books_count, ...)
    : output_stream(output_stream), books_count(books_count) {
    // alocam spatiu pentru vectorul de id-uri
    this->books = new int[books_count];
    va_list args;
    va_start(args, books_count);
    for (int i=0; i<books_count; ++i) {
        int value = va_arg(args, int);
        books[i] = value;
    }
    va_end(args);
}
MyLibrary::MyLibrary(std::initializer_list<int> v) : output_stream(std::cout), books_count() {
     this->books = new int[this->books_count];
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        this->books[i] = *it;
        ++i;
    }
    this->books_count = i;
}
MyLibrary::~MyLibrary() {
    delete[] books;
}