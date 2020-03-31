// From: www.thegeekstuff.com/2011/12/c-socket-programming
// Note that port# 5000 is hard-coded into this implementation

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <stdbool.h>
#include <ctype.h> 

#include "verify.h"

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, valread = 0;
    int port;
    struct sockaddr_in serv_addr; 

    char sendBuff[3], recvBuff[10];
    time_t ticks; 

    if(argc != 2) 
    {
        printf("\n Usage: %s <port number> \n", argv[0]);
        return -1;
    }

    if ((port = getPortNum(argc, argv)) == -1) {
        return -1;
    };

    printf("port: %d\n", port);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        valread = read(connfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[valread] = 0;
        fprintf(stdout, "1583256161.99: # 1 (T%3s) from ug11.20295\n", recvBuff);

        if(valread < 0)
        {
            fprintf(stderr, "\n Read error \n");
        } 

        int n = atoi(recvBuff);
        snprintf(sendBuff, sizeof(sendBuff), "%d", n);
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
}