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

void StartThreads(){
	LOG_F_CALL("<threads.c> StartThreads()");

	int err_eventHandlerThread = 
		pthread_create(&eventHandlerThread_id, NULL, &eventHandlerThread, NULL);	
	
	int err_toxCommunicateThread = 
		pthread_create(&toxCommunicateThread_id, NULL, &toxCommunicateThread, NULL);

	//	TODO:	Handle errors
	while (1){usleep(1000000);}
}

void StopThreads(){
	LOG_INFO("Killing Threads\n");
	pthread_kill(eventHandlerThread_id, SIGKILL);
	// TODO: Save tox data on kill
	pthread_kill(toxCommunicateThread_id, SIGKILL);
	
}

#endif
