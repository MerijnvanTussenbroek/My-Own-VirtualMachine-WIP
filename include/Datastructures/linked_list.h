#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

/*
Here, we make the assumption that nodes[0] is the next node in the list
*/

#define DEFINE_LINKED_LIST(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
name##_node* name##_initializeLinkedList(type newData);\
void name##_addNewNodeToLL(name##_node* list, type newData);\
void name##_insertNewNodeToLL(name##_node** list, type newData, int index);\
name##_GraphResult name##_retrieveDataFromLL(name##_node* list, int index);\
int name##_getSizeFromLL(name##_node* list);\
void name##_removeItemFromLL(name##_node** list, int index);\
void name##_changeValueinLL(name##_node* list, int index, type newData);\
void name##_destroyLinkedList(name##_node* list);

