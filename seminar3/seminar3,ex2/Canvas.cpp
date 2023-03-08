#include "Canvas.h"
#include <cstdio>
#include <cstdarg>
#include <iostream>

Canvas::Canvas(int lines, int columns){
    clear();
    this->inaltime = lines;
    this->latime = columns;
}

void Canvas::set_pixel(int x, int y, char value){
    this->mat[x][y] = value;
}

void Canvas::set_pixels(int count, ...){
    std::va_list args;
    va_start(args,count);
    for (int i = 0; i < count; i++) {
        int x = va_arg(args, int);
        int y = va_arg(args, int);
        char value = va_arg(args, char);
        set_pixel(x, y, value);
    }
    va_end(args);
}

void Canvas::clear(){
    for (int i = 0; i < this->inaltime; i++) 
        for (int j = 0; j < this->latime; j++)
           this->mat[i][j] = ' ';
    }

void Canvas::print() const{
    for (int i = 0; i < this->inaltime; i++) {
        for (int j = 0; j < this->latime; j++) {
            printf("%c", this->mat[i][j]);
        }
        printf("\n");
    }
}
