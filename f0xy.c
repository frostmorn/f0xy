#include <stdlib.h>
#include "checks/checks.c"
#include "threads/threads.c"
#include "signals.c"
#define EXIT_OK 0
#define EXIT_CHECKS_FAILED 1


int main() {
	if (PerformChecks() != CHECKS_OK){
		exit(EXIT_CHECKS_FAILED);
	}
	LOG_INFO("----> Checks completed! We are in!\n");
	
	register_signal_catchers();

	StartThreads();
	return 0;
}
