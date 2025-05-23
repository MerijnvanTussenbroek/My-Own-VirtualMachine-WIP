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
name##_stack* name##_initializeStack(type* newData);\
void name##_push(name##_stack* stack, type* newData);\
name##_stack_ss name##_pop(name##_stack* stack);        \
void name##_destroyStack(name##_stack* stack);\
