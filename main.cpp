

#include "Movie.h"
#include "OMDbClient.h"

int main()
{
    OMDbClient client;
    return client.FetchMovieRatings();
return 0;
}
