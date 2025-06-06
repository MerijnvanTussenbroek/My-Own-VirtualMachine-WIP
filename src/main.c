#include "main.h"


Program* initializeProgram()
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

    virtualMachine->r.temporaryStorageRegister = 0;
    virtualMachine->r.Var1 = 0;
    virtualMachine->r.Var2 = 0;
    virtualMachine->r.Result = 0;
    virtualMachine->r.ip = 0;
    virtualMachine->r.sp = 0;

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
    printf("\n\n");
    values_stack* valuesStack = vm->loadedValues;
    frame_stack* frames = vm->frames;
    args_list* globalVars = vm->globalVariables;
    
    for(int i = 0; i < globalVars->size; i++)
    {
        Args a = globalVars->data[i];
        printf("%s : %lu\n", a.name, a.value);
    }

    Frame f = frames->LL->data;

    for(int i = 0; i < f.args->size; i++)
    {
        Args b = f.args->data[i];
        printf("%s : %lu\n", b.name, b.value);
    }
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

    int amount = 0;

    *ip = 0;
    while(p[*ip].instr != HALT && amount < 50)
    {
        amount++;
        //printf("%lu", *ip);
        //showValues(vm);
        printCommand(&p[*ip]);
        
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
        (*ip)++;
    }
    if(p[*ip].instr == HALT)
    {
        showValues(vm);
    }
    else
    {
        printf("Something went wrong.");
    }
}


int main()
{
    Program* p = initializeProgram();
    VM* vm = initializeVirtualMachine(p);    

    Run_VM(vm);

    destroyVM(vm);

    printf("\n\n\nProgram finished without issue");
    return 0;
}