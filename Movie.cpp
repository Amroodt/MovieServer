//
// Created by Joel Amroodt on 2025/06/22.
//

#include "Movie.h"

#include <iostream>

#include "OMDbClient.h"
#include <nlohmann/json.hpp>

#include "OMDbClient.h"
using json = nlohmann::json;


Movie::Movie()
    : title(" "), year(" "), genre(" "), release(" "), ratings(" "), f_ratings(" "),
      top_ten_list(""), comments("")

{
    int rating = fetchRating();
};

int Movie::fetchRating()
{
    return client.FetchMovieRatings();
}
std::string Movie::getTitle()
{
    std::cout << "\nTitle should go here" << std::endl;
    return title;

}


