//
//  asrt_tests.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/15/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "asrt_tests.h"

#include <stdio.h>
#include "asrt.h"

//---------------------------------------------------------------------------//
//  Make sure every suite has equal number of failing and Ok test.
//  That way it is much easier to check if everything is working as expected.
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
static void suite_Empty() {
}

//---------------------------------------------------------------------------//
static int test_RetZeroOk() {
    return 0;
}

//---------------------------------------------------------------------------//
static int test_RetNonZeroFail() {
    return 77;
}

//---------------------------------------------------------------------------//
static int test_Fail() {
    ASRT_FAIL();
}

//---------------------------------------------------------------------------//
static int test_Failm() {
    ASRT_FAILm("FAILm custom message");
}

//---------------------------------------------------------------------------//
static int test_TrueOk() {
    ASRT_TRUE( 1 );
    return 0;
}

//---------------------------------------------------------------------------//
static int test_TrueFail() {
    ASRT_TRUE( 0 );
    return 0;
}

//---------------------------------------------------------------------------//
static int test_FalseOk() {
    ASRT_FALSE( 0 );
    return 0;
}

//---------------------------------------------------------------------------//
static int test_FalseFail() {
    ASRT_FALSE( 1 );
    return 0;
}

//---------------------------------------------------------------------------//
void suite_RetTests() {
    ASRT_TEST( test_Fail );
    ASRT_TEST( test_Failm );
    ASRT_TEST( test_RetNonZeroFail );
    ASRT_TEST( test_TrueFail );
    ASRT_TEST( test_FalseFail );
    
    ASRT_TEST( test_RetZeroOk );
    ASRT_TEST( test_RetZeroOk );
    ASRT_TEST( test_RetZeroOk );
    ASRT_TEST( test_TrueOk );
    ASRT_TEST( test_FalseOk );
}

//---------------------------------------------------------------------------//
int test_DoubleFail() {
    ASRT_DOUBLE(123.45, 123.55, 0.01);
    return 0;
}

//---------------------------------------------------------------------------//
int test_DoubleOk() {
    ASRT_DOUBLE(123.45, 123.55, 0.2);
    return 0;
}

//---------------------------------------------------------------------------//
void suite_Double() {
    ASRT_TEST( test_DoubleFail );
    ASRT_TEST( test_DoubleOk );
}

//---------------------------------------------------------------------------//
int test_PtrFail() {
    int x, y;
    ASRT_PTR(&x, &y);
    return 0;
}

//---------------------------------------------------------------------------//
int test_PtrAndNull() {
    int x;
    ASRT_PTR(&x, NULL);
    return 0;
}

//---------------------------------------------------------------------------//
int test_PtrAndNull2() {
    int x;
    ASRT_PTR(NULL, &x);
    return 0;
}

//---------------------------------------------------------------------------//
int test_PtrNullNull() {
    int *p = 0;
    ASRT_PTR(p, NULL);
    return 0;
}

//---------------------------------------------------------------------------//
int test_PtrOk() {
    int x;
    ASRT_PTR(&x, &x);
    return 0;
}

//---------------------------------------------------------------------------//
int test_StrFail() {
    ASRT_STRZ("aaa", "aab");
    return 0;
}

//---------------------------------------------------------------------------//
int test_StrAndNull() {
    ASRT_STRZ("xxx", NULL);
    return 0;
}

//---------------------------------------------------------------------------//
int test_StrAndNull2() {
    ASRT_STRZ(NULL, "aaa");
    return 0;
}

//---------------------------------------------------------------------------//
int test_StrNullNull() {
    int *p = 0;
    ASRT_PTR(p, NULL);
    return 0;
}

//---------------------------------------------------------------------------//
int test_StrOk() {
    const char *x = "aaa";
    const char *y = "aaa";
    ASRT_STRZ(x, y);
    return 0;
}


//---------------------------------------------------------------------------//
void suite_Pointers() {
    ASRT_TEST( test_PtrFail );
    ASRT_TEST( test_PtrAndNull );
    ASRT_TEST( test_PtrAndNull2 );
    ASRT_TEST( test_StrFail );
    ASRT_TEST( test_StrAndNull );
    ASRT_TEST( test_StrAndNull2 );
    
    ASRT_TEST( test_PtrNullNull );
    ASRT_TEST( test_PtrOk );
    ASRT_TEST( test_PtrOk );
    ASRT_TEST( test_StrNullNull );
    ASRT_TEST( test_StrOk );
    ASRT_TEST( test_StrOk );

}

//---------------------------------------------------------------------------//
int test_CharOk() {
    ASRT_CHAR('X', 'X');
    return 0;
}

//---------------------------------------------------------------------------//
int test_CharFail() {
    ASRT_CHAR('X', 'Y');
    return 0;
}

//---------------------------------------------------------------------------//
int test_IntOk() {
    ASRT_INT(37, 37);
    return 0;
}

//---------------------------------------------------------------------------//
int test_IntFail() {
    int x = 37;
    int y = 38;
    ASRT_INT(x, y);
    return 0;
}

//---------------------------------------------------------------------------//
int test_UIntOk() {
    ASRT_INT(37, 37);
    return 0;
}

//---------------------------------------------------------------------------//
int test_UIntFail() {
    int x = 37;
    int y = 38;
    ASRT_INT(x, y);
    return 0;
}

//---------------------------------------------------------------------------//
void suite_Ints() {
    ASRT_TEST( test_CharFail );
    ASRT_TEST( test_IntFail );
    ASRT_TEST( test_UIntFail );

    ASRT_TEST( test_CharOk );
    ASRT_TEST( test_IntOk );
    ASRT_TEST( test_UIntOk );
}

//---------------------------------------------------------------------------//
void ASRT_TestsRunAll() {
    ASRT_INIT();
    ASRT_SUITE( suite_Empty );
    ASRT_SUITE( suite_RetTests );
    ASRT_SUITE( suite_Ints );
    ASRT_SUITE( suite_Double );
    ASRT_SUITE( suite_Pointers );
    ASRT_REPORT();
}