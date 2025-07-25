#include "Movie.h"
#include "user.h"
#include "OMDbClient.h"
#include "Review.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

#include "ServerSocket.h"

int main()
{
    //Database connection
     pqxx::connection c("dbname=MovieApp");
    //Add user
    // user toAdd;
    // toAdd.AddUser(c, "Ava", " ");

    //Search User
     // user* search_name = new user;
     // std::string try_search_name;
     //
     // bool userFound = false;
     // while (!userFound)
     // {
     //     std::cout << "Enter a user name: " << std::endl;
     //     std::getline(std::cin, try_search_name);
     //
     //     try
     //     {
     //         std::cout <<  search_name->getUser(c, try_search_name) << std::endl;
     //         userFound = true;
     //     }
     //     catch (const std::exception& e)
     //     {
     //         std::cout << "Username not found: "<<e.what() << std::endl;
     //     }
     //
     // }
     //
     //
     //
     //
     // delete search_name;


    // Movie movie;
    // std::cout << "" << movie.getTitle();
    // // std::cout << "\n" << movie.getYear();
    // // std::cout << "\n" << movie.getRelease();
    // // std::cout << "\n" << movie.getGenre();
    // // std::cout << "\n" << movie.getPoster();

    // add user i.d
    // user* setID = new user;
    // std::string nameID;
    // bool userFound_2 = false;
    //
    // while (!userFound_2)
    // {
    //     std::cout << "Enter a user name: " << std::endl;
    //     std::getline(std::cin, nameID);
    //
    //     try
    //     {
    //         std::cout <<  setID->getUser(c, nameID) << std::endl;
    //         userFound_2 = true;
    //     }
    //     catch (const std::exception& e)
    //     {
    //         std::cout << "Username not found: "<<e.what() << std::endl;
    //     }
    // }
    // int ID = setID->getID(c, nameID);
    // delete setID;
    //
    // //Create a movie review with  userID and movieTitle
    // Movie* movie = new Movie();
    // std::string title = movie->getTitle();
    // delete movie;
    //
    // Review* review = new Review(c,title, ID);


    ServerSocket server(c);




    // OMDbClient client;
    // return client.FetchMovieRatings();

return 0;
}
