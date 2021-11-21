#ifndef F_SIGNAL_CATCHER
#define F_SIGNAL_CATCHER

#include "log.h"
#include "checks/checks.c"
#include <signal.h>
#include <unistd.h>

#include "threads/threads.c"
#include "settings.h"

void default_exit_handler(int signum, siginfo_t *info, void *ptr)
{
	// TODO: Handle signal as events
	LOG_INFO_X("<signal.c> SIGNAL %d recieved\n", signum);
	UnlockFileMutex();
	StopThreads();
	exit(EXIT_TERMINATE);
}

int catch_signal(int signal, void(handler_func)(int signum, siginfo_t *info, void *ptr))
{

	static struct sigaction _sigact;

	memset(&_sigact, 0, sizeof(_sigact));
	_sigact.sa_sigaction = handler_func;
	_sigact.sa_flags = SA_SIGINFO;

	sigaction(signal, &_sigact, NULL);
}

int register_signal_catchers()
{
	LOG_INFO("<signal.c> Registering signal catchers\n");
	catch_signal(SIGINT, default_exit_handler);
	catch_signal(SIGTERM, default_exit_handler);
}

#endif
