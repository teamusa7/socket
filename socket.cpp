#include <iostream>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


void error (char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    //file descriptors
    int sockfd, newsockfd, 
    //stores the port number on which the server accepts connections
    portno, 
    //stores the size of the client address
    client_len, 
    //return value for read() write(). contains the number of char read or written
    n;

    //server reads characters from the socket connection to this buffer
    char buffer[256];

    /*sockaddr_in contains an internet address
      serv_addr contains the server adress
      cli_addr contains the client adress that connects to the server
    */
    struct sockaddr_in serv_addr, cli_addr;

    //used for the user to pass in a port number
    if(argc < 2) {
        std::cout << "ERROR, no port provided" << std::endl;
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < -1) {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));




    return 0;
}
