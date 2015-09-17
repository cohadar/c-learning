//
//  panic.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/12/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "MC_panic.h"
#include <setjmp.h>
#include <assert.h>

//---------------------------------------------------------------------------//
jmp_buf MC_jmp_buffs[ 256 ];


#ifdef DEBUG
#include "asrt.h"
//---------------------------------------------------------------------------//
static int MC_TestPanic() {
    if ( MC_RECOVER( 'A' ) == 0 ) {
        MC_PANIC( 'A', 77 );
    } else {
        return 0;
    }
    ASRT_FAILm( "Panic did not recover" );
}

//---------------------------------------------------------------------------//
extern int MC_TestNestedPanic() {
    if ( MC_RECOVER( 'A' ) == 0 ) {
        if ( MC_RECOVER( 'B' ) == 0 ) {
            MC_PANIC( 'B', 77 );
        } else {
            MC_PANIC( 'A', 77 );
        }
        ASRT_FAILm( "Panic did not recover B" );
    } else {
        return 0;
    }
    ASRT_FAILm( "Panic did not recover A" );
}

//---------------------------------------------------------------------------//
void MC_PanicSuite() {
    ASRT_TEST( MC_TestPanic );
    ASRT_TEST( MC_TestNestedPanic );
}

#endif // DEBUG

