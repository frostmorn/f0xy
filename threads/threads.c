#ifndef THREADS_H
#define THREADS_H
#include <pthread.h>
#include "../log.h"
#include <unistd.h>
#include "tox.c"
#include "../types/types.c"
#include <signal.h>

// Threads
pthread_t eventHandlerThread_id;
pthread_t toxCommunicateThread_id;

void StartThreads()
{
	LOG_F_CALL("<threads.c> StartThreads()");

	int err_eventHandlerThread =
		pthread_create(&eventHandlerThread_id, NULL, &eventHandlerThread, NULL);

	int err_toxCommunicateThread =
		pthread_create(&toxCommunicateThread_id, NULL, &toxCommunicateThread, NULL);

	// Handle pthread creation errors

	if (err_eventHandlerThread != 0)
	{
		LOG_ERROR("<threads.c> Error while creating eventHandlerThread\n");
		LOG_INFO_X("Error = %d\n", err_eventHandlerThread);
	}
	if (err_toxCommunicateThread != 0){
		LOG_ERROR("<threads.c> Error while creating toxCommunicateThread\n");
		LOG_INFO_X("Error = %d\n", err_toxCommunicateThread);
	}

	while (1)
	{
		usleep(1000000);
	}
}

void StopThreads()
{
	LOG_INFO("Killing Threads\n");
	update_savedata_file(f0xy_tox);
	pthread_kill(eventHandlerThread_id, SIGKILL);
	pthread_kill(toxCommunicateThread_id, SIGKILL);
}

#endif
