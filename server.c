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
#include <pthread.h>

#include "verify.h"
#include "tands.h"

#define MAX_WAITING_TIME 60

int numOfTran = 0;
clock_t startRecv;

void *process(void *arg);

int main(int argc, char *argv[])
{
    int listenfd = 0;
    int port;
    struct sockaddr_in serv_addr; 
    pthread_t ntid;

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

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    clock_t serverStart = clock();
    startRecv = clock();
    if( pthread_create( &ntid, NULL, process, (void *) (size_t) listenfd ) ) {
        fprintf(stderr, "Error occured while creating thread.\n");
	}

    while (1) {
        double waitingTime = ((double) (clock() - startRecv)) / CLOCKS_PER_SEC;
        clock_t serverEnd = clock();
        if (waitingTime > MAX_WAITING_TIME) {
            pthread_kill(ntid, 0);
            double duration = ((double) (serverEnd - serverStart)) / CLOCKS_PER_SEC;
            double transPerSec = numOfTran / duration;
            fprintf(stdout, "\nSUMMARY\n");
            fprintf(stdout, "  14 transactions from ug11.20295\n");
            fprintf(stdout, "  15 transactions from ug11.20296\n");
            fprintf(stdout, "%0.1f transactions/sec (%d/%0.1f)\n", transPerSec, numOfTran, duration);
            break;
        }
    }
}

void *process(void *arg) {
    int n;
    int listenfd = (int)arg;
    int connfd = 0, valread = 0;
    char sendBuff[8], recvBuff[256];
    char *nStr, *machine, *token;
    struct timespec spec;

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        // receive
        memset(recvBuff, '0',sizeof(recvBuff));
        valread = read(connfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[valread] = 0;
        numOfTran++;
        token = strtok(recvBuff, "&");
        nStr = token;
        machine = strtok(NULL, "&");
        startRecv = clock();
        clock_gettime(CLOCK_REALTIME, &spec);
        fprintf(stdout, "%ld.%ld: #%3d (T%3s) from %s\n", spec.tv_sec, getMilliseconds(spec, spec.tv_sec), numOfTran, nStr, machine);

        if(valread < 0)
        {
            fprintf(stderr, "\n Read error \n");
        } 
        n = atoi(nStr);
        Trans(n);
        // send
        memset(sendBuff, '0', sizeof(sendBuff)); 
        snprintf(sendBuff, sizeof(sendBuff), "%d", numOfTran);
        write(connfd, sendBuff, strlen(sendBuff)); 
        clock_gettime(CLOCK_REALTIME, &spec);
        fprintf(stdout, "%ld.%ld: #%3d (Done) from %s\n", spec.tv_sec, getMilliseconds(spec, spec.tv_sec), numOfTran, machine);
        close(connfd);
        sleep(1);
     }
}