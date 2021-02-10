#ifndef  EMAIL_H
#define  EMAIL_H

#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
 

struct upload_status {
    const char *rptr;
    size_t sizl;
};

int enviar_email(const char*, const char* , const char* , const char* );


#endif