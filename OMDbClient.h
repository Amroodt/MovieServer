#pragma once
#include <string>
#include <nlohmann/json.hpp>

class OMDbClient
{
private:
    std::string jsonBody;


public:
    OMDbClient();
    int FetchMovieRatings();
    std::string get_jsonBody() const;
    std::string title, year, release, genre, ratings, f_ratings, comments, top_ten_list;


};