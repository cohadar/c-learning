//
//  MC_malloc.h
//  c-learning
//
//  Created by Damir Cohadarevic on 4/13/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#ifndef __c_learning__MC_malloc__
#define __c_learning__MC_malloc__

#include <stdlib.h>

#define MC_MALLOC_MAX_MEM 1024*1024*1024

extern void* MC_malloc( size_t size );
extern void* MC_calloc( size_t count, size_t size );
extern void* MC_realloc( void *p, size_t size );
extern void  MC_free( void *p );

#endif /* defined(__c_learning__MC_malloc__) */
