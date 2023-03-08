#pragma once
#include <cstdio>

class Canvas {
    int inaltime=10 , latime=50 ;
    char mat[12][52];
  public:
    // contructor will call the clear method
    Canvas(int lines, int columns);

    // set the character at the position x and y to value
    void set_pixel(int x, int y, char value);

    // tuples of x, y, value
    void set_pixels(int count, ...);

    void clear();

    void print() const;
};