#include <stdlib.h>
#include <stdio.h>

#define DEFINE_GRAPH(name, type)        \
typedef struct name##_node name##_node; \
typedef struct name##_node              \
{                                       \
    char* nodeName;                         \
    type data;                          \
    name##_node** nodes;                \
    int length;                         \
};                                      \
                                        \
typedef struct                          \
{                                       \
    int success;                        \
    type value;                         \
} name##_GraphResult;                   \
                                        \
name##_node* name##_initializeGraph(char* newName);\
void name##_addNewNode(name##_node* node, char* newName);\
void name##_removeNode(name##_node* node, int index);\
void name##_addExistingNode(name##_node* origin, name##_node* nodeToBeAdded);\
void name##_destroyGraph(name##_node* node);

