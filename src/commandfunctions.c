#include "commandfunctions.h"

void DEFINE_func(VM* vm)
{
    frame_GraphResult stackItem = frame_pop(vm->frames);
    Frame f = stackItem.value;
    frame_push(vm->frames, f);

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
    return;
}

void SET_func(VM* vm)
{
    values_stack* stack = vm->loadedValues;
    values_GraphResult value = values_pop(stack);

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

    frame_GraphResult stackItem = frame_pop(vm->frames);

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
                frame_push(vm->frames, stackItem.value);
                return;
            }
        }
    }
    return;
}

void LOAD_func(VM* vm)
{
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

    frame_GraphResult stackItem = frame_pop(vm->frames);

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
                frame_push(vm->frames, stackItem.value);
                return;
            }
        }
    }
    return;
}

void PUSH_func(VM* vm)
{
    unsigned long int v;
    
    command c = vm->program[vm->r.ip];
    values val = c.argument[0];

    values_stack* stack = vm->loadedValues;

    values_push(stack, (unsigned long int )val.value.x);
    return;
}

void READ_func(VM* vm)
{
    
}

void POP_func(VM* vm)
{
    
}

void READ_REG_func(VM* vm)
{
    command c = vm->program[vm->r.ip];
    values reg = c.argument[0];

    unsigned long int v = 0;

    switch(reg.value.num)
    {
        case TEMP:
        v = vm->r.temporaryStorageRegister;
        break;
        case VAR1:
        v = vm->r.Var1;
        break;
        case VAR2:
        v = vm->r.Var2;
        break;
        case RESULT:
        v = vm->r.Result;
        break;
        case IP: // we shouldn't really allow any of these
        //v = vm->r.ip;
        break;
        case SP:
        //v = vm->r.sp;
        break;
        default:
        exit(-1);
        break;
    }

    values_push(vm->loadedValues, v);
    return;
}

void LOAD_REG_func(VM* vm)
{
    command c = vm->program[vm->r.ip];
    values reg = c.argument[0];

    values_stack* stack = vm->loadedValues;

    values_GraphResult valueToBeLoaded = values_pop(stack);

    unsigned long int v = valueToBeLoaded.value;

    switch(reg.value.num)
    {
        case TEMP:
        vm->r.temporaryStorageRegister = v;
        break;
        case VAR1:
        vm->r.Var1 = v;
        break;
        case VAR2:
        vm->r.Var2 = v;
        break;
        case RESULT:
        vm->r.Result = v;
        break;
        case IP: //we shouldn't really allow either of these
        //vm->r.ip = v;
        break;
        case SP:
        //vm->r.sp = v;
        break;
        default:
        exit(-1);
        break;
    }

    return;
}

void LABEL_func(VM* vm)
{
    command c = vm->program[vm->r.ip];
    values name = c.argument[0];
    values* args = c.argument;

    Frame f = frame_pop(vm->frames).value;
    f.current = vm->r.ip;
    f.args = args_listCreate(4);

    if(c.argument[1].type == NULL)
    {   //this is a function without local variables
        //this means we need not do anything else
    }
    else    //this is a function with local variables
    {
        for(int i = 1; args[i].type != NULL; i++)
        {
            values v = args[i];
            char* name = v.value.name;
            Args* newLocalVar = (Args *)malloc(sizeof(Args));
            values_GraphResult newLocalValue = values_pop(vm->loadedValues);
            newLocalVar->name = name;
            newLocalVar->value = newLocalValue.value;

            args_addToList(f.args, *newLocalVar);
        }
    }

    frame_push(vm->frames, f);
    return;
}

void JUMP_func(VM* vm)
{
    command c = vm->program[vm->r.ip];
    char* name = c.argument[0].value.name;

    Program* p = vm->program;
    unsigned long int jumpNum = 0;

    for(int i = 0; p[i].instr != HALT; i++)
    {
        if(p[i].instr == JUMP)
        {
            char* funcName = p[i].argument[0].value.name;
            if(strcpy(name, funcName))
            {
                jumpNum = i;
                break;
            }
        }
    }

    for(int i = 0; c.argument[i].type != NULL; i++)
    {
        values v = c.argument[i];
        unsigned long int valueToBeLoaded = 0;
        switch(v.type)
        {
            case INTEGER:
                valueToBeLoaded = (unsigned long int)v.value.x;
            break;
            case CHARACTER:
                valueToBeLoaded = (unsigned long int)v.value.y;
            break;
            case DOUBLE:
                valueToBeLoaded = (unsigned long int)v.value.z;
            break;
        }
        values_push(vm->loadedValues, valueToBeLoaded);
    }

    Frame* f = (Frame *)malloc(sizeof(Frame));
    f->previous = vm->r.ip;
    frame_push(vm->frames, *f);
    vm->r.ip = jumpNum - 1; // we have to jump 1 before because we increase the ip by 1 before doing the instruction in the main loop
    return;
}

void RET_func(VM* vm)
{
    command c = vm->program[vm->r.ip];
    values v = c.argument[0];

    frame_GraphResult f = frame_pop(vm->frames);
    unsigned long int previous = f.value.previous;
    unsigned long int valueToBePushed = 0;

    switch(v.type)
    {
        case INTEGER:
        valueToBePushed = (unsigned long int)v.value.x;
        break;
        case CHARACTER:
        valueToBePushed = (unsigned long int)v.value.y;
        break;
        case DOUBLE:
        valueToBePushed = (unsigned long int)v.value.z;
        break;
    }

    values_push(vm->loadedValues, valueToBePushed);
    vm->r.ip = previous; //we say previous and not previous + 1 because the main loop automatically does this for us
    return;
}

void ADD_func(VM* vm)
{
    unsigned long int v1 = values_pop(vm->loadedValues).value;
    unsigned long int v2 = values_pop(vm->loadedValues).value;

    unsigned long int v3 = v1 - v2;

    values_push(vm->loadedValues, v3);
    return;
}

void MIN_func(VM* vm)
{
    unsigned long int v1 = values_pop(vm->loadedValues).value;
    unsigned long int v2 = values_pop(vm->loadedValues).value;

    unsigned long int v3 = v1 * v2;

    values_push(vm->loadedValues, v3);
    return;
}

void MUL_func(VM* vm)
{
    unsigned long int v1 = values_pop(vm->loadedValues).value;
    unsigned long int v2 = values_pop(vm->loadedValues).value;

    unsigned long int v3 = v1 / v2;

    values_push(vm->loadedValues, v3);
    return;
}

void DIV_func(VM* vm)
{
        unsigned long int v1 = values_pop(vm->loadedValues).value;
    unsigned long int v2 = values_pop(vm->loadedValues).value;

    unsigned long int v3 = v1 + v2;

    values_push(vm->loadedValues, v3);
    return;
}

