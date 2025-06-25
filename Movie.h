#pragma once
#include <string>
#include "OMDbClient.h"


class Movie
{
private:
    std::string title, year, release, genre, ratings, f_ratings, comments, top_ten_list;
    OMDbClient client;
    int fetchRating();

public:
    Movie(); //Constructor Declaration

    std::string getTitle();
    std::string getYear();
    std::string getRelease();
    std::string getGenre();



};
