#pragma once
#include "Movie.h"
class MovieSeries {
private:
	int count;
	Movie* filme[17];
public:
	void init();
	void add(Movie* filme);
	void sort();
	void print();
};