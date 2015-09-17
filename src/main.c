//
//  main.c - set to call one of the multiple secondary "soft" main functions.
//  Also runs test suites.
/*
#include <stdio.h>
#include <stdlib.h>
#include "double.h"
#include "MC_tests.h"
#include "cairo_main.h"
 */
#include "main2.h"
#include <assert.h>
#include <float.h>

//---------------------------------------------------------------------------//
int main( int argc, const char * argv[] ) {
    assert(FLT_EVAL_METHOD == 0);
    assert(FLT_ROUNDS == 1);
    /*
	if ( MC_TestsRunAll() == 0 ) {
		return 101;
	}
	// return DoubleMain( argc, argv );
	return cairo_main();
     */
    
    main2();
}
