#pragma once

typedef char* Label;

enum _argType
{
    INTEGER = 0,
    CHARACTER = 1,
    DOUBLE = 2
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
    Label current;
    Label previous;
    int argAmount;
    Args* args;
} Frame;