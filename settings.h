#ifndef SETTINGS_H
#define SETTINGS_H
#define EVENT_HANDLER_SLEEP_TIME 1000
#define MUTEX_FILENAME_PATH "/tmp/f0xy_mutex"
#define TOX_SAVEDATA_PATH "savedata.tox"
#define TOX_TMP_SAVEDATA_PATH "savedata.tox.tmp"
#define MUTEX_ERROR -1
#define SIGTERM_EXIT_CODE 107
#define DI_EVENTS 0
#if DI_EVENTS
#define DI_COUNT_CREATED_EVENTS 1
#define DI_COUNT_HANDLED_EVENTS 1
#else
#define DI_COUNT_CREATED_EVENTS 0
#define DI_COUNT_HANDLED_EVENTS 0
#endif
#endif
