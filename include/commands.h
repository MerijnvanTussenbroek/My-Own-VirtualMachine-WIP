#pragma once

enum e_opcode
{
    DEFINE,
    SET,
    LOAD,

    PUSH,
    POP,

    LABEL,
    RET,

    ADD,
    MIN,
    MUL,
    DIV,

    HALT
};
typedef unsigned char Opcode;

typedef Opcode* Program;

/*
DEFINE (varname)
SET (varname) //it pops the value off the stack and sets this var to that
LOAD (varname) // pushes the variable into the stack

PUSH (value)
POP

// load value 1 into Var1 and 2 into Var2 and then computes the result and puts it into the Result register
ADD (value) (value) 
SUB (value) (value)
MUL (value) (value)
DIV (value) (value)

LABEL (name) (variable names)
RET (value) //puts a variable in the temporary register and pushes it on the stack when back

HALT
*/