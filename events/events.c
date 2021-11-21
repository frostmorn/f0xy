#ifndef EVENTS_H
#define EVENTS_H
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "../types/types.c"
#include "../settings.h"
#include "../commands/commands.h"
struct Event *events = 0;
size_t events_count = 0;
pthread_mutex_t events_mutex = PTHREAD_MUTEX_INITIALIZER;

void createEvent(uint32_t event_type, void *event_data, size_t data_length)
{
	LOG_INFO("<events.c>\tstarting createEvent()\n");

	struct Event event;
	event.type = event_type;
	// Mutex

	pthread_mutex_lock(&events_mutex);

	event.length = data_length;
	event.data = event_data;
	event.timestamp = time(0);

	if (events)
	{
		struct Event *_events = (struct Event *)realloc(events, sizeof(struct Event) * (events_count + 1));

		if (_events == 0)
		{
			LOG_ERROR("<events.c>\tREALLOC RETURNED NULL POINTER");
			exit(0);
		}
		events = _events;
	}
	else
	{
		events = (struct Event *)malloc(sizeof(struct Event));
	}
	memcpy(&events[events_count], &event, sizeof(struct Event));
	events_count++;
	pthread_mutex_unlock(&events_mutex);
#if DI_COUNT_CREATED_EVENTS
	LOG_INFO_X("There're %d created events\n", events_count);
#endif
}

void *eventHandlerThread(void *args)
{
	size_t handled_events = 0;
	while (1)
	{
		pthread_mutex_lock(&events_mutex);
		if ((events) && (handled_events != events_count))
		{
			LOG_INFO_X("Handling  %llu event...\n", handled_events);

			switch (events[handled_events].type)
			{
			case TDEFAULT_EVENT:
			{
				break;
			}
			case TOX_FRIEND_REQUEST_EVENT:
			{
				break;
			}
			case TOX_MESSAGE_EVENT:
			{
				
				struct ToxMessage *tdata = (struct ToxMessage *)events[handled_events].data;
				LOG_INFO_X("<events.c> { Tox Message } %s \n", (char *)(uint8_t *)tdata->message);
				
				TOX_ERR_FRIEND_SEND_MESSAGE *error;
				
				if (tdata->message[0] == COMMAND_TRIGGER){
										
					if ((strstr((char *)(uint8_t *)tdata->message, "echo") !=0) && strlen(tdata->message) > 6){
						char *cmd_response = cmd_echo( (char *)(uint8_t *)tdata->message + 6);
						tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), error);
					}
					else if ((strstr((char *)(uint8_t *)tdata->message, "time") !=0) ){
						char *cmd_response = cmd_time();
						tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), error);
					}
					else if ((strstr((char *)(uint8_t *)tdata->message, "restart") !=0) ){
						char *cmd_response = "Restart command recieved. Initiating...";
						tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), error);
						cmd_restart();
					}
					else if ((strstr((char *)(uint8_t *)tdata->message, "help") !=0) ){
						char *cmd_response = cmd_help();
						tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), error);
					}
					else{
						goto cmd_not_found;
					}
				}
				else{
					cmd_not_found:
						char *cmd_response = cmd_help();
						tox_friend_send_message(tdata->tox, tdata->friend_number, TOX_MESSAGE_TYPE_NORMAL, cmd_response, strlen(cmd_response), error);
				}
				break;
			}
			default:
			{
				LOG_ERROR("<events.c>\tUnknown event produced!!!");
				break;
			}
			}
			handled_events++;
#if DI_COUNT_HANDLED_EVENTS
			LOG_INFO_X("There're %d handled events\n", handled_events);
#endif
		}
		// Sleep
		pthread_mutex_unlock(&events_mutex);
		usleep(EVENT_HANDLER_SLEEP_TIME);
	}
}
#endif
