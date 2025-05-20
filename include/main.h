#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef unsigned int Args;
typedef char* Label;

typedef struct
{
    Label l;
    Args args[];
} Frame;

DEFINE_STACK(frameStack, Frame);

typedef unsigned long int Reg;

typedef struct {
    Reg Var1;
    Reg Var2;
    Reg Result;
    Reg ip;
} Registers;



typedef struct {
    Registers r;
}VM;
