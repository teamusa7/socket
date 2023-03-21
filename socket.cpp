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
    /* socket creats a new socket
       @param1: address domain of the socket
         - AF_UNIX: unix domain for two processes which share a common
           file system
         - AF_INET: internet domain for any two hosts on the internet
       @param2: socket type
         - stream socket: reads continuous stream like a file or pipe
         - datagram socket: messages are read in chunks
       @param3: protocol, if 0 the OS will choose the appropriate protocol
         - TCP for stream sockets
         - UDP for datagram sockets
       @return an entry into the file descriptor table (int) to reference the socket
         - returns a -1 if the cal fails
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < -1) {
        error("ERROR opening socket");
    }
    
    /* sets all values in a buffer to zero
       @param1: a pointer to the buffer
       @param2: size of the buffer (intitalizes serv_addr to zeros)
     */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    //takes the port number and converts from a string to an int
    portno = atoi(argv[1]);
    
    //from serv_addr sin_family has to be set to AF_INET
    serv_addr.sin_family = AF_INET;
    
    /*second field from serv_addr contains the port number but it must be
      converted to network byte order
     */
    serv_addr.sin_port = htons(portno);
    
    /* third fiels from serv_adddr contains the IP address of the host
        - for server code this will be the IP of the machine of the server
        - INADDR_ANY gets the address for us
     */
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    /* bind() binds a socket to an address (i.e. the address of the current
       host and port number on which the server will run)
       @param1: the socket file descriptor
       @param2: the address to which is bound
        - a pointer to a struct of type sockaddr (we type cast to correct it)
       @param3: the size of the address to which its bound
     */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("ERROR on binding");
    }
    
    /* listens on the socket for any connections
       @param1: the socket file descriptor
       @param2: size of the backlog queue
        - the number of connections that can be waiting while the process is
          handling a connection
        - should be set to 5, the max size permitted by most systems
     */
    listen(sockfd, 5);
    
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struck sockaddr *) &cli_addr, &clilen);
    if (newsocksd < 0 ) {
        error("ERROR on accpet");
    }



    return 0;
}
