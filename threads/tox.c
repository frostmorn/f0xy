#ifndef F_TOX_H
#define F_TOX_H
#include "../log.h"
#include "../events/events.c"
#include <unistd.h>
#include <sodium/utils.h>
#include <tox/tox.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../types/types.c"

void update_savedata_file(const Tox *tox)
{
	size_t size = tox_get_savedata_size(tox);
	uint8_t *savedata = (uint8_t*)malloc(size);
	tox_get_savedata(tox, savedata);

	FILE *f = fopen(TOX_TMP_SAVEDATA_PATH, "wb");
	fwrite(savedata, size, 1, f);
	fclose(f);

	rename(TOX_TMP_SAVEDATA_PATH, TOX_SAVEDATA_PATH);

	free(savedata);
}

void print_tox_id(Tox *tox)
{
	uint8_t tox_id_bin[TOX_ADDRESS_SIZE];
	tox_self_get_address(tox, tox_id_bin);

	char tox_id_hex[TOX_ADDRESS_SIZE*2 + 1];
	sodium_bin2hex(tox_id_hex, sizeof(tox_id_hex), tox_id_bin, sizeof(tox_id_bin));

	for (size_t i = 0; i < sizeof(tox_id_hex)-1; i ++) {
	    tox_id_hex[i] = toupper(tox_id_hex[i]);
	}

	LOG_INFO_X("<tox.c>\tTox ID: %s\n", tox_id_hex);
}

void friend_request_cb(Tox *tox, const uint8_t *public_key, const uint8_t *message, 
		size_t length, void *user_data)
{
	
	struct ToxFriendRequest *f_req	=	malloc(sizeof(struct ToxFriendRequest));
	f_req->tox			=	tox;
	f_req->public_key		=	public_key;
	f_req->message			=	(uint8_t *)malloc(sizeof(uint8_t)*length+1);
	f_req->length			=	length;
	f_req->user_data		=	user_data;

	memcpy(f_req->message, message, length);	
	f_req->message[length]=0;		// Null terminator
	
	// tox_friend_add_norequest(tox, public_key, NULL);
	createEvent(TOX_FRIEND_REQUEST_EVENT, f_req, sizeof(struct ToxFriendRequest));
	update_savedata_file(tox);
}

void friend_message_cb(Tox *tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, 
		const uint8_t *message, size_t length, void *user_data)
{

	struct ToxMessage *msg = malloc(sizeof(struct ToxMessage));
	msg->tox		=	tox;
	msg->friend_number	=	friend_number;
	msg->type		=	type;
	msg->message		=	(uint8_t *)malloc(sizeof(uint8_t)*length+1);
	msg->length		=	length;
	msg->user_data		=	user_data;	
	
	memcpy(msg->message, message, length);
	msg->message[length]=0;		// Null terminator
	
	createEvent(TOX_MESSAGE_EVENT, msg, sizeof(struct ToxMessage));
}

Tox *create_tox()
{
	Tox *tox;

	struct Tox_Options options;

	tox_options_default(&options);

	FILE *f = fopen(TOX_SAVEDATA_PATH, "rb");
	if (f) {
	    fseek(f, 0, SEEK_END);
	    long fsize = ftell(f);
	    fseek(f, 0, SEEK_SET);

	    uint8_t *savedata = (uint8_t *)malloc(fsize);

	    fread(savedata, fsize, 1, f);
	    fclose(f);

	    options.savedata_type = TOX_SAVEDATA_TYPE_TOX_SAVE;
	    options.savedata_data = savedata;
	    options.savedata_length = fsize;

	    tox = tox_new(&options, NULL);

	    free(savedata);
	} else {
	    tox = tox_new(&options, NULL);
	}
	return tox;
}


void run_tox(){
	Tox *tox = create_tox();

	size_t length = tox_self_get_name_size(tox);
	uint8_t *name = (uint8_t *)malloc(length);
	if (!name) {
		LOG_ERROR("<tox.c>\tINIT TOX FAILED");	
		abort();
	}
	tox_self_get_name(tox, name);
	
	for (int i = 0; i < length; ++i){
		LOG_INFO_X("%c", name+i);
	}

	LOG_INFO ("<tox.c>\tTOX STARTED\r\n");
	update_savedata_file(tox);

	print_tox_id(tox);

	tox_callback_friend_request(tox, friend_request_cb);
	
	tox_callback_friend_message(tox, friend_message_cb);
	
	while (1){
		usleep(tox_iteration_interval(tox) * 1000);
		tox_iterate(tox, NULL);
	}

}


void * toxCommunicateThread(void * args)
{
	LOG_INFO("<tox.c>\tStarting toxCommunicateThread\n");
	run_tox();
	LOG_INFO("<tox.c>\ttoxCommunicateThread\n");
	
	return NULL;
}
#endif
