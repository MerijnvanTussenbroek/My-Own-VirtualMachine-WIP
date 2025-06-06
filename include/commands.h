#pragma once

#include "frame.h"

enum e_opcode
{
    DEFINE,
    SET,
    LOAD,

    PUSH,
    POP,

    LABEL,
    JUMP,
    RET,

    ADD,
    MIN,
    MUL,
    DIV,

    BEGIN,
    NOTHING,
    HALT
};
typedef unsigned char Opcode;

typedef enum {
    TEMP = 1,
    VAR1,
    VAR2,
    RESULT,
    IP,
    SP
} RegLoc;
typedef unsigned char RegisterNumber;

typedef struct 
{
    ArgType type;
    union 
    {
        int x;
        char y;
        double z;
        char* name;
        RegisterNumber num;
    } value;
} values;


typedef struct 
{
    Opcode instr;
    values* argument;
} command;

typedef command Program;

/*
DEFINE (varname)
SET (varname) //it pops the value off the stack and sets this var to that
LOAD (varname) // pushes the variable into the stack

PUSH (value)
READ // reads the value at the top of the stack
POP

// loads the top 2 values of the stack into reg Var1 and Var2, then puts the computed value into Result Reg
// which gets pushed back onto the stack
ADD 
SUB 
MUL 
DIV

READ_REG (value)
LOAD_REG (value) (value) // first value is the register, we load off of the stack


LABEL (name)
JUMP (name) // jumps to the label with that name, any variables needed will be pushed onto the stack, and then popped into the variables defined at the label
JUMP (value) // if the last item on the stack is a 1, it jumps back the value given
RET // we return back to where we jumped from, if a value needs to be pushed onto the stack it will have already happened and the program will continue with that assumption

BEGIN
NOTHING // the VM does nothing
HALT
*/