#pragma once

#include "linked_list_impl.h"

#define DEFINE_STACK(name, type)            \
DEFINE_LINKED_LIST(name,type);              \
name##_stack* name##_initializeStack(type* newData)\
{                                           \
    name##_stack* newStack;                 \
    newStack = malloc(sizeof(name##_stack));\
    newStack->next = name##_initializateLinkedList(newData);\
    return newStack;                        \
}                                           \
                                            \
void name##_push(name##_stack* stack, type* newData) \
{                                           \
    name##_node* node = name##_initializateLinkedList(newData);\
    node->next = stack->next;               \
    stack->next = node;                     \
    return;                                 \
}                                           \
                                            \
name##_stack_ss name##_pop(name##_stack* stack)        \
{                                           \
    name##_stack_ss result = { 0 };         \
    name##_node* node = stack->next;        \
    name##_node* nextNode = node->next;     \
    if(node == NULL)                        \
    {                                       \
        return result;                      \
    }                                       \
    stack->next = nextNode;                 \
    result.success = 1;                     \
    result.value = node->data;              \
    free(node);                             \
    return result;                           \
}\
                                            \
void name##_destroyStack(name##_stack* stack)\
{                                           \
    name##_destroyLinkedList(stack->next);  \
    free(stack);                            \
}   