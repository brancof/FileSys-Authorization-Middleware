#ifndef  VERIFY_H
#define  VERIFY_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "getCode.h"

#include "config.h"

char* generateCode();

char* le_email(char*);

int loop_get_verify(char*);

#endif