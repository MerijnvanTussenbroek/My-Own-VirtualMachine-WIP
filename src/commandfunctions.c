#include "commandfunctions.h"

void DEFINE_func(VM* vm)
{
    Frame f = frame_retrieveData(vm->frames->next, 0).value;

    command c = vm->program[vm->r.ip];
    values v = c.argument[0];

    if(v.type != STRING)
    {
        exit(-1);
    }

    char* newName = v.value.name;

    args_list* l;

    if(f.current == 0)
    { // it is a global variable
        l = vm->globalVariables;
    }
    else
    { // it is a local variable
        l = f.args;
    }

    Args* newVar = (Args *)malloc(sizeof(Args));

    newVar->name = malloc(sizeof(newName));

    strcpy(newVar->name, newName);

    //args_addToList(l, *newVar);
}

void SET_func(VM* vm)
{
    values_stack* stack = vm->loadedValues;
    values_stack_ss value = values_pop(stack);

    if(value.success != 1)
    {
        exit(-1);
    }

    unsigned long int v = value.value;
}

void LOAD_func(VM* vm)
{
    
}

void PUSH_func(VM* vm)
{
    
}

void READ_func(VM* vm)
{
    
}

void POP_func(VM* vm)
{
    
}

void READ_REG_func(VM* vm)
{
    
}

void LOAD_REG_func(VM* vm)
{
    
}

void LABEL_func(VM* vm)
{
    
}

void JUMP_func(VM* vm)
{
    
}

void RET_func(VM* vm)
{
    
}

void ADD_func(VM* vm)
{
    
}

void MIN_func(VM* vm)
{
    
}

void MUL_func(VM* vm)
{
    
}

void DIV_func(VM* vm)
{
    
}

