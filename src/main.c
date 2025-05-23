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

void showValues(VM* vm)
{

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
        showValues(vm);
        (*ip)++;
        switch(p[*ip].instr)
        {
            case DEFINE:
            DEFINE_func(vm);
            break;
            case SET:

            break;
            case LOAD:

            break;
            case PUSH:

            break;
            case READ:

            break;
            case POP:

            break;
            case READ_REG:

            break;
            case LOAD_REG:

            break;
            case LABEL:

            break;
            case JUMP:

            break;
            case LOOP:

            break;
            case RET:

            break;
            case ADD:

            break;
            case MIN:

            break;
            case MUL:

            break;
            case DIV:

            break;
            case HALT:
                destroyVM(vm);
                return;
            break;
            default:
            printf("An unknown command has been put into the program. Error.");
            return;
            break;
        }
    }
    if(p[*ip].instr == HALT)
    {
        showValues(vm);
    }
    else
    {
        printf("Something went wrong.");
    }

    destroyVM(vm);
}


int main()
{
    


    printf("Program finished without issue");
    return 0;
}