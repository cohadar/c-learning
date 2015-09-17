#include "MC_stack.h"
#include <stdlib.h>
#include <assert.h>

#define MC_STACK_MAGIC 0x1D39C63A

//---------------------------------------------------------------------------//
struct MC_Stack {
    int magic;
    int size;
    struct Node {
        void *value;
        struct Node *prev;
    } *top;
};

//---------------------------------------------------------------------------//
MC_Stack * MC_StackNew( void ) {
    MC_Stack *ret = malloc( sizeof( MC_Stack ) );
    ret->magic = MC_STACK_MAGIC;
    ret->size = 0;
    ret->top = NULL;
    return ret;
}

//---------------------------------------------------------------------------//
int MC_StackIsEmpty( MC_Stack *stack ) {
    assert( stack );
    assert( stack->magic == MC_STACK_MAGIC );
    return stack->size == 0;
}

//---------------------------------------------------------------------------//
void MC_StackPush( MC_Stack *stack, void *value ) {
    assert( stack );
    assert( stack->magic == MC_STACK_MAGIC );
    stack->size++;
    struct Node *newTop = malloc( sizeof( struct Node ) );
    newTop->prev = stack->top;
    newTop->value = value;
    stack->top = newTop;
}

//---------------------------------------------------------------------------//
void * MC_StackPop( MC_Stack *stack ) {
    assert( stack );
    assert( stack->magic == MC_STACK_MAGIC );
    assert( stack->size > 0 );
    stack->size--;
    void * ret = stack->top->value;
    struct Node *top = stack->top;
    stack->top = top->prev;
    free( top );
    return ret;
}

//---------------------------------------------------------------------------//
void MC_StackFree( MC_Stack **stack ) {
    assert( *stack );
    assert( ( *stack )->magic == MC_STACK_MAGIC );
    while ( !MC_StackIsEmpty( *stack ) ) {
        MC_StackPop( *stack );
    }
    free( *stack );
    *stack = 0;
}
#undef MC_STACK_MAGIC

#ifdef DEBUG
#include "asrt.h"
//---------------------------------------------------------------------------//
static int TestPushPop() {
    int x = 111;
    int y = 222;
    MC_Stack *stack = MC_StackNew();
    MC_StackPush( stack, &x );
    MC_StackPush( stack, &y );
    int *y2 = MC_StackPop( stack );
    ASRT_INT( y, *y2 );
    int *x2 = MC_StackPop( stack );
    ASRT_INT( x, *x2 );
    MC_StackFree( &stack );
    return 0;
}

//---------------------------------------------------------------------------//
static int TestNewAndFree() {
    MC_Stack *stack = MC_StackNew();
    ASRT_TRUE( stack );

    MC_StackFree( &stack );
    ASRT_FALSE( stack );

    return 0;
}

//---------------------------------------------------------------------------//
static int TestIsEmpty() {
    int a, b;

    MC_Stack *stack = MC_StackNew();
    ASRT_TRUEm( "empty", MC_StackIsEmpty( stack ) );

    MC_StackPush( stack, &a );
    ASRT_FALSEm( "not-empty 1", MC_StackIsEmpty( stack ) );

    MC_StackPush( stack, &b );
    ASRT_FALSEm( "not-empty 2", MC_StackIsEmpty( stack ) );

    MC_StackPop( stack );
    ASRT_FALSEm( "not-empty 1 again", MC_StackIsEmpty( stack ) );

    MC_StackPop( stack );
    ASRT_TRUEm( "empty", MC_StackIsEmpty( stack ) );

    MC_StackFree( &stack );
    return 0;
}

//---------------------------------------------------------------------------//
void MC_StackSuite() {
    ASRT_TEST( TestNewAndFree );
    ASRT_TEST( TestIsEmpty );
    ASRT_TEST( TestPushPop );
}
#endif // DEBUG

