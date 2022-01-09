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
 * main define:
 * TGW_IMPLEMENTATION: add code for the implementation
 *
 * main functions:
 * void *TGW_ALLOC(size_t size);
 * void  TGW_FREE(void *memory);
 * void *TGW_REALLOC(void *memory, size_t size);
 *
 * memory tracking functions
 * void  TGW_MEMTRACK_INIT(void);
 * void  TGW_MEMTRACK_DUMP(void);
 * void  TGW_MEMTRACK_DESTROY(int32_t still_in_use);
 *
 * extra implementation defines:
 * __OPTIMIZE_SIZE__: Disable memory tracking
 * DEBUG_MEMORY: dump all memory calls
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ############################### */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

void  TGW_MEMTRACK_INIT(void);
void  TGW_MEMTRACK_DUMP(void);
void  TGW_MEMTRACK_DESTROY(int32_t still_in_use);

void *TGW_ALLOC(size_t size);
void *TGW_ALLOC_ZERO(size_t size);
void  TGW_FREE(void *memory);
void *TGW_REALLOC(void *memory, size_t size);

#ifdef TGW_IMPLEMENTATION

/* ############################### */
/*
 * When optimized for small size,
 * then disable all memory tracking
 *
 */

#ifdef __OPTIMIZE_SIZE__
void TGW_MEMTRACK_INIT(void)
{
}
void TGW_MEMTRACK_DUMP(void)
{
}
void TGW_MEMTRACK_DESTROY(int32_t still_in_use)
{
}


#ifndef TGW_ALLOC
void *TGW_ALLOC(size_t size)
{
    return malloc(size);
}
#endif

#ifndef TGW_ALLOC_ZERO
void *TGW_ALLOC_ZERO(size_t size)
{
    void * ptr = TGW_ALLOC(size);

    memset(ptr, 0, size);
    return ptr;
}
#endif


#ifndef TGW_FREE
void  TGW_FREE(void *memory)
{
    free(memory);
}
#endif


#ifndef TGW_REALLOC
void *TGW_REALLOC(void *memory, size_t new_size)
{
    return realloc(old_memory, new_size);
}
#endif

#else

volatile uint64_t memtrack_maxmem = 0;
volatile int32_t  memtrack_allocs = 0;

/* ############################### */
/*
 * ToDo: track size in the memory block
 * ToDo: faster memory functions
 */

void TGW_MEMTRACK_INIT(void)
{

#ifdef DEBUG_MEMORY
    printf("# %s()\n", __FUNCTION__);
#endif
    memtrack_maxmem = 0;
    memtrack_allocs = 0;
}


void TGW_MEMTRACK_DUMP(void)
{
#ifdef DEBUG_MEMORY
    printf("# %s()\n", __FUNCTION__);
#endif
    printf("# %"PRId64" bytes (%"PRId32" allocations in use)\n", memtrack_maxmem, memtrack_allocs);
}


void TGW_MEMTRACK_DESTROY(int32_t still_in_use)
{
#ifdef DEBUG_MEMORY
    printf("# %s(%"PRId32")\n", __FUNCTION__, still_in_use);
#endif

    TGW_MEMTRACK_DUMP();
    if (memtrack_allocs - still_in_use)
    {
        printf("# WARNING: %"PRId32" allocations in use\n", memtrack_allocs - still_in_use);
    }
}


/* ############################### */

#ifndef TGW_ALLOC
void *TGW_ALLOC(size_t size)
{
    /* ToDo: sync */
    memtrack_allocs++;
    memtrack_maxmem += size;
#ifdef DEBUG_MEMORY
    printf("# %s(%zu)\n", __FUNCTION__, size);
#endif
    return size ? malloc(size) : NULL;
}
#endif

#ifndef TGW_ALLOC_ZERO
void *TGW_ALLOC_ZERO(size_t size)
{
    void * ptr;
#ifdef DEBUG_MEMORY
    printf("# %s(%zu)\n", __FUNCTION__, size);
#endif

    ptr = TGW_ALLOC(size);
    memset(ptr, 0, size);
    return ptr;
}
#endif

#ifndef TGW_FREE
void TGW_FREE(void *memory)
{

    /* ToDo: sync */
    memtrack_allocs--;
#ifdef DEBUG_MEMORY
    printf("# %s(%p)\n", __FUNCTION__, memory);
#endif


    free(memory);
}
#endif


#ifndef TGW_REALLOC
void *TGW_REALLOC(void *old_memory, size_t size)
{
#ifdef DEBUG_MEMORY
    printf("# %s(%p,%zu)\n", __FUNCTION__, old_memory, size);
#endif
    /* ToDo: sync */
    memtrack_allocs += (old_memory) ? (size? 1: -1) : 1;
    memtrack_maxmem += size;

    return realloc(old_memory, size);
}
#endif

/* ############################### */
/* close  #ifdef __OPTIMIZE_SIZE__ */
#endif

/* close #ifdef TGW_IMPLEMENTATION */
#endif

#ifdef __cplusplus
}
#endif


