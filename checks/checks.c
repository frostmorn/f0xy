#ifndef CHECKS_H
#define CHECKS_H
#define CHECKS_OK 0
#include "../settings.h"
#include "../log.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
int f0xy_mutex_file = -1;

int FileMutexCheck()
{
	LOG_F_CALL("<checks.c> MutexCheck()[NOT_IMPLEMENTED]");
	f0xy_mutex_file = open(MUTEX_FILENAME_PATH, O_CREAT);

	if (f0xy_mutex_file != -1)
		return CHECKS_OK;
	else
		LOG_ERROR("MUTEX_ERROR happened. exiting...")
	return MUTEX_ERROR;
}
void UnlockFileMutex()
{
	LOG_INFO("<checks.c> UnlockFileMutex()\n");
	flock(f0xy_mutex_file, LOCK_UN);
	close(f0xy_mutex_file);
	remove(MUTEX_FILENAME_PATH);
}
int PerformChecks()
{
	LOG_F_CALL("<checks.c> PerformChecks()");
	return FileMutexCheck();
}

#endif
