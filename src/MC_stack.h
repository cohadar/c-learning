#ifndef __c_learning__stack__
#define __c_learning__stack__

typedef struct MC_Stack MC_Stack;

extern MC_Stack *  MC_StackNew    ( void );
extern int         MC_StackIsEmpty( MC_Stack *stack );
extern void        MC_StackPush   ( MC_Stack *stack, void *value );
extern void *      MC_StackPop    ( MC_Stack *stack );
extern void        MC_StackFree   ( MC_Stack **stack );

#ifdef DEBUG
extern void MC_StackSuite();
#endif

#endif /* defined(__c_learning__stack__) */
