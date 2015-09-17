//
//  MC_arena.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/12/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "MC_arena.h"
#include <stdlib.h>
#include <assert.h>

//---------------------------------------------------------------------------//
struct MC_Arena {
    int count;
    int max_allocations;
    void** allocated;
};

//---------------------------------------------------------------------------//
MC_Arena * MC_ArenaNew( int max_allocations ) {
    assert( max_allocations > 0 );
    MC_Arena *arena = malloc( sizeof( *arena ) );
    if ( arena == NULL ) {
        return NULL;
    }
    arena->allocated = malloc( max_allocations * sizeof( void* ) );
    if ( arena->allocated == NULL ) {
        free( arena );
        return NULL;
    }
    arena->count = 0;
    arena->max_allocations = max_allocations;
    return arena;
}

//---------------------------------------------------------------------------//
void MC_ArenaFree( MC_Arena **arena_ref ) {
    assert( arena_ref );
    MC_Arena *arena = *arena_ref;
    assert( arena );
    for ( int i = 0; i < arena->count; i++ ) {
        free( arena->allocated[ i ] );
    }
    free( arena );
    *arena_ref = NULL;
}

//---------------------------------------------------------------------------//
void * MC_ArenaAlloc( MC_Arena *arena, size_t size ) {
    assert( arena );
    assert( size > 0 );
    assert( arena->count < arena->max_allocations );
    void *p = calloc( 1, size );
    if ( p == NULL ) {
        return NULL;
    }
    arena->allocated[ arena->count++ ] = p;
    return p;
}

#ifdef DEBUG
#include "asrt.h"
//---------------------------------------------------------------------------//
static int TestArenaAlloc() {
    int COUNT = 100;
    int ARRAYS = 200;
    MC_Arena *arena = MC_ArenaNew( 1000 );
    ASRT_TRUE( arena );
    for ( int a = 0; a < ARRAYS; a++ ) {
        int *x = MC_ArenaAlloc( arena, COUNT * sizeof( *x ) );
        int *y = MC_ArenaAlloc( arena, COUNT * sizeof( *y ) );
        for ( int i = 0; i < COUNT; i++ ) {
            ASRT_INT( 0, x[i] );
            ASRT_INT( 0, y[i] );
            x[i] = i;
            y[i] = i;
        }
        for ( int i = 0; i < COUNT; i++ ) {
            ASRT_INT( i, x[i] );
            ASRT_INT( i, y[i] );
        }
    }
    MC_ArenaFree( &arena );
    ASRT_TRUE( arena == NULL );
    return 0;
}

//---------------------------------------------------------------------------//
void MC_ArenaSuite() {
    ASRT_TEST( TestArenaAlloc );
}

#endif // DEBUG
