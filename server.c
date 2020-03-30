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

#define MIN_PORT_NUM 5000
#define MAX_PORT_NUM 64000

bool isNum(char* num);
int getPortNum(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    int port;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

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

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
}

bool isNum(char* num) {
    for (int i = 0; i < strlen(num); i++){
        if (isdigit(num[i]) == 0) {
            return false; 
        }
    }
    return true; 
} 

// verify the input and return port number
int getPortNum(int argc, char *argv[]) {
    int port;

    if(argc != 2) 
    {
        printf("\n Usage: %s <port number> \n", argv[0]);
        return -1;
    } else
    {
        if (!isNum(argv[1])) {
            printf("\n Usage: %s <port number> \n", argv[0]);
            return -1;
        } 
        port = atoi(argv[1]);
        if ((port < MIN_PORT_NUM) || (port > MAX_PORT_NUM))
        {
            printf("The port must be in the range %d to %d.\n", MIN_PORT_NUM, MAX_PORT_NUM);
            return -1;
        }
    }
    return port;
}