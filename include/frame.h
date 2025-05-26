#pragma once

#include "list.h"

enum variableType
{
    INTEGER = 0,
    CHARACTER,
    DOUBLE,
    STRING,
    REGISTER
};
typedef unsigned char ArgType;

typedef struct
{
    ArgType type;
    unsigned char* name;
    unsigned long int value;
} Args;

DEFINE_LIST(Args, args);


typedef struct
{
    int current; //the index of the label of the current function we're in
    int previous; //the index of the instruction we were previously at
    args_list* args;
} Frame;