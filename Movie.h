#pragma once
#include <string>
#include "OMDbClient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Movie
{
private:
    OMDbClient client;
    int fetchRating();
    auto parseJson();
    std::string title, year, release, genre, ratings, f_ratings, comments, top_ten_list, poster;



public:
    Movie(); //Constructor Declaration

    std::string getTitle();
    std::string getYear();
    std::string getRelease();
    std::string getGenre();
    std::string getPoster();





};
