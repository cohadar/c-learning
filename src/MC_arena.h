//
//  MC_arena.h
//  c-learning
//
//  Created by Damir Cohadarevic on 4/12/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#ifndef __c_learning__MC_arena__
#define __c_learning__MC_arena__

#include <stdlib.h>

#ifdef DEBUG
extern void MC_ArenaSuite();
#endif

typedef struct MC_Arena MC_Arena;

extern MC_Arena *  MC_ArenaNew( int max_allocations );
extern void        MC_ArenaFree( MC_Arena **arena_ref );
extern void *      MC_ArenaAlloc( MC_Arena *arena, size_t size );

#endif /* defined(__c_learning__MC_arena__) */
