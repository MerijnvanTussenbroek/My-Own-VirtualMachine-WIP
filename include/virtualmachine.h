#pragma once

#include "stack.h"
#include "commands.h"

DEFINE_STACK(frame, Frame);
DEFINE_STACK(values, unsigned long int);

typedef unsigned long int Reg;

typedef struct {
    Reg temporaryStorageRegister; // 1
    Reg Var1; // 2
    Reg Var2; // 3
    Reg Result; // 4
    Reg ip; // 5
    Reg sp; // 6
} Registers;

typedef struct {
    Registers r;
    frame_stack* frames;
    values_stack* loadedValues;
    Args* globalVariables;
    Program* program;
}VM;