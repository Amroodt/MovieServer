#pragma once
#include <string>


class Movie
{
private:
    std::string title, year, release, genre;
public:
    std::string getTitle();
    std::string getYear();
    std::string getRelease();
    std::string getGenre();



};
