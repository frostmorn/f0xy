#ifndef F_TIME_H
#define F_TIME_H
#include <unistd.h>
#include <math.h>
struct tm *StartupTime = 0;

struct tm *get_local_time(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return timeinfo;
}
void SetStartupTime(){
    StartupTime = malloc(sizeof(struct tm));
    struct tm *buffer = get_local_time();
    memcpy(StartupTime, buffer, sizeof(struct tm ));
}
char *difftime_memory = 0;
char * GetTimeDiffStr(struct tm* TIME_1, struct tm* TIME_0){
    struct tm* startup = TIME_0;
    double secs = difftime(mktime(TIME_1),mktime(TIME_0));
    double days = floor(secs/86400);
    secs = secs - days * 86400;
    double hours = floor(secs/3600);
    secs = secs - hours * 3600;
    double mins = floor(secs/60);
    secs = secs - mins*60;
    if (!difftime_memory){
        difftime_memory = malloc(DIFFTIME_SIZE*sizeof(char));
    }
    if (!difftime_memory){
        LOG_ERROR("<time.h>malloc failed to align memory block\n");
        exit(EXIT_NO_MEMORY);
    }
    sprintf(difftime_memory, "%10.0lf days, %2.0lf hours, %2.0lf mins, %2.0lf secs", days, hours, mins, secs);
    return difftime_memory;
}
#endif