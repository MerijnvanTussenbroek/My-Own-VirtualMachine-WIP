#include "parser.h"

#include "list_impl.h"

#include <ctype.h>

DEFINE_LIST(command, command);

void parseLine(char* line, command_list* l);

void printCommand(command* c);

int readNum(char* input);
char* readName(char* input);

command* parse()
{

    command* listOfCommands;
    command_list* l = command_listCreate(4);

    printf("\nTrying to open the file");
    FILE* program = fopen("program.txt", "r");

    if(program == NULL)
    {
        printf("\nCould not open the file");
        exit(-1);
    }

    printf("\nOpened the file\n");
    rewind(program);

    char* output = malloc(sizeof(char) * 50);
    while(fgets(output, 50, program))
        parseLine(output, l);
    fclose(program);
    listOfCommands = (command *)malloc(l->size * sizeof(command));
    
    printf("\n\n");

    for(int i = 0; i < l->size; i++)
    {
        listOfCommands[i] = l->data[i];
    }

    command_deleteList(l);
    printf("\nfinished parsing\n");

    return listOfCommands;
}


void parseLine(char* line, command_list* l)
{
    char* input = line;
    //printf("%s\n", input);

    //printf("%c\n", line[0]);

    if(line[0] == '\0' || line[0] == '\n')
        return;
    
    command newCommand  = { 0 };
    newCommand.instr = NOTHING;
    newCommand.argument = NULL;

    switch(line[0])
    {
        case 'A': //ADD
            newCommand.instr = ADD;
            newCommand.argument = NULL;
        break;
        case 'B': //BEGIN
            newCommand.instr = BEGIN;
            newCommand.argument = NULL;
        break;
        case 'C':

        break;
        case 'D': //DEFINE DIV
            if(line[1] == 'E')
            {
                newCommand.instr = DEFINE;
                input += 7;
                newCommand.argument = (values *)malloc(sizeof(values));
                newCommand.argument->type = STRING;
                newCommand.argument->value.name = readName(input);
            }
            if(line[1] == 'I')
            {
                newCommand.instr = DIV;
                newCommand.argument = NULL;
            }
        break;
        case 'E':

        break;
        case 'F':

        break;
        case 'G':

        break;
        case 'H': //HALT
            newCommand.instr = HALT;
            newCommand.argument = NULL;
        break;
        case 'I':
            
        break;
        case 'J': //JUMP
            newCommand.instr = JUMP;
            newCommand.argument = (values *)malloc(sizeof(values));
            input += 5;
            if(isdigit(*input))
            {
                newCommand.argument->type = INTEGER;
                newCommand.argument->value.x = readNum(input);
            }
            else
            {
                newCommand.argument->type = STRING;
                newCommand.argument->value.name = readName(input);
            }
        break;
        case 'K':

        break;
        case 'L': // LABEL LOAD LOAD_REG
            newCommand.argument = (values *)malloc(sizeof(values));
            newCommand.argument->type = STRING;
            if(line[1] == 'A')
            {
                newCommand.instr = LABEL;
                input += 6;
            }
            if(line[4] == '_')
            {
                newCommand.instr = LOAD_REG;
                input += 9;
            }
            if(line[4] == ' ')
            {
                newCommand.instr = LOAD;
                input += 5;
            }

            newCommand.argument->value.name = readName(input);
        break;
        case 'M': // MUL
            newCommand.instr = MUL;
            newCommand.argument = NULL;
        break;
        case 'N': // NOTHING
            newCommand.instr = NOTHING;
            newCommand.argument = NULL;
        break;
        case 'O':

        break;
        case 'P': // POP PUSH
            if(line[1] == 'O')
            {
                newCommand.instr = POP;
                newCommand.argument = NULL;
            }
            if(line[1] == 'U')
            {
                newCommand.instr = PUSH;
                input += 5;
                newCommand.argument = (values *)malloc(sizeof(values));
                newCommand.argument->type = INTEGER;
                newCommand.argument->value.x = readNum(input);
            }
        break;
        case 'Q':

        break;
        case 'R': // READ_REG RET
            if(line[2] == 'T')
            {
                newCommand.instr = RET;
                newCommand.argument = NULL;
            }
            if(line[4] == '_')
            {
                newCommand.instr = READ_REG;
                newCommand.argument = (values *)malloc(sizeof(values));
                input += 9;
                newCommand.argument->type = INTEGER;
                newCommand.argument->value.num = readNum(input);
            }
        break;
        case 'S': // SET SUB
            if(line[1] == 'E')
            {
                newCommand.instr = SET;
                input += 4;
                newCommand.argument = (values *)malloc(sizeof(values));
                newCommand.argument->type = STRING;
                newCommand.argument->value.name = readName(input);
            }
            if(line[1] == 'U')
            {
                newCommand.instr = MIN;
                newCommand.argument = NULL;
            }
        break;
        case 'T':

        break;
        case 'U':

        break;
        case 'V':

        break;
        case 'W':

        break;
        case 'X':

        break;
        case 'Y':

        break;
        case 'Z':

        break;
        default:
            printf("A problem has occurred\n");
        break;
    }

    /*
    Here, we make a shallow copy of the newCommand struct
    This is exaclty what we want here, we want the argument pointer
    in the newCommand struct to be copied over, we thus want a shallow copy
    and not a deep copy
    */
    command_addToList(l, newCommand);
}

void printCommand(command* c)
{
    switch(c->instr)
    {
        case DEFINE:
            printf("DEFINE %s\n", c->argument->value.name);
        break;
        case SET:
            printf("SET %s\n", c->argument->value.name);
        break;
        case LOAD:
            printf("LOAD %s\n", c->argument->value.name);
        break;
        case PUSH:
            printf("PUSH %d\n", c->argument->value.x);
        break;
        case POP:
            printf("POP\n");
        break;
        case READ_REG:
            printf("READ_REG %d\n", c->argument->value.num);
        break;
        case LOAD_REG:
            printf("LOAD_REG %d\n", c->argument->value.num);
        break;
        case LABEL:
            printf("LABEL %s\n", c->argument->value.name);
        break;
        case JUMP:
            if(c->argument->type == INTEGER)
            {
                printf("JUMP %d\n", c->argument->value.x);
            }
            else
            {
                printf("JUMP %s\n", c->argument->value.name);
            }
        break;
        case RET:
            printf("RET\n");
        break;
        case ADD:
            printf("ADD\n");
        break;
        case MIN:
            printf("MIN\n");
        break;
        case MUL:
            printf("MUL\n");
        break;
        case DIV:
            printf("DIV\n");
        break;
        case BEGIN:
            printf("BEGIN\n");
        break;
        case NOTHING:
            printf("NOTHING\n");
        break;
        case HALT:
            printf("HALT\n");
        break;
        default:
            printf("something went wrong here\n");
        break;
    }
}

int readNum(char* input)
{
    char* begin = input;
    char* end;

    size_t length;

    while(*input != ' ' && *input != '\n')
        input++;

    length = input - begin;

    char* name = malloc(sizeof(char) * (length + 1));
    strncpy(name, begin, length);
    name[length] = '\0';
    int num = (int)strtol(begin, &end ,10);
    free(name);
    return num;
}

char* readName(char* input)
{
    char* begin = input;
    char* name;
    size_t length;
    while(*input != ' ' && *input != '\n')
        input++;

    length = input - begin;

    name = malloc(sizeof(char) * (length + 1));
    strncpy(name, begin, length);
    name[length] = '\0';
    return name;
}