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
//  File: asrt.h
//===========================================================================//

#ifndef ASRT_INCLUDED_H
#define ASRT_INCLUDED_H

//---------------------------------------------------------------------------//
//  We use a lot of C99 features, lets test for it explicitly.
//---------------------------------------------------------------------------//
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ < 199901
        #error You need a newer C compiler
    #endif
#elif _MSC_VER
    #if _MSC_VER < 1800
        #error You need a newer MSVC++ compiler
    #endif
#else
    #error You need a real C compiler
#endif

//---------------------------------------------------------------------------//
//  Call ASRT_INIT before ASRT_SUITE calls.
//---------------------------------------------------------------------------//
#define ASRT_INIT() ASRT_Init()

//---------------------------------------------------------------------------//
//  Call ASRT_REPORT after ASRT_SUITE calls.
//---------------------------------------------------------------------------//
#define ASRT_REPORT() ASRT_Report()

//---------------------------------------------------------------------------//
//  Call ASRT_ALL_OK after ASRT_REPORT to find out if all tests passed.
//---------------------------------------------------------------------------//
#define ASRT_ALL_OK() ASRT_AllOk()

//---------------------------------------------------------------------------//
//  Runs a test suite. Must be void function.
//---------------------------------------------------------------------------//
#define ASRT_SUITE( SUITE ) ASRT_Suite( #SUITE, SUITE )

//---------------------------------------------------------------------------//
//  Specify a void function to be executed before every test in a suite.
//---------------------------------------------------------------------------//
#define ASRT_BEFORE( SETUP ) ASRT_SetBefore( SETUP )

//---------------------------------------------------------------------------//
//  Specify a void function to be executed after every test in a suite.
//---------------------------------------------------------------------------//
#define ASRT_AFTER( TEARDOWN ) ASRT_SetAfter( TEARDOWN )

//---------------------------------------------------------------------------//
//  Runs a test function. Call only from inside Suite functions.
//  Test functions return int and can have variable number of arguments.
//  Test passes when it returns 0.
//---------------------------------------------------------------------------//
#define ASRT_TEST( TEST, ... ) ASRT_INVOKE( #TEST, TEST( __VA_ARGS__ ) )

//---------------------------------------------------------------------------//
//  ASRT MACROS, use 'em often.
//---------------------------------------------------------------------------//
#define ASRT_FAIL()                    ASRT_FAILm(   NULL )
#define ASRT_TRUE(   COND )            ASRT_TRUEm(   #COND, COND )
#define ASRT_FALSE(  COND )            ASRT_FALSEm(  #COND, COND )
#define ASRT_EQ(     EXP, GOT )        ASRT_EQm(     #EXP " == " #GOT, EXP, GOT )
#define ASRT_NEQ(    EXP, GOT )        ASRT_NEQm(    #EXP " != " #GOT, EXP, GOT )
#define ASRT_CHAR(   EXP, GOT )        ASRT_CHARm(   #EXP " == " #GOT, EXP, GOT )
#define ASRT_INT(    EXP, GOT )        ASRT_INTm(    #EXP " == " #GOT, EXP, GOT )
#define ASRT_UINT(   EXP, GOT )        ASRT_UINTm(   #EXP " == " #GOT, EXP, GOT )
#define ASRT_SIZE_T( EXP, GOT )        ASRT_SIZE_Tm( #EXP " == " #GOT, EXP, GOT )
#define ASRT_DOUBLE( EXP, GOT, DELTA ) ASRT_DOUBLEm( #EXP " == " #GOT, EXP, GOT, DELTA )
#define ASRT_PTR(    EXP, GOT )        ASRT_PTRm(    #EXP " == " #GOT, EXP, GOT )
#define ASRT_STRZ(   EXP, GOT )        ASRT_STRZm(   #EXP " == " #GOT, EXP, GOT )

#define ASRT_FAILm(   MSG )                  ASRT_MRET( MSG, ASRT_Fail() )
#define ASRT_TRUEm(   MSG, COND )            ASRT_MARK( MSG, ASRT_True( !!(COND) ) )
#define ASRT_FALSEm(  MSG, COND )            ASRT_MARK( MSG, ASRT_True( !(COND) ) )
#define ASRT_EQm(     MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_True( EXP == GOT ) )
#define ASRT_NEQm(    MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_True( EXP != GOT ) )
#define ASRT_CHARm(   MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_Char( EXP, GOT ) )
#define ASRT_INTm(    MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_Int( EXP, GOT ) )
#define ASRT_UINTm(   MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_UInt( EXP, GOT ) )
#define ASRT_SIZE_Tm( MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_Size_t( EXP, GOT ) )
#define ASRT_DOUBLEm( MSG, EXP, GOT, DELTA ) ASRT_MARK( MSG, ASRT_Double( EXP, GOT, DELTA ) )
#define ASRT_PTRm(    MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_Ptr( EXP, GOT ) )
#define ASRT_STRZm(   MSG, EXP, GOT )        ASRT_MARK( MSG, ASRT_Strz( EXP, GOT ) )

//---------------------------------------------------------------------------//
//  Macro boilerplates, do not use directly.
//---------------------------------------------------------------------------//
#define ASRT_MARK( MSG, ASRT ) \
    do { \
        ASRT_Mark( __FILE__, __LINE__, MSG ); \
        if ( ASRT ) { return 1; }; \
    } while (0)

#define ASRT_MRET( MSG, ASRT ) \
    do { \
        ASRT_Mark( __FILE__, __LINE__, MSG ); \
        return ASRT; \
    } while (0)

#define ASRT_INVOKE( TEST_NAME, TEST_CALL ) \
    do { \
        ASRT_RunBefore(); \
        ASRT_TestReport( __FILE__, __LINE__, TEST_NAME, TEST_CALL ); \
        ASRT_RunAfter(); \
    } while (0)

//---------------------------------------------------------------------------//
//  Low level API, use ASRT MACROS instead, it is easier.
//---------------------------------------------------------------------------//
#include <stdlib.h>

extern void ASRT_Init();
extern void ASRT_Report();
extern int  ASRT_AllOk();
extern void ASRT_SetBefore( void before() );
extern void ASRT_SetAfter( void after() );
extern void ASRT_RunBefore();
extern void ASRT_RunAfter();
extern void ASRT_Suite( const char *suiteName, void suite( void ) );
extern void ASRT_TestReport( const char *fileName, int fileLine, const char *testName, int testResult );
extern void ASRT_Mark( const char *fileName, int fileLine, const char *message );

extern int ASRT_Fail();
extern int ASRT_True( int condition );
extern int ASRT_Char( char expected, char actual );
extern int ASRT_Int( int expected, int actual );
extern int ASRT_UInt( unsigned int expected, unsigned int actual );
extern int ASRT_Size_t( size_t expected, size_t actual );
extern int ASRT_Double( double expected, double actual, double delta );
extern int ASRT_Ptr( const void *expected, const void *actual );
extern int ASRT_Strz( const char *expected, const char *actual );

#endif /* ASRT_INCLUDED_H */
