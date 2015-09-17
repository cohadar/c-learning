//
//  MC_List.h
//  c-learning
//
//  Created by Damir Cohadarevic on 4/13/15.
//  Copyright (c) 2015 Damir Cohadarevic. All rights reserved.
//

#ifndef __c_learning__MC_List__
#define __c_learning__MC_List__

#include <stdlib.h>

typedef struct MC_List MC_List;

struct MC_List {
    void* head;
    MC_List* tail;
};

extern MC_List* MC_ListAppend( MC_List *listA, MC_List *listB );
extern MC_List* MC_ListCopy( MC_List *list );
extern MC_List* MC_ListList( void *head, ... );
extern MC_List* MC_ListPop( void **head_out, MC_List *list );
extern MC_List* MC_ListPush( void *head, MC_List *tail );
extern MC_List* MC_ListReverse( MC_List *list );
extern size_t   MC_ListLength( MC_List *list );
extern size_t   MC_ListFree( MC_List **list_ref );
extern MC_List* MC_ListMap( MC_List *list, void *map( void *element, void **acc ), void *acc );
extern void**   MC_ListToArray( MC_List *list, void *end );

#ifdef DEBUG
#include "asrt.h"
extern void MC_ListSuite();
#endif

#endif /* defined(__c_learning__MC_List__) */
