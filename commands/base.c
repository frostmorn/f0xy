#ifndef BASE_COMMANDS_C
#define BASE_COMMANDS_C
#include "../checks/checks.c"
#include "../time.h"
#include <time.h>
#include "../memory.h"
char * cmd_echo(char *arg){
    return arg;
}
char * cmd_time(){
    return asctime (get_local_time()) ;
}

char *cmd_uptime(){
    char *diff =  GetTimeDiffStr(get_local_time(), startup_time);
    // Allocate memory just once
    cmd_uptime_memory = allocate_once(cmd_uptime_memory, CMD_UPTIME_SIZE*sizeof(char));

    strcpy(cmd_uptime_memory, "UPTIME:\n");
    strcat(cmd_uptime_memory, diff);
    strcat(cmd_uptime_memory, "\0");
    return cmd_uptime_memory;
}

char * cmd_restart(){
    // TODO : Check permissions for tox-user
    UnlockFileMutex();
    execv("/proc/self/exe", 0);
    exit(0);
}

char * cmd_help(){
    return  "----> f0xy bot : v"    FOXY_VERSION                "\n"
            "\t""Base:\n"
            "echo"      "\t"    "simple echo command"           "\n"
            "time"      "\t"    "returns current local time"    "\n"
            "uptime"    "\t"    "returns bot uptime"            "\n"
            "restart"   "\t"    "restarts bot"                  "\n"
            "help"      "\t"    "current command"               "\n";
}
#endif