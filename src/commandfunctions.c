#include "commandfunctions.h"

void DEFINE_func(VM* vm)
{
    command currentCommand = vm->program[(vm->r.ip)];
    values* arg = currentCommand.argument;
    if(arg->type != STRING)
    {
        printf("\nSomething went wrong, the DEFINE func got something other than a string\n");
        exit(-1);
    }

    char* name = arg->value.name;

    Args* newVar = (Args *)malloc(sizeof(Args));

    newVar->name = name;

    frame_stack* stack = vm->frames;

    args_list* list;

    if(frame_getSizeFromLL(stack->LL) == 1)
    {
        //global var
        list = vm->globalVariables;
    }
    else
    {
        //local var
        frame_GraphResult f = frame_pop(vm->frames);
        if(f.success != 1)
        {
            printf("\n tried popping a frame off in DEFINE, failed\n");
            exit(-1);
        }
        Frame frame = f.value;
        list = frame.args;

        frame_push(vm->frames, frame);
    }

    args_addToList(list, *newVar);

    free(newVar);
}

void SET_func(VM* vm)
{
    command currentCommand = vm->program[(vm->r.ip)];
    values* arg = currentCommand.argument;
    if(arg->type != STRING)
    {
        printf("\nSomething went wrong, the SET func got something other than a string\n");
        exit(-1);
    }

    char* name = arg->value.name;

    values_stack* stack = vm->loadedValues;

    values_GraphResult result = values_pop(stack);
    if(result.success != 1)
    {
        printf("\nSomething went wrong in SET popping off the values stack\n");
        exit(-1);
    }

    unsigned long int value = result.value;

    //we first check all local variables, then global ones

    Args* variable = NULL;

    frame_GraphResult f = frame_pop(vm->frames);
    if(f.success != 1)
    {
        printf("\n tried popping a frame off in DEFINE, failed\n");
        exit(-1);
    }
    Frame frame = f.value;
    args_list* list = frame.args;

    frame_push(vm->frames, frame);

    for(int i = 0; i < list->size; i++)
    {
        if(strncmp(name, list->data[i].name, strlen(name)) == 0)
        {
            variable = &list->data[i];
        }
    }

    if(variable == NULL)
    {
        list = vm->globalVariables;
        for(int i = 0; i < list->size; i++)
        {
            if(strncmp(name, list->data[i].name, strlen(name)) == 0)
            {
                variable = &list->data[i];
            }
        }
    }

    if(variable == NULL)
    {
        printf("\nWe got an out of scope variable in the SET function\n");
        printf("%s", name);
        exit(-1);
    }

    variable->value = value;

    variable = NULL;
    return;
}

void LOAD_func(VM* vm)
{
    command currentCommand = vm->program[(vm->r.ip)];
    values* arg = currentCommand.argument;
    if(arg->type != STRING)
    {
        printf("\nSomething went wrong, the LOAD func got something other than a string\n");
        exit(-1);
    }

    char* name = arg->value.name;

    //we first search through local varaibles

    Args* variable = NULL;

    frame_GraphResult f = frame_pop(vm->frames);
    if(f.success != 1)
    {
        printf("\n tried popping a frame off in DEFINE, failed\n");
        exit(-1);
    }
    Frame frame = f.value;
    args_list* list = frame.args;

    frame_push(vm->frames, frame);

    for(int i = 0; i < list->size; i++)
    {
        if(strncmp(name, list->data[i].name, strlen(name)) == 0)
        {
            variable = &list->data[i];
        }
    }

    if(variable == NULL)
    {
        list = vm->globalVariables;
        for(int i = 0; i < list->size; i++)
        {
            if(strncmp(name, list->data[i].name, strlen(name)) == 0)
            {
                variable = &list->data[i];
            }
        }
    }

    if(variable == NULL)
    {
        printf("\nWe got an out of scope variable in the LOAD function\n");
        printf("%s", name);
        exit(-1);
    }

    unsigned long int value = variable->value;

    values_push(vm->loadedValues, value);
}

void PUSH_func(VM* vm)
{
    command currentCommand = vm->program[(vm->r.ip)];
    values* arg = currentCommand.argument;
    if(arg->type != INTEGER)
    {
        printf("\nSomething went wrong, the LOAD func got something other than a string\n");
        exit(-1);
    }
    unsigned long int value = arg->value.x;

    values_push(vm->loadedValues, value);
}

void POP_func(VM* vm)
{
    values_GraphResult result = values_pop(vm->loadedValues);
}

void LABEL_func(VM* vm)
{
    command currentCommand = vm->program[(vm->r.ip)];
    values* arg = currentCommand.argument;
    
    if(strncmp("main", arg->value.name, strlen("main")) == 0)
    {
        //if it is the main function, we must manualle push on a frame
        //as we never jump to main
        Frame* f = (Frame *)malloc(sizeof(Frame));
        f->args = args_listCreate(4);
        f->previous = 0;
        f->current = vm->r.ip;
        frame_push(vm->frames, *f);
        free(f);
    }
}

void JUMP_func(VM* vm)
{
    command currentCommand = vm->program[(vm->r.ip)];
    values* arg = currentCommand.argument;
    if(arg->type == INTEGER)
    {
        //loop jump
        //yet to be added
        return;
    }
    if(arg->type == STRING)
    {
        //printf("\nyou got here\n");
        //function jump
        char* name = arg->value.name;
        command* commands = vm->program;
        
        int i = 0;
        while(1)
        {
            if(commands[i].instr == LABEL)
            {
                if(strncmp(name, commands[i].argument->value.name, strlen(name)) == 0)
                {
                    break;
                }
            }

            i++;
        }

        Frame* f = (Frame *)malloc(sizeof(Frame));

        f->previous = vm->r.ip;
        f->current = i;
        f->args = args_listCreate(4);
        vm->r.ip = i;
        frame_push(vm->frames, *f);
        free(f);
        return;
    }

    printf("\nJUMP func it was neither an integer or a string\n");
    exit(-1);
}

void RET_func(VM* vm)
{
    unsigned long int current = vm->r.ip;

    frame_GraphResult f = frame_pop(vm->frames);

    Frame frame = f.value;

    args_deleteList(frame.args);
    
    unsigned long int whereToGo = f.value.previous;

    signed long diff = whereToGo - current;

    vm->r.ip += diff;
}

void ADD_func(VM* vm)
{
    values_stack* stack = vm->loadedValues;

    values_GraphResult result = values_pop(stack);
    if(result.success != 1)
    {
        printf("\nSomething went wrong in ADD popping off the values stack 1\n");
        exit(-1);
    }
    vm->r.Var1 = result.value;

    result = values_pop(stack);

    if(result.success != 1)
    {
        printf("\nSomething went wrong in ADD popping off the values stack 2\n");
        exit(-1);
    }

    vm->r.Var2 = result.value;

    vm->r.Result = vm->r.Var1 + vm->r.Var2;

    values_push(stack, vm->r.Result);
}

void MIN_func(VM* vm)
{
    values_stack* stack = vm->loadedValues;

    values_GraphResult result = values_pop(stack);
    if(result.success != 1)
    {
        printf("\nSomething went wrong in MIN popping off the values stack 1\n");
        exit(-1);
    }
    vm->r.Var1 = result.value;

    result = values_pop(stack);

    if(result.success != 1)
    {
        printf("\nSomething went wrong in MIN popping off the values stack 2\n");
        exit(-1);
    }

    vm->r.Var2 = result.value;

    vm->r.Result = vm->r.Var1 - vm->r.Var2;

    values_push(stack, vm->r.Result);
}

void MUL_func(VM* vm)
{
    values_stack* stack = vm->loadedValues;

    values_GraphResult result = values_pop(stack);
    if(result.success != 1)
    {
        printf("\nSomething went wrong in MUL popping off the values stack 1\n");
        exit(-1);
    }
    vm->r.Var1 = result.value;

    result = values_pop(stack);

    if(result.success != 1)
    {
        printf("\nSomething went wrong in MUL popping off the values stack 2\n");
        exit(-1);
    }

    vm->r.Var2 = result.value;

    vm->r.Result = vm->r.Var1 * vm->r.Var2;

    values_push(stack, vm->r.Result);
}

void DIV_func(VM* vm)
{
    values_stack* stack = vm->loadedValues;

    values_GraphResult result = values_pop(stack);
    if(result.success != 1)
    {
        printf("\nSomething went wrong in DIV popping off the values stack 1\n");
        exit(-1);
    }
    vm->r.Var1 = result.value;

    result = values_pop(stack);

    if(result.success != 1)
    {
        printf("\nSomething went wrong in DIV popping off the values stack 2\n");
        exit(-1);
    }

    vm->r.Var2 = result.value;

    vm->r.Result = vm->r.Var1 / vm->r.Var2;

    values_push(stack, vm->r.Result);    
}