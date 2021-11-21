#ifndef BASE_COMMANDS_C
#define BASE_COMMANDS_C
#include "../checks/checks.c"
char * cmd_echo(char *arg){
    return arg;
}
char * cmd_time(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return asctime (timeinfo) ;
}
char * cmd_help(){
    return  "----> f0xy bot : v"    FOXY_VERSION                "\n"
            "echo"      "\t"    "simple echo command"           "\n"
            "time"      "\t"    "returns current local time"    "\n"
            "restart"   "\t"    "restarts bot"                  "\n"
            "help"      "\t"    "current command"               "\n";
}
char * cmd_restart(){
    // TODO : Check permissions for tox-user
    UnlockFileMutex();
    execv("/proc/self/exe", 0);
    exit(0);
}
#endif