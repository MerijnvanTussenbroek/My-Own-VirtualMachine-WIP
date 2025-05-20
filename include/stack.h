#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFINE_STACK(name, type)            \
DEFINE_LINKED_LIST(name,type);              \
typedef struct name##_stack name##_stack;   \
typedef struct name##_stack                 \
{                                           \
    name##_node* next;                      \
};                                          \
                                            \
typedef struct                                \
{                                           \
    int success;                            \
    type value;                             \
}name##_stack_ss;                                          \
                                            \
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
}