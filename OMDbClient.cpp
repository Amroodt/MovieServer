#include "OMDbClient.h"
#include <iostream>
//#include <string>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <chrono>
#include <cmath>


#define PORT "80"
#define HOST "www.omdbapi.com"
    //#define PATH "/?i=tt3896198&apikey=4cfe3aa7"
#define BUFFER_SIZE 4096


OMDbClient::OMDbClient()
{

};

int OMDbClient::FetchMovieRatings(void)
    {
        struct addrinfo hints, *res, *p;
        int sockfd;
        int status;

        char buffer[BUFFER_SIZE];
        int bytes_received;

        auto start_dns = std::chrono::high_resolution_clock::now();
        // 1. Set up hints
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;  // IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM;

        // 2. Get address info
        if ((status = getaddrinfo(HOST, PORT, &hints, &res)) != 0) {
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
            return 1;
        }
        auto end_dns = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_dns - start_dns);
        double time_in_seconds = duration.count() * 1e-9;
        std::cout << "Time taken equals: " << time_in_seconds << " seconds" << std::endl;

        // 3. Loop through results and connect
        for (p = res; p != NULL; p = p->ai_next)
            {
            // Try to create a socket
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
                perror("client: socket");
                continue;
            }

            // Try to connect
            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                perror("client: connect");
                continue;
            }

            break; // Connected!
        }

        if (p == NULL)
        {
            fprintf(stderr, "client: failed to connect\n");
            return 2;
        }

        freeaddrinfo(res); // no longer needed


    // enter movie title
    std::string title;
    std::cout << "Please enter a movie title: ";
    std::getline(std::cin, title);

    for (int title_char = 0; title_char < title.size(); title_char++)
    {
        if (title[title_char] == ' ')
        {
            title[title_char] = '+';
        }
    }

    std::ifstream  apiFile ("apikey.txt");
    std:: string apiKey;
    if (apiFile) {
        std::getline(apiFile, apiKey);
    }
    std:: string path = "/?t=" + title + "&apikey=" + apiKey;
    std:: cout << path << std::endl; // delete this line, it is not needed and cout's the api key.


    char request[512];
    snprintf(request, sizeof(request),
        "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Accept-Encoding: identity\r\n"
        "Connection: close\r\n"
        "\r\n", path.c_str(), HOST);

    // Send request
    if (send(sockfd, request, strlen(request), 0) == -1) {
        perror("send");
        return 3;
    }

    printf("=== Response ===\n");

    // recv function
    while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate
        printf("%s", buffer);
    }

    if (bytes_received == -1) {
        perror("recv");
    }

    close(sockfd);

    return 0;
    }
