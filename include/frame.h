#pragma once

enum variableType
{
    INTEGER = 0,
    CHARACTER,
    DOUBLE,
    NAME
};
typedef unsigned char ArgType;

typedef struct
{
    ArgType type;
    unsigned char* name;
    union{
        int x;
        char y;
        double z;
    } value;
} Args;


typedef struct
{
    int current; //the index of the label of the current function we're in
    int previous; //the index of the label of the instruction we were previously at
    Args* args;
} Frame;