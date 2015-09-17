//
//  MC_List.c
//  c-learning
//
//  Created by Damir Cohadarevic on 4/13/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#include "MC_list.h"
#include "MC_malloc.h"
#include <assert.h>
#include <stdarg.h>

//---------------------------------------------------------------------------//
MC_List* MC_ListList( void *head, ... ) {
    if ( head == NULL ) {
        return NULL;
    }
    MC_List *ret = MC_malloc( sizeof( *ret ) );
    if ( ret == NULL ) {
        return ret;
    }
    ret->head = head;
    ret->tail = NULL;
    MC_List *list = ret;
    va_list args;
    va_start( args, head );
    while ( ( head = va_arg( args, void * ) ) != NULL ) {
        list->tail = MC_malloc( sizeof( *list ) );
        if ( list->tail == NULL ) {
            MC_ListFree( &ret );
            return NULL;
        }
        list = list->tail;
        list->head = head;
    }
    list->tail = NULL;
    va_end( args );
    return ret;
}

//---------------------------------------------------------------------------//
MC_List* MC_ListPush( void *head, MC_List *tail ) {
    if ( head == NULL ) {
        return tail;
    }
    MC_List* list = malloc( sizeof ( *list ) );
    if ( list == NULL ) {
        return NULL;
    }
    list->head = head;
    list->tail = tail;
    return list;
}

//---------------------------------------------------------------------------//
MC_List* MC_ListPop( void **head_out, MC_List *list ) {
    assert( head_out );
    assert( list );
    *head_out = list->head;
    MC_List *tail = list->tail;
    free( list );
    return tail;
}

//---------------------------------------------------------------------------//
MC_List* MC_ListAppend( MC_List *listA, MC_List *listB ) {
    if ( listA == NULL ) {
        return listB;
    }
    if ( listB == NULL ) {
        return listA;
    }
    MC_List* tail = listA;
    while ( tail->tail ) {
        tail = tail->tail;
    }
    tail->tail = listB;
    return listA;
}

//---------------------------------------------------------------------------//
size_t MC_ListFree( MC_List **list_ref ) {
    assert( list_ref );
    MC_List *list = *list_ref;
    *list_ref = NULL;
    int count = 0;
    while ( list ) {
        MC_List *temp = list->tail;
        free( list );
        count++;
        list = temp;
    }
    return count;
}

//---------------------------------------------------------------------------//
size_t MC_ListLength( MC_List *list ) {
    int count = 0;
    while ( list ) {
        list = list->tail;
        count++;
    }
    return count;
}

//---------------------------------------------------------------------------//
MC_List* MC_ListCopy( MC_List *list ) {
    if ( list == NULL ) {
        return NULL;
    }
    MC_List *ret = MC_malloc( sizeof( *ret ) );
    if ( ret == NULL ) {
        return NULL;
    }
    ret->head = list->head;
    ret->tail = NULL;
    list = list->tail;
    MC_List *curr = ret;
    for ( ; list; list = list->tail ) {
        curr->tail = MC_malloc( sizeof( *list ) );
        if ( curr->tail == NULL ) {
            if ( ret != NULL ) {
                MC_ListFree( &ret );
            }
            return NULL;
        }
        curr = curr->tail;
        curr->head = list->head;
    }
    curr->tail = NULL;
    return ret;
}

//---------------------------------------------------------------------------//
MC_List* MC_ListReverse( MC_List *list ) {
    if ( list == NULL ) {
        return NULL;
    }
    MC_List* ret = NULL;
    for ( ; list; list = list->tail ) {
        MC_List* head = MC_malloc( sizeof( *head ) );
        if ( head == NULL ) {
            MC_ListFree( &ret );
            return NULL;
        }
        head->head = list->head;
        head->tail = ret;
        ret = head;
    }
    return ret;
}

//---------------------------------------------------------------------------//
void** MC_ListToArray( MC_List *list, void *end ) {
    size_t len = MC_ListLength( list );
    void** ret = MC_malloc( (len + 1) * sizeof( void * ) );
    if ( ret == NULL ) {
        return NULL;
    }
    size_t i = 0;
    for ( ; list; list = list->tail ) {
        ret[ i++ ] = list->head;
    }
    ret[ i ] = end;
    return ret;
}

//---------------------------------------------------------------------------//
MC_List* MC_ListMap( MC_List *list, void *map( void *element, void **acc ), void *acc ) {
    if ( list == NULL ) {
        return NULL;
    }
    MC_List *ret = MC_malloc( sizeof ( *ret ) );
    if ( ret == NULL ) {
        return NULL;
    }
    ret->head = map( list->head, &acc );
    if ( ret->head == NULL ) {
        return NULL;
    }
    ret->tail = NULL;
    list = list->tail;
    MC_List *last = ret;
    while ( list ) {
        MC_List* end = MC_malloc( sizeof ( *end ) );
        if ( end == NULL ) {
            MC_ListFree( &ret );
            return NULL;
        }
        end->head = map( list->head, &acc );
        if ( end->head == NULL ) {
            MC_ListFree( &ret );
            return NULL;
        }
        last->tail = end;
        last = end;
        list = list->tail;
    }
    last->tail = NULL;
    return ret;
}


//===========================================================================//
#ifdef DEBUG
#include "asrt.h"
//---------------------------------------------------------------------------//
typedef struct Njak {
    int x, y;
} Njak;

static Njak *pointers[10000];
//---------------------------------------------------------------------------//
static void BeforeTest() {
    for ( int i = 0; i < 10000; i++ ) {
        pointers[ i ] = malloc( sizeof( Njak ) );
        pointers[ i ]->x = i;
    }
}

//---------------------------------------------------------------------------//
static void AfterTest() {
    for ( int i = 0; i < 10000; i++ ) {
        free( pointers[i] );
    }
}

//---------------------------------------------------------------------------//
static int MC_ListTestAppend() {
    MC_List *listA = NULL;
    MC_List *listB = NULL;
    for ( int i = 0; i < 5000; i++ ) {
        listA = MC_ListPush( pointers[ i ], listA );
        listB = MC_ListPush( pointers[ 5000 + i ], listB );
    }
    listA = MC_ListAppend( listA, listB );
    size_t freed = MC_ListFree( &listA );
    ASRT_SIZE_T( 10000, freed );
    return 0;
}

//---------------------------------------------------------------------------//
static int MC_ListTestPushPop() {
    MC_List *list = NULL;
    for ( int i = 0; i < 10000; i++ ) {
        list = MC_ListPush( pointers[ i ], list );
    }

    for ( int i = 10000-1; i >= 0; i-- ) {
        Njak *temp;
        list = MC_ListPop( (void**)&temp, list );
        ASRT_EQ( pointers[ i ], temp );
    }

    ASRT_TRUE( list == NULL );
    return 0;;
}

//---------------------------------------------------------------------------//
static int MC_ListTestCopy() {
    MC_List *listA = NULL;
    for ( int i = 0; i < 10000; i++ ) {
        listA = MC_ListPush( pointers[ 10000 - i - 1 ], listA );
    }
    ASRT_SIZE_T( 10000, MC_ListLength( listA ) );

    MC_List *listB = MC_ListCopy( listA );
    MC_ListFree( &listA );

    for ( int i = 0; i < 10000; i++ ) {
        void *temp;
        listB = MC_ListPop( &temp, listB );
        ASRT_EQ( pointers[ i ], temp );
    }
    return 0;
}

//---------------------------------------------------------------------------//
// Pushes memory to the limit until malloc fails!
//---------------------------------------------------------------------------//
#if 0
static int MC_ListTestCopyOverload_DANGEROUS() {
    struct rlimit rl = {1024*1024*1024, 1024*1024*1024};
    struct rlimit rl2 = {1024*1024, 1024*1024};
    MC_List *listA = NULL;
    for ( int i = 0; i < 10000; i++ ) {
        listA = MC_ListPush( pointers[ i ], listA );
    }
    int listSize = sizeof( MC_List ) * 10000;
    for ( double i = 0; 1; i += listSize ) {
        printf( "%fG\n", i/(1024*1024*1024) );
        listA = MC_ListCopy(listA);
        if ( listA == NULL ) {
            break;
        }
    }
    return 0;
}
#endif

//---------------------------------------------------------------------------//
static int MC_ListReverse_test() {
    MC_List *listA = NULL;
    for ( int i = 0; i < 10000; i++ ) {
        listA = MC_ListPush( pointers[ i ], listA );
    }
    ASRT_SIZE_T( 10000, MC_ListLength( listA ) );

    MC_List *listB = MC_ListReverse( listA );
    ASRT_SIZE_T( 10000, MC_ListLength( listB ) );

    for ( int i = 0; i < 10000; i++ ) {
        void *temp;
        listB = MC_ListPop( &temp, listB );
        ASRT_EQ( pointers[ i ], temp );
    }

    MC_ListFree( &listA );
    return 0;
}

//---------------------------------------------------------------------------//
static int MC_ListToArray_test() {
    MC_List *listA = NULL;
    for ( int i = 0; i < 10000; i++ ) {
        listA = MC_ListPush( pointers[ i ], listA );
    }
    ASRT_SIZE_T( 10000, MC_ListLength( listA ) );

    int end = 0;
    void **arr = MC_ListToArray( MC_ListReverse(listA) , &end );
    for ( int i = 0; i < 10000; i++ ) {
        ASRT_EQ( pointers[ i ], arr[ i ] );
    }
    ASRT_EQ( &end, arr[ 10000 ] );

    MC_ListFree( &listA );
    return 0;
}

//---------------------------------------------------------------------------//
static void* square(void *element, void **acc) {
    Njak *ret = MC_malloc( sizeof( *ret ) );
    if ( ret == NULL ) {
        return NULL;
    }
    ret->x = ((Njak *)element)->x * ((Njak *)element)->x;
    return ret;
}

//---------------------------------------------------------------------------//
static int MC_ListMap_test() {
    MC_List *listA = NULL;
    for ( int i = 0; i < 10000; i++ ) {
        listA = MC_ListPush( pointers[ i ], listA );
    }
    ASRT_SIZE_T( 10000, MC_ListLength( listA ) );

    MC_List *listB = MC_ListMap( listA, square, NULL );
    ASRT_SIZE_T( 10000, MC_ListLength( listB ) );

    for ( int i = 10000-1; i >= 0; i-- ) {
        Njak *temp;
        listB = MC_ListPop( (void **)&temp, listB );
        ASRT_INT( i*i, temp->x );
    }

    MC_ListFree( &listA );
    return 0;
}

//---------------------------------------------------------------------------//
static int MC_ListList_test() {
    Njak a, b, c;
    MC_List *list = MC_ListList( &a, NULL );
    ASRT_SIZE_T( 1, MC_ListFree( &list ) );

    list = MC_ListList( &a, &b, &c, NULL );
    ASRT_SIZE_T( 3, MC_ListFree( &list ) );

    return 0;
}

//---------------------------------------------------------------------------//
void MC_ListSuite() {
    ASRT_BEFORE( BeforeTest );
    ASRT_AFTER( AfterTest );
    ASRT_TEST( MC_ListTestPushPop );
    ASRT_TEST( MC_ListTestAppend );
    ASRT_TEST( MC_ListTestCopy );
    // ASRT_TEST( MC_ListTestCopyOverload_DANGEROUS );
    ASRT_TEST( MC_ListReverse_test );
    ASRT_TEST( MC_ListToArray_test );
    ASRT_TEST( MC_ListMap_test );
    ASRT_TEST( MC_ListList_test );
}
#endif // DEBUG
