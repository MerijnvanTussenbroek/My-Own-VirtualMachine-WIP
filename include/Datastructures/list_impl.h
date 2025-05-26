#pragma once

#define DEFINE_LIST(type,name)\
/* datastructure initialization */      \
name##_list* name##_listCreate(int newSize)                                         \
{                                                                                   \
    name##_list* list;                                                              \
    list = malloc(sizeof(name##_list));                                             \
    list->data = malloc(sizeof(type) * (newSize + 4));                              \
    list->size = 0;                                                           \
    list->capacity = (newSize + 4);                                                 \
    return list;                        \
}                                       \
                                        \
/* datastructure functions */           \
void name##_addToList(name##_list *l, type value)\
{                                       \
    if(l->size == l->capacity)          \
    {                                   \
        type* temp = realloc(l->data, sizeof(type) * (l->capacity + 2));\
        l->capacity += 2;               \
        l->size += 2;                   \
        if(!temp) exit(-1);             \
        l->data = temp;                 \
    }                                   \
    l->data[l->size++] = value;         \
}                                       \
                                        \
void name##_changeInList(name##_list *l, type value, int index)\
{                                       \
    if(l->size < index  || index < 0){  \
        printf("Tried changeing an item that doesn't exist.");\
        return;                         \
    }                                   \
    l->data[index] = value;             \
}                                       \
                                        \
void name##_removeFromList(name##_list *l, int index)\
{                                       \
    if(l->size < index  || index < 0){  \
        printf("Tried deleting an item that doesn't exist.");\
        return;                         \
    }                                   \
    for(int i = index; i < (l->size - 1); i++)\
    {                                   \
        l->data[i] = l->data[i+1];\
    }                                   \
    l->size--;                          \
}                                       \
                                        \
void name##_insertIntoListAt(name##_list *l, int index, type value)\
{                                       \
    if(l->size < index  || index < 0){  \
        printf("Tried inserting an item at an index that deosn't exit.");\
        return;                         \
    }                                   \
                                        \
    for(int i = index; i < l->size; i++){\
        l->data[i+1] = l->data[i];      \
    }                                   \
    l->size++;                          \
    l->data[index] = value;             \
}                                       \
                                        \
void name##_deleteList(name##_list *l)  \
{                                       \
    if(!l) exit(-1);                    \
    if(!l->data) exit(-1);              \
    free(l->data);                      \
    free(l);                            \
}                                       \
                                        \
name##_result name##_retrieveFromList(name##_list *l, int index)\
{                                       \
    name##_result result =  { 0 };      \
    if(l->size < index || index < 0)    \
    {                                   \
        printf("Tried retrieving an item that doesn't exist. %d \n", index);\
        return result;                  \
    }                                   \
    result.success = 1;                 \
    result.value = l->data[index];      \
    return result;                      \
}                                       \
/* This only works if the type can be compared */\
/* To do this, youll have to define your own comparison function that must adhere to the following requirements */\
/* The output is an integer, if the first input is less than the second, return 1, otherwise return 0*/\
/*so for example, with 5 < 6 you return 1, but for 8 < 2 you return 0 or anything BUT 1*/\
void name##_sortList(name##_list *l, int (*cmp)(const type *, const type *))    \
{                                       \
    for(int i = 0; i < l->size; i++)    \
    {                                   \
        for(int j = i; j < l->size; j++)\
        {                               \
            if(cmp(&l->data[i], &l->data[j]) != 1)\
            {                           \
                type temp = l->data[i]; \
                l->data[i] = l->data[j];\
                l->data[j] = temp;      \
            }                           \
        }                               \
    }                                   \
}                                        
// There are defitiely better sorting algorithms,
// but I haven't gotten there in my university
// studies yet, so for now it's this