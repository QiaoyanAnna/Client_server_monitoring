#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <ctype.h> 
#include <math.h>
#include <time.h>

#include "verify.h"

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

    if (!isNum(argv[1])) {
        fprintf(stderr, "\n Usage: %s <port number> \n", argv[0]);
        return -1;
    } 
    port = atoi(argv[1]);
    if ((port < MIN_PORT_NUM) || (port > MAX_PORT_NUM))
    {
        fprintf(stderr, "The port must be in the range %d to %d.\n", MIN_PORT_NUM, MAX_PORT_NUM);
        return -1;
    }
    
    return port;
}

// reference: https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux [Accessed Mar.31, 2020]
long getMilliseconds(struct timespec spec, time_t seconds)
{
    long milliseconds;
    
    milliseconds = round(spec.tv_nsec / 1.0e7);
    if (milliseconds > 99) {
        seconds++;
        milliseconds = 0;
    } 

    return milliseconds;
}