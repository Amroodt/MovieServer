//
// Created by Joel Amroodt on 2025/07/23.
//

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "user.h"

#define PORT "3490" //Port to connect
#define BACKLOG 5 // the amount of pending connections

class ServerSocket {

public:
    ServerSocket(pqxx::connection& c);
    ~ServerSocket();



private:
    static void sigchild_handler(int s);
    // get sockaddrr, IPv4 or IPv6
    void *get_in_addr(struct sockaddr *sa);

    int sockfd, new_fd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    user user;



};



#endif //SERVERSOCKET_H
