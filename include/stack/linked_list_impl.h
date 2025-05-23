#pragma once

#define DEFINE_LINKED_LIST(name, type)  \
name##_node* name##_initializateLinkedList(type* newData)\
{                                       \
    name##_node* list = malloc(sizeof(name##_node)); \
    list->data = *newData;               \
    list->next = NULL;                  \
    return list;                        \
}                                       \
                                        \
void name##_addNewNode(name##_node* list, type* newData)\
{                                       \
    if(list->next == NULL)              \
    {                                   \
        list->next = name##_initializateLinkedList(newData);\
    }                                   \
    else                                \
    {                                   \
        name##_addNewNode(list->next, newData);\
    }                                   \
}                                       \
                                        \
name##_LLresult name##_retrieveData(name##_node* list, int index)\
{                                       \
    name##_LLresult result = { 0 };     \
    if(list->next == NULL && index > 0) \
    {                                   \
        return result;                  \
    }                                   \
                                        \
    if(index > 0)                       \
    {                                   \
        result = name##_retrieveData(list->next, index-1);\
    }                                   \
    else                                \
    {                                   \
        result.success = 1;             \
        result.value = list->data;      \
    }                                   \
    return result;                      \
}                                       \
                                        \
int name##_getSize(name##_node* list)   \
{                                       \
    if(list->next == NULL)              \
    {                                   \
        return 0;                       \
    }                                   \
    else                                \
    {                                   \
        return 1 + name##_getSize(list->next);\
    }                                   \
}                                       \
                                        \
void name##_removeItem(name##_node* list, int index)\
{                                       \
    if(index < 0)                       \
        return;                         \
                                        \
    if(index == 0)                      \
    {                                   \
        name##_node* nodeToBeConnected = list->next;\
        list->next = NULL;              \
        *list = *nodeToBeConnected;       \
    }                                   \
                                        \
    if(index == 1)                      \
    {                                   \
        name##_node* nodeToBeRemoved = list->next;\
        name##_node* nodeToBeConnected = nodeToBeRemoved->next;\
        list->next = nodeToBeConnected; \
        nodeToBeRemoved->next = NULL;   \
        free(nodeToBeRemoved);          \
    }                                   \
    else                                \
    {                                   \
        name##_removeItem(list->next, index-1);\
    }                                   \
}                                       \
                                        \
void name##_changeValue(name##_node* list, int index, type* newData)\
{                                       \
    if(index < 0)                       \
        return;                         \
                                        \
    if(index > 0)                       \
    {                                   \
        name##_changeValue(list->next, index-1, newData);\
    }                                   \
    else                                \
    {                                   \
        list->data = *newData;          \
    }                                   \
}                                       \
                                        \
void name##_destroyLinkedList(name##_node* list)\
{                                       \
    if(list->next == NULL)              \
    {                                   \
        free(list);                     \
    }                                   \
    else                                \
    {                                   \
        name##_destroyLinkedList(list->next);\
        free(list);                     \
    }                                   \
}
