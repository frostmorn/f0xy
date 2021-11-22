#ifndef F_TIME_H
#define F_TIME_H
#include <unistd.h>
#include <math.h>
#include "memory.h"

struct tm *get_local_time(){
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return timeinfo;
}
void SetStartupTime(){
    startup_time = allocate_once(startup_time, sizeof(struct tm));
    struct tm *buffer = get_local_time();
    memcpy(startup_time, buffer, sizeof(struct tm ));
}

char * GetTimeDiffStr(struct tm* TIME_1, struct tm* TIME_0){

    struct tm* startup = TIME_0;
    double secs = difftime(mktime(TIME_1),mktime(TIME_0));
    double days = floor(secs/86400);
    secs = secs - days * 86400;
    double hours = floor(secs/3600);
    secs = secs - hours * 3600;
    double mins = floor(secs/60);
    secs = secs - mins*60;

    difftime_memory = allocate_once(difftime_memory, DIFFTIME_SIZE*sizeof(char));

    sprintf(difftime_memory, FOXY_DIFFTIME_FORMAT, days, hours, mins, secs);

    return difftime_memory;
}
#endif