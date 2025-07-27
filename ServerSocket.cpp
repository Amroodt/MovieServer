//
// Created by Joel Amroodt on 2025/07/23.
//

#include "ServerSocket.h"
#include "user.h"

#include <cstdio>
#include <cstdlib>
#include <string>

ServerSocket::ServerSocket(pqxx::connection &c)
    : servinfo (nullptr),
      db_connection(c)

{
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((rv= getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0)
    {
        fprintf(stderr,"gai error: %s\n", gai_strerror(rv));
        return;
    }


    // loop through the results and bind to the first one
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))== -1)
        {
            perror("server: socket");;
            continue;
        }
        if(setsockopt(sockfd, SOL_SOCKET,SO_REUSEPORT, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }
        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }
    freeaddrinfo(servinfo);

    if(p==NULL)
    {
        fprintf(stderr,"server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }
    sa.sa_handler = sigchild_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    printf("server: waiting for connection...\n");



    }

ServerSocket::~ServerSocket()
{
}

void ServerSocket::run()
{
    while(1)
    {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if(new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr),s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork())
        {
            close(sockfd);
            handleConnection();
            close(new_fd);
            exit(0);
        }
        close(new_fd);
    }

}

void ServerSocket::handleConnection()
{
    std::string path = recvRequest(new_fd);

    if (path.find("/userid?name=") == 0)
    {
        std::string searchUser = user.UserSerializer(path, db_connection, user);
        std::string body;
        body = "{\"user_id\": " + searchUser + "}";

        std::string status = "200 OK";
        std:: string content_type = "application/json";

        sendResponse(new_fd, status, content_type, body);
        close(new_fd);
    }
}

void ServerSocket::sendResponse(int new_fd, const std::string &status, const std::string &contentType,
    const std::string &body)
{
    std::ostringstream response;
    response << "HTTP/1.1 " << status <<"\r\n"
             << "Content-Type: " << contentType << "\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << body;

    std::string res = response.str();
    //send(new_fd, res.c_str(), res.size(), 0);

    ssize_t sent = send(new_fd, res.c_str(), res.size(), 0);
    if (sent == -1)
        perror("send");
}


std::string ServerSocket::recvRequest(int new_fd)
{
    char request_buffer[4096] = {0};
    ssize_t received = recv(new_fd, request_buffer, sizeof(request_buffer) - 1, 0);



    if (received < 0)
    {
        printf( request_buffer);
        perror("recv failed or connection failed" );
        return "";
    }
    std::string request_line(request_buffer);
    size_t path_start = request_line.find("GET ") + 4;
    size_t path_end = request_line.find(" ", path_start);
    std::string path = request_line.substr(path_start, path_end - path_start);

    if (path_start == std::string::npos || path_end == std::string::npos)
    {
        fprintf(stderr, "Server: Malformed request\n");
        return "";
    }

    printf("Received HTTP request:\n%s\n", request_buffer);
    return request_line.substr(path_start, path_end - path_start);

}

void ServerSocket::sigchild_handler(int s)
{
    (void)s; // unused variable warning
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) >0);
    errno = saved_errno;

}

void * ServerSocket::get_in_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
