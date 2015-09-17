//
//  MC_malloc.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/13/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "MC_malloc.h"

static size_t availableMemory = MC_MALLOC_MAX_MEM;

//---------------------------------------------------------------------------//
void* MC_malloc( size_t size ) {
    if ( availableMemory < size ) {
        return NULL;
    }
    availableMemory -= size;
    return malloc( size );
}

//---------------------------------------------------------------------------//
void* MC_calloc( size_t count, size_t size ) {
    if ( availableMemory < size ) {
        return NULL;
    }
    availableMemory -= size;
    return calloc( count, size );
}

//---------------------------------------------------------------------------//
void* MC_realloc( void *p, size_t size ) {
    if ( availableMemory < size ) {
        return NULL;
    }
    availableMemory -= size;
    return realloc( p, size );
}

//---------------------------------------------------------------------------//
extern void  MC_free( void *p ) {
    // availableMemory += size;
    free( p );
}

