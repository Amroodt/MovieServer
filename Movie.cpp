//
// Created by Joel Amroodt on 2025/06/22.
//

#include "Movie.h"

#include <iostream>

#include "OMDbClient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json j;

Movie::Movie()
    : title(" "), year(" "), genre(" "), release(" "), ratings(" "), f_ratings(" "),
      top_ten_list(""), comments(""), poster("")

{
    int rating = fetchRating();
};

int Movie::fetchRating()
{
    //return client.FetchMovieRatings();
    return client.FetchMovieRatings();
}
std::string Movie::getTitle()
{
    std::string rawJson = client.get_jsonBody();
    json j = json::parse(rawJson);
    title = j.at("Title").get_to(rawJson);

    return title;
}
std::string Movie::getYear()
{
    std::string rawJson = client.get_jsonBody();
    json j = json::parse(rawJson);
    year = j.at("Year").get_to(rawJson);

    return year;
}
std::string Movie::getRelease()
{
    std::string rawJson = client.get_jsonBody();
    json j = json::parse(rawJson);
    release = j.at("Released").get_to(rawJson);

    return release;
}
std::string Movie::getGenre()
{
    std::string rawJson = client.get_jsonBody();
    json j = json::parse(rawJson);
    genre = j.at("Genre").get_to(rawJson);

    return genre;
}
std::string Movie::getPoster()
{
    std::string rawJson = client.get_jsonBody();
    json j = json::parse(rawJson);
    poster = j.at("Poster").get_to(rawJson);

    return poster;
}



