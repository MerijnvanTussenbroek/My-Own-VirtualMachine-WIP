#include <stdlib.h>
#include <stdio.h>

#define DEFINE_LINKED_LIST(name, type)  \
typedef struct name##_node name##_node; \
typedef struct name##_node              \
{                                       \
    type data;                         \
    name##_node* next;                  \
};                                      \
                                        \
typedef struct                          \
{                                       \
    int success;                        \
    type value;                        \
} name##_LLresult;                      \
                                        \
                                        \
name##_node* name##_initializateLinkedList(type* newData);\
void name##_addNewNode(name##_node* list, type* newData);\
name##_LLresult name##_retrieveData(name##_node* list, int index);\
int name##_getSize(name##_node* list);\
void name##_removeItem(name##_node* list, int index);\
void name##_changeValue(name##_node* list, int index, type* newData);\
void name##_destroyLinkedList(name##_node* list);\

