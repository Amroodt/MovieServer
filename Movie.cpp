//
// Created by Joel Amroodt on 2025/06/22.
//

#include "Movie.h"
#include <nlohmann/json.hpp>

#include "OMDbClient.h"
using json = nlohmann::json;


Movie::Movie()
    : title(" "), year(" "), genre(" "), release(" ")
{
    //nothing here
};
