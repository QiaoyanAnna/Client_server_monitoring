// From: www.thegeekstuff.com/2011/12/c-socket-programming
// Note that port# 5000 is hard-coded into this implementation

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <stdbool.h>
#include <ctype.h> 

#include "verify.h"

int main(int argc, char *argv[])
{
    int sockfd = 0, valread = 0; 
    int port;
    char recvBuff[3], sendBuff[10];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        fprintf(stderr, "\n Usage: %s <port number> <ip of server> \n", argv[0]);
        return 1;
    } 

    if ((port = getPortNum(argc, argv)) == -1) {
        return -1;
    };

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, argv[2], &serv_addr.sin_addr)<=0)
    {
        fprintf(stderr, "\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       fprintf(stderr, "\n Error : Connect Failed \n");
       return 1;
    } 

    int n = 30;
    snprintf(sendBuff, sizeof(sendBuff), "%d", n);
    write(sockfd, sendBuff, strlen(sendBuff)); 

    while ( (valread = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[valread] = 0;
        fprintf(stdout, "1583256162.00: Recv (D%3s)\n", recvBuff);
    } 

    if(valread < 0)
    {
        fprintf(stderr, "\n Read error \n");
    } 

    return 0;
}

