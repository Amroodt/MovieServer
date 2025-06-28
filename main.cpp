

#include "Movie.h"
#include "OMDbClient.h"
#include <iostream>

int main()
{
    Movie movie;
    std::cout << "" << movie.getTitle();
    std::cout << "\n" << movie.getYear();
    std::cout << "\n" << movie.getRelease();
    std::cout << "\n" << movie.getGenre();
    std::cout << "\n" << movie.getPoster();

    // OMDbClient client;
    // return client.FetchMovieRatings();

return 0;
}
