#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "parser.h"
#include "commands.h"
#include "frame.h"

DEFINE_STACK(frameStack, Frame);
DEFINE_STACK(valuesStack, unsigned long int);

typedef unsigned long int Reg;

typedef struct {
    Reg temporaryStorageRegister;
    Reg Var1;
    Reg Var2;
    Reg Result;
    Reg ip;
    Reg sp;
} Registers;



typedef struct {
    Registers r;
    frameStack_stack* frames;
    valuesStack_stack* loadedValues;
    Program program;
}VM;
