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

    args_addToList(l, *newVar);
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

    command c = vm->program[vm->r.ip];
    values val = c.argument[0];

    if(val.type != STRING)
    {
        exit(-1);
    }

    char* varName = val.value.name;

    //we first look through global variables, then through the local ones
    // We also already assume the value has been loaded onto the stack

    args_list* globalList = vm->globalVariables;
    int length = globalList->size;
    for(int i = 0; i < length; i++)
    {
        args_result result = args_retrieveFromList(globalList, i);
        if(result.success == 1)
        {
            if(strcpy(result.value.name, varName))
            {
                Args* updatedValue = &result.value;

                updatedValue->value = v;
                args_changeInList(globalList, *updatedValue, i);
                return;
            }
        }
    }

    frame_stack_ss stackItem = frame_pop(vm->frames);

    if(stackItem.success != 1)
    {
        exit(-1);
    }

    args_list* localList = stackItem.value.args;
    length = localList->size;
    for(int i = 0; i < length; i++)
    {
        args_result result2 = args_retrieveFromList(localList, i);
        if(result2.success == 1)
        {
            if(strcpy(result2.value.name, varName))
            {
                Args* updatedValue2 = &result2.value;

                updatedValue2->value = v;
                args_changeInList(localList, *updatedValue2, i);
                frame_push(vm->frames, &stackItem.value);
                return;
            }
        }
    }
}

void LOAD_func(VM* vm)
{
        values_stack* stack = vm->loadedValues;
    values_stack_ss value = values_pop(stack);

    if(value.success != 1)
    {
        exit(-1);
    }

    unsigned long int v = value.value;

    command c = vm->program[vm->r.ip];
    values val = c.argument[0];

    if(val.type != STRING)
    {
        exit(-1);
    }

    char* varName = val.value.name;

    //we first look through global variables
    // then through local ones

    values_stack* stack = vm->loadedValues;

    args_list* globalList = vm->globalVariables;
    int length = globalList->size;
    for(int i = 0; i < length; i++)
    {
        args_result result = args_retrieveFromList(globalList, i);
        if(result.success == 1)
        {
            if(strcpy(result.value.name, varName))
            {
                values_push(stack, result.value.value);
                return;
            }
        }
    }

    frame_stack_ss stackItem = frame_pop(vm->frames);

    if(stackItem.success != 1)
    {
        exit(-1);
    }

    args_list* localList = stackItem.value.args;
    length = localList->size;
    for(int i = 0; i < length; i++)
    {
        args_result result2 = args_retrieveFromList(localList, i);
        if(result2.success == 1)
        {
            if(strcpy(result2.value.name, varName))
            {
                values_push(stack, result2.value.value);
                frame_push(vm->frames, &stackItem.value);
                return;
            }
        }
    }
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

