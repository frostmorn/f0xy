#ifndef F_COMMANDS_H
#define F_COMMANDS_H
#include "base.c"
#include "../types/types.c"
int ExecuteToxMessageCommand(struct ToxMessage *tdata ){
    TOX_ERR_FRIEND_SEND_MESSAGE error;
    char *cmd_response = 0;
    if (tdata->message[0] == COMMAND_TRIGGER){
                            
        if ((strstr((char *)(uint8_t *)tdata->message, "echo") !=0) && strlen(tdata->message) > 6){
            cmd_response = cmd_echo( (char *)(uint8_t *)tdata->message + 6);
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
        }
        else if ((strstr((char *)(uint8_t *)tdata->message, "uptime") !=0) ){
            cmd_response = cmd_uptime();
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
        }
        else if ((strstr((char *)(uint8_t *)tdata->message, "time") !=0) ){
            cmd_response = cmd_time();
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
        }
        else if ((strstr((char *)(uint8_t *)tdata->message, "restart") !=0) ){
            cmd_response = "Restart command recieved. Initiating...";
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
            cmd_restart();
        }
        else if ((strstr((char *)(uint8_t *)tdata->message, "help") !=0) ){
            cmd_response = cmd_help();
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
        }
        else{
            cmd_response = "[ ERROR ] Command doesn't exist...";
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
            goto cmd_not_found;
        }
    }
    else{
        cmd_not_found:
            cmd_response = cmd_help();
            tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), &error);
    }
    if (error != TOX_ERR_FRIEND_SEND_MESSAGE_OK){
        // TODO : Handle another TOX_ERRORS
        LOG_ERROR("<commands/commands.h>Error while tox message sent occured. Take a next try...\n");
        usleep(SLEEP_BEFORE_RETRY);
        return ExecuteToxMessageCommand(tdata);
    }
}
#endif