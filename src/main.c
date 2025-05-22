#include "main.h"


Program* initializePorgram()
{
    Program* p;


    return p;
}

VM* initializeVirtualMachine(Program* p)
{
    VM* virtualMachine;

    virtualMachine = (VM *)malloc(sizeof(VM));

    Args* globalVars = NULL;

    Frame* firstFrame = (Frame *)malloc(sizeof(Frame));
    firstFrame->current = 0;
    firstFrame->previous = 0;
    firstFrame->args = globalVars;

    unsigned long int initialValue = 0;

    values_stack* valuesStack = values_initializeStack(&initialValue);

    virtualMachine->frames = frame_initializeStack(firstFrame);
    virtualMachine->loadedValues = valuesStack;

    virtualMachine->program = p;
    return virtualMachine;
}

void destroyVM(VM* vm)
{
    values_stack* valuesStack = vm->loadedValues;
    frame_stack* frames = vm->frames;
    Args* globalVars = vm->globalVariables;
    Program* p = vm->program;
 
    free(p);
    free(globalVars);
    values_destroyStack(valuesStack);
    frame_destroyStack(frames);

    free(vm);
}

void Run_VM(VM* vm)
{
    Program* p = vm->program;
    unsigned long int* ip = &vm->r.ip;
    while(p[*ip].instr != HALT)
    {
        switch(p[*ip].instr)
        {

            default:
            printf("An unknown command has been put into the program. Error.");
            return;
            break;
        }


        *ip++;
    }
}


int main()
{
    


    printf("Program finished without issue");
    return 0;
}