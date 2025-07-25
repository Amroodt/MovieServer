//
// Created by Joel Amroodt on 2025/07/16.
//

#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <pqxx/pqxx>



class Review
{
public:
    Review(pqxx::connection& c, std::string movieTitle, int userID);


private:

};



#endif //REVIEW_H
