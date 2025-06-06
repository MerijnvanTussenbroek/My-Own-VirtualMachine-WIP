#include "main.h"


Program* initializePorgram()
{
    Program* p;

    p = (Program *)malloc(sizeof(Program));

    p = (Program *)parse();

    return p;
}

VM* initializeVirtualMachine(Program* p)
{
    VM* virtualMachine;

    virtualMachine = (VM *)malloc(sizeof(VM));

    args_list* l = args_listCreate(1);

    Frame* firstFrame = (Frame *)malloc(sizeof(Frame));
    firstFrame->current = 0;
    firstFrame->previous = 0;
    
    virtualMachine->globalVariables = l;

    unsigned long int initialValue = 0;

    values_stack* valuesStack = values_initializeStack(initialValue);

    virtualMachine->frames = frame_initializeStack(*firstFrame);
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
    args_list* globalVars = vm->globalVariables;
    Program* p = vm->program;
 
    free(p);
    args_deleteList(globalVars);
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
            SET_func(vm);
            break;
            case LOAD:
            LOAD_func(vm);
            break;
            case PUSH:
            PUSH_func(vm);
            break;
            case POP:
            POP_func(vm);
            break;
            case READ_REG:
            READ_REG_func(vm);
            break;
            case LOAD_REG:
            LOAD_REG_func(vm);
            break;
            case LABEL:
            LABEL_func(vm);
            break;
            case JUMP:
            JUMP_func(vm);
            break;
            case RET:
            RET_func(vm);
            break;
            case ADD:
            ADD_func(vm);
            break;
            case MIN:
            MIN_func(vm);
            break;
            case MUL:
            MUL_func(vm);
            break;
            case DIV:
            DIV_func(vm);
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

void showProgram(Program* p)
{
    unsigned long int* ip = 0;
    while(p[*ip].instr != HALT)
    {
        
        (*ip)++;
        switch(p[*ip].instr)
        {
            case DEFINE:
            
            break;
            case SET:
            
            break;
            case LOAD:
            
            break;
            case PUSH:
            
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
                
                return;
            break;
            default:
            printf("An unknown command has been put into the program. Error.");
            return;
            break;
        }
    }
}


int main()
{
    Program* p = initializePorgram();
    //VM* vm = initializeVirtualMachine(NULL);    

    //destroyVM(vm);

    printf("\n\n\nProgram finished without issue");
    return 0;
}