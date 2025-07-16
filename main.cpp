#include "Movie.h"
#include "user.h"
#include "OMDbClient.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

int main()
{
    //Database connection
     pqxx::connection c("dbname=MovieApp");

    // setup a user
    //  user Joel;
    // std::string name = "Joel", password = Joel.getPassword();

    // std::cout <<" Connected to " << c.dbname() << "\n";
    //
    //
    // Joel.SaveUser(c, name, password);
    //
    // std::cout << name << "created \n";

    //Search User
    user* search_name = new user;
    std::string try_search_name;

    bool userFound = false;
    while (!userFound)
    {
        std::cout << "Enter a user name: " << std::endl;
        std::getline(std::cin, try_search_name);

        try
        {
            std::cout <<  search_name->getUser(c, try_search_name) << std::endl;
            userFound = true;
        }
        catch (const std::exception& e)
        {
            std::cout << "Username not found: "<<e.what() << std::endl;
        }

    }




    delete search_name;

    //
    // Movie movie;
    // std::cout << "" << movie.getTitle();
    // std::cout << "\n" << movie.getYear();
    // std::cout << "\n" << movie.getRelease();
    // std::cout << "\n" << movie.getGenre();
    // std::cout << "\n" << movie.getPoster();



    // OMDbClient client;
    // return client.FetchMovieRatings();

return 0;
}
