#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


void error (char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    
    //file descriptors
    int sockfd, newsockfd, portno, client_len, n;
    
    char bufer[256];
    
    struct sockaddr_in serv_addr, cli_addr;
    
    if(argc < 2) {
        error("ERROR, no port provided");
    }
    
    //create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error
    }
    
    
    
}
