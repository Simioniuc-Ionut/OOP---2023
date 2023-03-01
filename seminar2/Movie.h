#pragma once

class Movie {
private:
	char name[256];
	int year;
	double score;
	int length;

public:
	void set_name(const char* name);
	void set_year(int year);
	void set_score(double score);
	void set_length(int length);
	const char* get_name();
	int get_year();
	double get_score();
	int get_length();
	int get_passed_years();
};