#pragma once
#include <iostream>
#include <pqxx/pqxx>
//#include <<bcrypt/BCrypt.hpp> // will use bycrypt for password hashing

class user
{
public:
    user();
    ~user();


    void setName(std::string name);
    std::string getName();

    // void setServeName();
    // std::string getServeName();

    std::string getPassword();
    void setPasswordHash(std::string password);
    bool ValidatePassword(std::string password);

    void setRole();
    std::string getRole() const;
    void SaveUser(pqxx::connection& c,std::string name, std::string password);
    std::string getUser(pqxx::connection& c, std::string username) const;
    int getID(pqxx::connection& c, std::string username) const;

    void AddUser(pqxx::connection& c, std::string username, std::string password);



private:
    int id;
    std::string username;
    std::string  passWordHash;
    std::string serverID;
    std::string role;




};


