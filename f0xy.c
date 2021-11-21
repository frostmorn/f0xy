#include <stdlib.h>
#include "checks/checks.c"
#include "threads/threads.c"
#include "signals.c"
#include "time.h"

int main()
{
	if (PerformChecks() != CHECKS_OK)
	{
		exit(EXIT_CHECKS_FAILED);
	}
	LOG_INFO("----> Checks completed! We are in!\n");

	register_signal_catchers();
	SetStartupTime();
	StartThreads();
	return 0;
}
