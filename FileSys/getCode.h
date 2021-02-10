#ifndef  GETCODE_H
#define  GETCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>


struct campo {
    char* ptr;
    size_t len;
};

char* realiza_get(char*);

#endif