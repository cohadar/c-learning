//
//  panic.h
//  c-learning
//
//  Created by Damir Cohadarevic on 4/12/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#ifndef __c_learning__panic__
#define __c_learning__panic__

#include <setjmp.h>
#include <assert.h>

extern jmp_buf MC_jmp_buffs[ 256 ];

// WARNING: These macros are neither recursive friendly nor multithreaded.
#define MC_RECOVER( C ) setjmp( MC_jmp_buffs[ (unsigned char) C ] )
#define MC_PANIC( C, CODE ) longjmp( MC_jmp_buffs[ (unsigned char) C ], CODE );

#ifdef DEBUG
extern void MC_PanicSuite();
#endif

#endif /* defined(__c_learning__panic__) */
