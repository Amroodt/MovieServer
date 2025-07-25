//
// Created by Joel Amroodt on 2025/07/23.
//

#include "ServerSocket.h"
#include "user.h"

#include <cstdio>
#include <cstdlib>

ServerSocket::ServerSocket(pqxx::connection &c)
: servinfo (nullptr)
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
            // if (send(new_fd, "Hello World!\n", 13, 0) == -1)
            //     perror("send");
            // send(new_fd, http_response, strlen(http_response), 0);
            // close(new_fd);
            char request_buffer[4096] = {0};
            ssize_t received = recv(new_fd, request_buffer, sizeof(request_buffer) - 1, 0);

            std::string request_line(request_buffer); // convert to C++ string
            size_t path_start = request_line.find("GET ") + 4;
            size_t path_end = request_line.find(" ", path_start);
            std::string path = request_line.substr(path_start, path_end - path_start);

            if (received > 0) {
                printf("Received HTTP request:\n%s\n", request_buffer);
            }

            if (path.find("/userid?name=") == 0) {
                std::string username = path.substr(strlen("/userid?name="));

                std::string searchUser = user.getUser(c,username); //Function Call to search User


                std::ostringstream body;
                body << "{\"user_id\": " << searchUser << "}";

                std::ostringstream response;
                response << "HTTP/1.1 200 OK\r\n"
                         << "Content-Type: application/json\r\n"
                         << "Content-Length: " << body.str().length() << "\r\n"
                         << "Connection: close\r\n"
                         << "\r\n"
                         << body.str();

                std::string res = response.str();
                send(new_fd, res.c_str(), res.size(), 0);

                ssize_t sent = send(new_fd, res.c_str(), strlen(res.c_str()), 0);
                if (sent == -1)
                    perror("send");
                close(new_fd);
                exit(0);
            }
            close(new_fd);
            exit(0);
        }

    }
}
ServerSocket::~ServerSocket()
{
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
