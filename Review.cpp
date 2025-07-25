//
// Created by Joel Amroodt on 2025/07/16.
//

#include "Review.h"


Review::Review(pqxx::connection& c,std::string movieTitle, int userID)
{
    pqxx::work txn{c};
    txn.exec("INSERT INTO reviews (movietitle,userid) VALUES (" + txn.quote(movieTitle) + "," + txn.quote(userID) + ")");
    txn.commit();
}

