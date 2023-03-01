#include "Movie.h"
#define _CRT_SECURE_NO_WARNINGS
#include"cstring"
void Movie::set_name(const char* name)
{
	strcpy(this->name, name);
}

void Movie::set_year(int year)
{
	this->year = year;
}

void Movie::set_score(double score)
{
	if (!(score >= 1 && score <= 10)) {
		return;
	}
	this->score = score;
}

void Movie::set_length(int length)
{
	this->length = length;
}

const char* Movie::get_name()
{
	return name;
}

int Movie::get_year()
{
	return year;
}

double Movie::get_score()
{
	return score;
}

int Movie::get_length()
{
	return length;
}

int Movie::get_passed_years()
{	
	return 2023 - year;
}
