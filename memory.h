#ifndef F_MEMORY_H
#define F_MEMORY_H
#include "log.h"
#include "settings.h"
#include <stdlib.h>
/**************************************************/
/* Globals vars for once allocated memory blocks  */
/**************************************************/
// commands/base.c                              /**/
char *cmd_uptime_memory = 0;                    /**/
/**************************************************/
// time.h                                       /**/
char *difftime_memory = 0;                      /**/
struct tm *startup_time = 0;                     /**/
/**************************************************/

/**
 * Allocates zero-filled memory in size of count_bytes.
 * If ``block`` ! = 0 then memory filled by zeros
 * if ``count_bytes`` == 0 then given block will be freed
 */
void *allocate_once(void *block, size_t count_bytes){
    if (!block){
        if (count_bytes > 0){
            block = malloc(count_bytes);
            memset(block, 0, count_bytes);
        }
        else if (count_bytes == 0)
        {
            free(block);
        }  
        else{
            #if DI_MEMORY_ALLOCS
                LOG_ERROR("Trying to allocate negative count of bytes. Exiting\n");
            #endif
            exit(EXIT_NEGATIVE_MEMORY_ALLOC);
        }
    }
    else
    {
        memset(block, 0, count_bytes);
        #if DI_MEMORY_ALLOCS
            LOG_INFO("<memory.h> Block allready allocated. Filled by zeros\n");
        #endif
    }
    // Check on success allocation
    if (!block){
        #if DI_MEMORY_ALLOCS
            LOG_ERROR("<memory.h>malloc failed to allocate memory block\n");
        #endif
        exit(EXIT_NO_MEMORY);
    }
    else
    return block;
}

#endif