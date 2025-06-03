#pragma once

#define DEFINE_GRAPH(name, type)            \
                                            \
name##_node* name##_initializeGraph(char* newName)\
{                                           \
    name##_node* node = malloc(sizeof(name##_node));\
    *node->nodeName = *newName;               \
    node->nodes = malloc(sizeof(name##_node));\
    node->length = 1;                       \
    return node;                            \
}                                           \
                                            \
void name##_addNewNode(name##_node* node, char* newName)\
{                                           \
    node->nodes = realloc(node->nodes, (node->length + 1) * sizeof(name##_node *));\
    name##_node* newNode = name##_initializeGraph(newName);\
    newNode->length = 0;                    \
    newNode->nodes = NULL;                  \
    *node->nodes[node->length] = *newNode;  \
    node->length++;                         \
}                                           \
                                            \
void name##_removeNode(name##_node* node, int index)\
{                                           \
    if(index < 0 || index > node->length-1) \
        return;                             \
                                            \
    name##_node* nodeToBeRemoved = node->nodes[index];\
    for(int i = index; i < (node->length)-1; i++)   \
    {                                       \
        node->nodes[i] = node->nodes[i+1];  \
    }                                       \
    free(nodeToBeRemoved);                  \
}                                           \
                                            \
void name##_addExistingNode(name##_node* origin, name##_node* nodeToBeAdded)\
{                                           \
    origin->nodes = realloc(origin->nodes, (origin->length + 1) * sizeof(name##_node *));\
    *origin->nodes[origin->length] = *nodeToBeAdded;\
    origin->length++;                         \
}                                           \
                                            \
void name##_destroyGraph(name##_node* node) \
{                                           \
    if(node->length > 0)                    \
    {                                       \
        for(int i = 0; i < node->length; i++)\
        {                                   \
            if(node->nodes[i] != NULL)      \
                name##_destroyGraph(node->nodes[i]);\
        }                                   \
        free(node->nodes);                  \
    }                                       \
    free(node);                             \
}