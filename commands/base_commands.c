#ifndef BASE_COMMANDS_C
#define BASE_COMMANDS_C
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
    return  "----> f0xy bot : v"FOXY_VERSION"\n"
            "echo\t""simple echo command\n"\
            "time\t""returns current local time\n"
            "help\t""current command";
}
#endif