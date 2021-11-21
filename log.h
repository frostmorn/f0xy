#ifndef LOG_H
#define LOG_H
#include <stdio.h>
// Log function call
#define LOG_INFO(x) printf("\e[1;32m[ INFO ]\e[0m "); printf(x);
#define LOG_INFO_X(x,y) printf("\e[1;32m[ INFO ]\e[0m "); printf(x, y);
#define LOG_F_CALL(x) printf("\e[1;32m[ INFO ]\e[0m starting call \e[1;33m");printf(x);printf("\e[0m\n");
#define LOG_ERROR(x) printf("\e[1;90m[ ERROR ]\e[0m "); printf(x);

#endif
