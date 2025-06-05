#pragma once

#include "linked_list_impl.h"

#define DEFINE_STACK(name, type)            \
DEFINE_LINKED_LIST(name,type);              \
                                            \
name##_stack* name##_initializeStack(type newData)\
{                                           \
    name##_stack* stack = malloc(sizeof(name##_stack));\
    stack->LL = name##_initializeLinkedList(newData);\
    stack->length++;                        \
}                                           \
                                            \
void name##_push(name##_stack* stack, type newData)\
{                                           \
    stack->length++;                        \
    name##_insertNewNodeToLL(&stack->LL, newData, 0);\
}                                           \
                                            \
name##_GraphResult name##_pop(name##_stack* stack)\
{                                           \
    if(stack->length > 0)                   \
    {                                       \
        stack->length--;                    \
        name##_GraphResult result = name##_retrieveDataFromLL(stack->LL, 0);\
        name##_removeItemFromLL(&stack->LL, 0);\
        return result;                      \
    }                                       \
}                                           \
                                            \
void name##_destroyStack(name##_stack* stack)\
{                                           \
    name##_destroyLinkedList(stack->LL);    \
    free(stack);                            \
}