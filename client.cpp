#include <iostream>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <unistd.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    
    //creates the file descriptors for the sockets
    int sockfd,
    portno;
    
    ssize_t n;
    
    // serv_addr will contain the servers address
    struct sockaddr_in serv_addr;
    
    // used to define a host computer on the internet
    struct hostent *server;
    
    //buffer for sending messages
    char buffer[256];
    
    // checks to see if the hostname port was entered
    if (argc < 3) {
        std::cout << "Usage " << argv[0] << " hostname port" << std::endl;
        exit(0);
    }
    
    // get the port number enterd
    portno = atoi(argv[2]);
    
    /* create a socket
     @param1: address domain of the socket
        - AF_UNIX: unix domain for two proccesses which share a common file
        - AF_INTET: internet domain for any two hosts on the internet
     @param2: socket type
        - stream socket: reads continuous stream like a file
        - datagram socket: messages are read in chunks
     @param3: protocol, if 0 the OS will choose the appropriate protocol
        - TCP for stream sockets
        - UDP for datagram sockets
     @return an entry into the file descriptor table(int) to reference the socket
        - returns a -1 if the call fails
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        error((char*)"Error opening socket");
    }
    
    //get the hostname from argv[1]
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        error((char *)"Error no such hostname");
    }
    
    /* sets all values in a buffer to zero
       @param1: a pointer to the buffer
       @param2: size of the buffer (initalizes serv_addr to zeros)
     */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    // from serv_addr sin_family has to be set to AF_INET
    serv_addr.sin_family = AF_INET;
    
    /* sets the fields in serv_addr
       copies 'length' bytes from 's1' to 's2'
        - bcopy(char *s1, char *s2, int length)
     */
    bcopy((char *) server -> h_addr, (char *) &serv_addr.sin_addr.s_addr, server -> h_length);
    
    /* second filed from serv_addr ontains the port number
        but must be converted to nerwork byte order*/
    serv_addr.sin_port = htons(portno);
    
    /* connect function is called by the client to establish a connectino to the server
       @param1: file descriptor
       @param2: the address of the host it wants to connect too(including port no.)
       @param3: the size of the address
       @return: 0 if success and -1 if fails*/
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        error((char *)"ERROR connecting");
    }
    
    std::cout << "Please enter the message: " << std::endl;
    
    // clearing buffer to write to it
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
        error((char *)"ERROR writing to socket");
    }
    bzero(buffer, 256);
    n = read(sockfd, buffer, 256);
    if (n < 0) {
        error((char *)"ERROR reading from the socket");
    }
    std::cout << buffer << std::endl;
    
    close(sockfd);
    return 0;
    
    
}
