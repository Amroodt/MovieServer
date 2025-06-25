#pragma once
#include <string>
#include <nlohmann/json.hpp>

class OMDbClient
{
private:

public:
    OMDbClient();
    int FetchMovieRatings();
};