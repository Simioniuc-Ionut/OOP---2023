#include "MovieSeries.h"
#include "Movie.h"
#include <cstdio>
void MovieSeries::init()
{
    this->count = 0;
}

void MovieSeries::add(Movie* film)
{
    this->filme[count] = film;
    this->count++;
}

void MovieSeries::sort()
{
    Movie* aux;
    for (int i = 1; i < count; i++)
    {
        for (int j = i; j < count; j++)
        {
            if (this->filme[i]->get_passed_years() > this->filme[j - 1]->get_passed_years())
            {
                aux = this->filme[i];
                this->filme[i] = this->filme[j - 1];
                this->filme[j - 1] = aux;
            }
        }
    }
}
void MovieSeries::print()
{
    for (int i = 0; i < this->count; i++)
    {
        printf(R"(
name        : %s
year        : %d
score       : %f
length      : %d
passed years: %d
)",
        this->filme[i]->get_name(),
        this->filme[i]->get_year(),
        this->filme[i]->get_score(),
        this->filme[i]->get_length(),
        this->filme[i]->get_passed_years(),'\n');
    }
}
