/*
 * Copyright (c) 2021-22 Detlef Riekenberg
 * 
 * You have the option to choose between two licenses:
 * Select either the MIT License
 * or the public domain license.
 *
 * See the LICENSE file
 *
 * newest version:
 * https://www.github.com/winspool/tgwatcher
 * 
 * ############################## */

#ifdef __cplusplus
extern "C" {
#endif

/* ############################## */

#define TGW_IMPLEMENTATION
#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>

#include "tgw_memory.h"


/* ############################## */

int main(int argc, char **argv)
{

    TGW_MEMTRACK_INIT();

    puts("Hello World\n");

    TGW_MEMTRACK_DESTROY(0);
    printf("end of %s\n", __FUNCTION__);
    return 0;
}

/* ############################## */

#ifdef __cplusplus
}
#endif

