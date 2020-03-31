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
#include "tands.h"

int main(int argc, char *argv[])
{
    int sockfd = 0, valread = 0, numOfTran = 0; 
    int port, n;
    char request;
    char recvBuff[3], sendBuff[10], outputFileName[15];;
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        fprintf(stderr, "\n Usage: %s <port number> <ip of server> \n", argv[0]);
        return 1;
    } 

    if ((port = getPortNum(argc, argv)) == -1) {
        return -1;
    };

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); 

    if(inet_pton(AF_INET, argv[2], &serv_addr.sin_addr)<=0)
    {
        fprintf(stderr, "\n inet_pton error occured\n");
        return 1;
    } 

    char machinename[6] = "ug11";
    char pid[6] = "20295";

    strcpy(outputFileName, machinename);
    strcat(outputFileName, ".");
    strcat(outputFileName, pid);
    stdout = fopen(outputFileName, "w");

    fprintf(stdout, "Using port %d\n", port);
    fprintf(stdout, "Using server address %s\n", argv[2]);
    fprintf(stdout, "Host %s.%s\n", machinename, pid);

    while (1){

        if (scanf("%c%d", &request, &n) == EOF) {    
            fprintf(stdout, "Sent %d transactions\n", numOfTran);   
            break;
        }
        
        if (request == 'T') {
            memset(recvBuff, '0',sizeof(recvBuff));
            memset(sendBuff, '0',sizeof(sendBuff));
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                fprintf(stderr, "\n Error : Could not create socket \n");
                return 1;
            } 

            if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                fprintf(stderr, "\n Error : Connect Failed \n");
                return 1;
            } 
            // send
            snprintf(sendBuff, sizeof(sendBuff), "%d", n);
            write(sockfd, sendBuff, strlen(sendBuff)); 
            fprintf(stdout, "1583256162.00: Send (T%3s)\n", sendBuff);
            numOfTran++;
            // receive
            valread = read(sockfd, recvBuff, sizeof(recvBuff)-1);
            recvBuff[valread] = 0;
            fprintf(stdout, "1583256162.00: Recv (D%3s)\n", recvBuff);

            if ( valread < 0)
            {
                fprintf(stderr, "\n Read error \n");
            } 
        } else if (request == 'S') {
            Sleep(n);
            printf("Sleep %d units\n", n);
        } 
        getchar(); // read a newline char
    }

    return 0;
}

