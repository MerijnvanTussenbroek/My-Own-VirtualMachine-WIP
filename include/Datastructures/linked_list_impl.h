#pragma onced

#include "graph_impl.h"

#define DEFINE_LINKED_LIST(name, type)  \
DEFINE_GRAPH(name, type);               \
                                        \
name##_node* name##_initializeLinkedList(type newData)\
{                                       \
    name##_node* list = malloc(sizeof(name##_node));\
    list->nodes = malloc(sizeof(name##_node *) * 1);\
    list->nodes[0] = NULL;              \
    list->data = newData;               \
    list->length = 1;                   \
    return list;                        \
}                                       \
                                        \
void name##_addNewNodeToLL(name##_node* list, type newData)\
{                                       \
    name##_node* current = list;        \
    while(current->nodes[0] != NULL)    \
    {                                   \
        current = current->nodes[0];    \
    }                                   \
    name##_node* newNode = name##_initializeLinkedList(newData);\
    current->nodes[0] = newNode;        \
}                                       \
                                        \
void name##_insertNewNodeToLL(name##_node** list, type newData, int index)\
{                                       \
    name##_node* current = *list;       \
                                        \
    if(index == 0)                      \
    {                                   \
        name##_node* newNode = name##_initializeLinkedList(newData);\
        newNode->nodes[0] = *list;      \
        *list = newNode;                \
        return;                         \
    }                                   \
                                        \
    while(index > 1)                    \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            printf("trying to insert where it doesn't exist");\
            return;                     \
        }                               \
                                        \
        current = current->nodes[0];    \
        index--;                        \
    }                                   \
                                        \
    name##_node* nodeToBeAdded = name##_initializeLinkedList(newData);\
    name##_node* inbetween = current->nodes[0];\
    current->nodes[0] = nodeToBeAdded;  \
    nodeToBeAdded->nodes[0] = inbetween;\
}                                       \
                                        \
name##_GraphResult name##_retrieveDataFromLL(name##_node* list, int index)\
{                                       \
    name##_GraphResult result = { 0 };  \
    name##_node* current = list;        \
    while(index > 0)                    \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            printf("trying to retreive data that doesn't exist");\
            return result;              \
        }                               \
                                        \
        current = current->nodes[0];    \
        index--;                        \
    }                                   \
                                        \
    result.success = 1;                 \
    result.value = current->data;       \
    return result;                      \
}                                       \
                                        \
int name##_getSizeFromLL(name##_node* list)\
{                                       \
    int length = 1;                     \
    name##_node* current = list;        \
    while(current->nodes[0] != NULL)    \
    {                                   \
        current = current->nodes[0];    \
        length++;                       \
    }                                   \
    return length;                      \
}                                       \
                                        \
void name##_removeItemFromLL(name##_node** list, int index)\
{                                       \
    name##_node* current = *list;       \
                                        \
    if(index < 0)                       \
        return;                         \
                                        \
    if(index == 0)                      \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            printf("\nremoveitemfromLL current nodes0 == NULL");\
            return;                     \
        }                               \
                                        \
        name##_node* nodeToBeCon = current->nodes[0];\
        current->nodes[0] = NULL;       \
        name##_destroyLinkedList(current);\
        *list = nodeToBeCon;            \
        return;                         \
    }                                   \
                                        \
    while(index > 1)                    \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            printf("trying to remove that doesn't exist");\
            return;                     \   
        }                               \
                                        \
        current = current->nodes[0];    \
        index--;                        \
    }                                   \
                                        \
    name##_node* nodeToBeRemoved = current->nodes[0];\
    name##_node* nodeToBeConnected = nodeToBeRemoved->nodes[0];\
    nodeToBeRemoved->nodes[0] = NULL;   \
    name##_destroyGraph(nodeToBeRemoved);\
    current->nodes[0] = nodeToBeConnected;\
}                                       \
                                        \
void name##_changeValueInLL(name##_node* list, int index, type newData)\
{                                       \
    name##_node* current = list;        \
    while(index > 0)                    \
    {                                   \
        if(current->nodes[0] == NULL)   \
        {                               \
            printf("trying to change thzat doesn't exist");\
            return;                     \        
        }                               \
                                        \
        current = current->nodes[0];    \
        index--;                        \
    }                                   \
                                        \
    current->data = newData;            \
}                                       \
                                        \
void name##_destroyLinkedList(name##_node* list)\
{                                       \
    name##_destroyGraph(list);          \
}                                       