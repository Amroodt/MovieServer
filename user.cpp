//
// Created by Joel Amroodt on 2025/07/10.
//

#include "user.h"

user::user()
    : username("Change to your name."),
      serverID("Amroodt"),
      passWordHash("1234")

{

}
user::~user()
{

}

void user::setName(std::string name)
{

}

std::string user::getName()
{
}

std::string user::getPassword()
{
    return passWordHash;
}

void user::setPasswordHash(std::string password)
{
}

bool user::ValidatePassword(std::string password)
{
}

void user::setRole()
{
}

std::string user::getRole() const
{
}

void user::SaveUser(pqxx::connection& c,std::string name, std::string password )
{
    pqxx::work txn{c};
    txn.exec("INSERT INTO users (username, password_hash) VALUES (" + txn.quote(name) + ", " + txn.quote(password) + ")");
    txn.commit();
}

std::string user::getUser(pqxx::connection& c, std::string username) const
{
    pqxx::work txn{c};
    pqxx::result r = txn.exec(
        "SELECT id, username FROM users WHERE username = " + txn.quote(username)
    );
    txn.commit();

    if(r.empty())
        return "User not found";

    int id = r[0][0].as<int>();
    std::string uname = r[0][1].as<std::string>();



    return "ID: " + std::to_string(id) + ", Username: " + uname;
}

int user::getID(pqxx::connection& c, std::string username) const
{
    pqxx::work txn{c};
    pqxx::result r = txn.exec("SELECT id FROM users WHERE username = " + txn.quote(username));
    txn.commit();
    int const id = r[0][0].as<int>();
    return id;
}

void user::AddUser(pqxx::connection &c, std::string username, std::string password)
{
    // setup a user
     user* toAdd = new user();
    std::string name = username;
    password = toAdd->getPassword();

    std::cout <<" Connected to " << c.dbname() << "\n";


    toAdd->SaveUser(c, name, password);

    std::cout << name << "created \n";
}

std::string user::UserSerializer(std::string& path, pqxx::connection &db_connection, const user& user)
{
    std::string username = path.substr(strlen("/userid?name="));
    std::string searchUser = user.getUser(db_connection,username);
    return searchUser;
}
