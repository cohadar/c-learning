/******************************************************************************
 The MIT License (MIT)

 Copyright (c) 2015 Damir Cohadarevic

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
//===========================================================================//
//  ASRT - C99 unit testing library
//  File: asrt.c
//===========================================================================//

#include "asrt.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

//===========================================================================//
//  Print functions, format to your desire.
//===========================================================================//

//---------------------------------------------------------------------------//
static void ASRT_PrintFail( const char *fileName, int fileLine, const char *message, const char *testName ) {
    printf( "\n(f) %s %s:%d", testName, fileName, fileLine );
    if ( message ) {
        printf( "\n  %s", message );
    }
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailStrz( const char *expected, const char *actual ) {
    if ( expected ) {
        printf( "\n  Expected: \"%s\"", expected );
    } else {
        printf( "\n  Expected: NULL" );
    }
    if ( actual ) {
        printf( "\n  Actual  : \"%s\"", actual );
    } else {
        printf( "\n  Actual  : NULL" );
    }
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailChar( int expected, int actual ) {
    printf( "\n  Expected: '%c', Actual: '%c'", expected, actual );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailInt( int expected, int actual ) {
    printf( "\n  Expected: %d, Actual: %d", expected, actual );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailUInt( unsigned int expected, unsigned int actual ) {
    printf( "\n  Expected: %u, Actual: %u", expected, actual );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailSize_t( size_t expected, size_t actual ) {
    printf( "\n  Expected: %zu, Actual: %zu", expected, actual );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailDouble( double expected, double actual, double delta ) {
    printf( "\n  Expected: %f, Actual: %f, Delta: %f", expected, actual, delta );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintFailPtr( const void *expected, const void *actual ) {
    printf( "\n  Expected: %p, Actual: %p", expected, actual );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintPass( const char *testName ) {
    // printf( "\n(p) %s", testName );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintBadTest( const char *testName, const char *fileName, int fileLine, int exitCode ) {
    printf( "\n(b) %s %s:%d", testName, fileName, fileLine );
    printf( "\n  Test returned %d, did you forget to use ASRT_FAIL ?", exitCode );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintBeforeSuite( const char *suiteName ) {
    // none
}

//---------------------------------------------------------------------------//
static void ASRT_PrintAfterSuite( const char *suiteName, int passed, int failed, double seconds ) {
    if ( failed == 0 ) {
        printf( "\n[OK:%d] %s, sec: %.3f", passed, suiteName, seconds );
    } else {
        printf( "\n[F:%d, P:%d] %s, sec: %.3f", failed, passed, suiteName, seconds );
    }
    printf( "\n================================" );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintInit() {
    printf( "\nRunning tests" );
    printf( "\n================================" );
}

//---------------------------------------------------------------------------//
static void ASRT_PrintReport( int passed, int failed, double seconds ) {
    if ( failed == 0 ) {
        printf( "\nALL OK: %d, sec: %.3f\n", passed, seconds );
    } else {
        printf( "\nFAIL: %d, PASS: %d, sec: %.3f\n", failed, passed, seconds );
    }
}

//===========================================================================//
//  Implementation, do not change below this line.
//===========================================================================//

//---------------------------------------------------------------------------//
static struct ASRT_Suite {
    const char *name;
    int passed;
    int failed;
    clock_t start;
    clock_t end;
    void (*before)();
    void (*after)();
} p_suite, p_total;

//---------------------------------------------------------------------------//
static struct ASRT_Mark {
    const char *message;
    const char *fileName;
    int fileLine;
    int result;
} p_mark;

//---------------------------------------------------------------------------//
static union {
    int p_int;
    unsigned int p_uint;
    size_t p_size_t;
    double p_double;
    const char *p_strz;
    const void *p_void;
} p_expected, p_actual, p_delta;

//---------------------------------------------------------------------------//
static void ASRT_ClearSuite( struct ASRT_Suite *suite, const char *suiteName ) {
    suite->name = suiteName;
    suite->passed = 0;
    suite->failed = 0;
    suite->start = 0;
    suite->end = 0;
    suite->before = NULL;
    suite->after = NULL;
}

//---------------------------------------------------------------------------//
static void ASRT_ClearMark( struct ASRT_Mark *mark ) {
    mark->message = NULL;
    mark->fileName = NULL;
    mark->fileLine = 0;
    mark->result = 0;
}

//---------------------------------------------------------------------------//
static void ASRT_UpdateTotal( struct ASRT_Suite *total, struct ASRT_Suite *suite ) {
    total->passed += suite->passed;
    total->failed += suite->failed;
}

//---------------------------------------------------------------------------//
static double ASRT_Seconds( clock_t start, clock_t end ) {
    return (double) ( end - start ) / ( 1.0 * CLOCKS_PER_SEC );
}

//---------------------------------------------------------------------------//
void ASRT_Init() {
    ASRT_ClearSuite( &p_suite, NULL );
    ASRT_ClearSuite( &p_total, NULL );
    ASRT_ClearMark( &p_mark );
    ASRT_PrintInit();
    p_total.start = clock();
}

//---------------------------------------------------------------------------//
void ASRT_Report() {
    p_total.end = clock();
    ASRT_PrintReport( p_total.passed, p_total.failed, ASRT_Seconds( p_total.start, p_total.end ) );
}

//---------------------------------------------------------------------------//
int ASRT_AllOk() {
    return p_total.failed == 0;
}

//---------------------------------------------------------------------------//
void ASRT_Suite( const char *suiteName, void suite( void ) ) {
    ASRT_ClearSuite( &p_suite, suiteName );
    ASRT_ClearMark( &p_mark );

    ASRT_PrintBeforeSuite( suiteName );
    p_suite.start = clock();
    suite();
    p_suite.end = clock();
    ASRT_UpdateTotal( &p_total, &p_suite );
    ASRT_PrintAfterSuite( suiteName, p_suite.passed, p_suite.failed, ASRT_Seconds( p_suite.start, p_suite.end ) );
}

//---------------------------------------------------------------------------//
void ASRT_SetBefore( void before() ) {
    p_suite.before = before;
}

//---------------------------------------------------------------------------//
void ASRT_SetAfter( void after() ) {
    p_suite.after = after;
}

//---------------------------------------------------------------------------//
void ASRT_RunBefore() {
    if ( p_suite.before ) {
        p_suite.before();
    }
}

//---------------------------------------------------------------------------//
void ASRT_RunAfter() {
    if ( p_suite.after ) {
        p_suite.after();
    }
}

//---------------------------------------------------------------------------//
//  Magic numbers for decoding test results ( WARNING: subject to change )
//---------------------------------------------------------------------------//
enum ASRT_RESULT {
    ASRT_RESULT_FAIL = 0x37CF,
    ASRT_RESULT_FAIL_STRZ,
    ASRT_RESULT_FAIL_CHAR,
    ASRT_RESULT_FAIL_INT,
    ASRT_RESULT_FAIL_UINT,
    ASRT_RESULT_FAIL_SIZE_T,
    ASRT_RESULT_FAIL_DOUBLE,
    ASRT_RESULT_FAIL_PTR,
};

//---------------------------------------------------------------------------//
void ASRT_TestReport( const char *fileName, int fileLine, const char *testName, int testResult ) {
    if ( p_mark.result == 0 ) {
        if ( testResult == 0 ) {
            p_suite.passed++;
            ASRT_PrintPass( testName );
        } else {
            p_suite.failed++;
            ASRT_PrintBadTest( testName, fileName, fileLine, testResult );
        }
        ASRT_ClearMark( &p_mark );
        return;
    }
    switch ( p_mark.result ) {
        case ASRT_RESULT_FAIL:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            break;
        case ASRT_RESULT_FAIL_STRZ:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailStrz( p_expected.p_strz, p_actual.p_strz );
            break;
        case ASRT_RESULT_FAIL_CHAR:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailChar( p_expected.p_int, p_actual.p_int );
            break;
        case ASRT_RESULT_FAIL_INT:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailInt( p_expected.p_int, p_actual.p_int );
            break;
        case ASRT_RESULT_FAIL_UINT:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailUInt( p_expected.p_uint, p_actual.p_uint );
            break;
        case ASRT_RESULT_FAIL_SIZE_T:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailSize_t( p_expected.p_size_t, p_actual.p_size_t );
            break;
        case ASRT_RESULT_FAIL_DOUBLE:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailDouble( p_expected.p_double, p_actual.p_double, p_delta.p_double );
            break;
        case ASRT_RESULT_FAIL_PTR:
            p_suite.failed++;
            ASRT_PrintFail( p_mark.fileName, p_mark.fileLine, p_mark.message, testName );
            ASRT_PrintFailPtr( p_expected.p_void, p_actual.p_void );
            break;
        default :
            p_suite.failed++;
            ASRT_PrintBadTest( testName, fileName, fileLine, testResult );
    }
    ASRT_ClearMark( &p_mark );
}

//---------------------------------------------------------------------------//
//  Should be called before any of the functions below
//---------------------------------------------------------------------------//
void ASRT_Mark( const char *fileName, int fileLine, const char *message ) {
    p_mark.message = message;
    p_mark.fileName = fileName;
    p_mark.fileLine = fileLine;
    p_mark.result = 0;
}

//---------------------------------------------------------------------------//
int ASRT_Fail() {
    p_mark.result = ASRT_RESULT_FAIL;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_True( int condition ) {
    if ( condition ) {
        return 0;
    }
    p_mark.result = ASRT_RESULT_FAIL;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_Strz( const char *expected, const char *actual ) {
    if ( expected == NULL && actual == NULL ) {
        return 0;
    }
    if ( expected != NULL && actual != NULL ) {
        if ( strcmp( expected, actual ) == 0 ) {
            return 0;
        }
    }
    p_expected.p_strz = expected;
    p_actual.p_strz = actual;
    p_mark.result = ASRT_RESULT_FAIL_STRZ;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_Char( char expected, char actual ) {
    if ( expected == actual ) {
        return 0;
    }
    p_expected.p_int = expected;
    p_actual.p_int = actual;
    p_mark.result = ASRT_RESULT_FAIL_CHAR;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_Int( int expected, int actual ) {
    if ( expected == actual ) {
        return 0;
    }
    p_expected.p_int = expected;
    p_actual.p_int = actual;
    p_mark.result = ASRT_RESULT_FAIL_INT;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_UInt( unsigned int expected, unsigned int actual ) {
    if ( expected == actual ) {
        return 0;
    }
    p_expected.p_uint = expected;
    p_actual.p_uint = actual;
    p_mark.result = ASRT_RESULT_FAIL_UINT;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_Size_t( size_t expected, size_t actual ) {
    if ( expected == actual ) {
        return 0;
    }
    p_expected.p_size_t = expected;
    p_actual.p_size_t = actual;
    p_mark.result = ASRT_RESULT_FAIL_SIZE_T;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_Double( double expected, double actual, double delta ) {
    if ( fabs( expected - actual ) <= delta  ) {
        return 0;
    }
    p_expected.p_double = expected;
    p_actual.p_double = actual;
    p_delta.p_double = delta;
    p_mark.result = ASRT_RESULT_FAIL_DOUBLE;
    return 1;
}

//---------------------------------------------------------------------------//
int ASRT_Ptr( const void *expected, const void *actual ) {
    if ( expected == actual ) {
        return 0;
    }
    p_expected.p_void = expected;
    p_actual.p_void = actual;
    p_mark.result = ASRT_RESULT_FAIL_PTR;
    return 1;
}


