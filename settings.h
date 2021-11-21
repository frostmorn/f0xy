#ifndef SETTINGS_H
#define SETTINGS_H
#define FOXY_VERSION "0.0.1"
#define EVENT_HANDLER_SLEEP_TIME 1000
#define MUTEX_FILENAME_PATH "/tmp/f0xy_mutex"
#define TOX_SAVEDATA_PATH "savedata.tox"
#define TOX_TMP_SAVEDATA_PATH "savedata.tox.tmp"
#define MUTEX_ERROR -1
#define DI_EVENTS 0
#define COMMAND_TRIGGER '/'
// EXIT CODES:

#define EXIT_OK 0
#define EXIT_CHECKS_FAILED 1
#define EXIT_TERMINATE 2


#if DI_EVENTS
#define DI_COUNT_CREATED_EVENTS 1
#define DI_COUNT_HANDLED_EVENTS 1
#else
#define DI_COUNT_CREATED_EVENTS 0
#define DI_COUNT_HANDLED_EVENTS 0
#endif
#endif
