#ifndef VERIFY_H
#define VERIFY_H

#define MIN_PORT_NUM 5000
#define MAX_PORT_NUM 64000
#define _POSIX_C_SOURCE 200809L

bool isNum(char* num);
int getPortNum(int argc, char *argv[]);
long getMilliseconds(struct timespec spec, time_t seconds);

#endif