#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <ctype.h> 

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
        printf("\n Usage: %s <port number> \n", argv[0]);
        return -1;
    } 
    port = atoi(argv[1]);
    if ((port < MIN_PORT_NUM) || (port > MAX_PORT_NUM))
    {
        printf("The port must be in the range %d to %d.\n", MIN_PORT_NUM, MAX_PORT_NUM);
        return -1;
    }
    
    return port;
}