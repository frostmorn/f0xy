#ifndef F_TYPES
#define F_TYPES

#include <tox/tox.h>
/********************************************************/
/*						EVENT TYPES						*/
/********************************************************/

#define TDEFAULT_EVENT 0

/********************************************************/
/*							TOX							*/
/********************************************************/
#define TOX_FRIEND_REQUEST_EVENT 1
#define TOX_MESSAGE_EVENT 2
/********************************************************/

struct Event
{
	uint32_t type;
	size_t length;
	void *data;
	time_t timestamp;
};
struct Callback
{
	//	void(void *)*	callback=0;
	uint32_t event_type;
};

//	Event Types:
struct ToxMessage
{
	Tox *tox;
	uint32_t friend_number;
	TOX_MESSAGE_TYPE type;
	uint8_t *message;
	size_t length;
	void *user_data;
};

struct ToxFriendRequest
{
	Tox *tox;
	const uint8_t *public_key;
	uint8_t *message;
	size_t length;
	void *user_data;
};

#endif
