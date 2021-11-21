#ifndef BASE_COMMANDS_C
#define BASE_COMMANDS_C
#include "../checks/checks.c"
#include "../time.h"
#include <time.h>

char * cmd_echo(char *arg){
    return arg;
}
char * cmd_time(){
    return asctime (get_local_time()) ;
}


char *cmd_uptime_memory = 0;

char *cmd_uptime(){
    char *diff =  GetTimeDiffStr(get_local_time(), StartupTime);
    // Allocate memory just once
    if (!cmd_uptime_memory){
        cmd_uptime_memory = malloc(sizeof(char)*(CMD_UPTIME_SIZE));
    }
    if (!cmd_uptime_memory){
        LOG_ERROR("<commands/base.c>malloc failed to align memory block\n");
        return "Command cannot be complete";
    }
    memset(cmd_uptime_memory, 0, CMD_UPTIME_SIZE);
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
            "restart"   "\t"    "restarts bot"                  "\n"
            "help"      "\t"    "current command"               "\n";
}
#endif