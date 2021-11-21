#include <stdlib.h>
#include "checks/checks.c"
#include "threads/threads.c"
#include "signals.c"


int main()
{
	if (PerformChecks() != CHECKS_OK)
	{
		exit(EXIT_CHECKS_FAILED);
	}
	LOG_INFO("----> Checks completed! We are in!\n");

	register_signal_catchers();

	StartThreads();
	return 0;
}
