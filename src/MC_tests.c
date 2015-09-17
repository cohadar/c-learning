//
//  MC_tests.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/12/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "MC_tests.h"

//---------------------------------------------------------------------------//
// if DEBUG is undefined no tests will be run
//---------------------------------------------------------------------------//
#ifdef DEBUG
#include "double.h"
#include "MC_stack.h"
#include "MC_atom.h"
#include "MC_panic.h"
#include "MC_arena.h"
#include "MC_list.h"
#include "asrt.h"
#include "asrt_tests.h"
#endif

//---------------------------------------------------------------------------//
// Set up, run suite(s) of tests, report pass/fail/skip stats.
//---------------------------------------------------------------------------//
int MC_TestsRunAll() {
#ifdef DEBUG
    
    ASRT_TestsRunAll();
    
    ASRT_INIT();
    ASRT_SUITE( DoubleSuite );
    ASRT_SUITE( MC_StackSuite );
    ASRT_SUITE( MC_AtomSuite );
    ASRT_SUITE( MC_PanicSuite );
    ASRT_SUITE( MC_ArenaSuite );
    ASRT_SUITE( MC_ListSuite );
    ASRT_REPORT();
    
    return ASRT_ALL_OK();
#else
    return 1;
#endif
}
