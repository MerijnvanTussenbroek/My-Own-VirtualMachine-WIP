#include "parser.h"

#include "list_impl.h"

DEFINE_LIST(command, command);

void parseLine(char* line, command_list* l);
command* copyCommand(command* original);

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
    fseek(program, 0, SEEK_END);
    size_t length = ftell(program);
    rewind(program);

    char* output = malloc(sizeof(char) * 50);
    while(fgets(output, sizeof(49), program))
    {
        output[49] = '\0';
        parseLine(output, l);
    }
    
    
    fclose(program);

    listOfCommands = (command *)malloc(l->size * sizeof(command));
    
    for(int i = 0; i < l->size; i++)
    {
        listOfCommands[i] = *copyCommand(&(l->data[i]));
    }

    command_deleteList(l);
    return listOfCommands;
}


void parseLine(char* line, command_list* l)
{
    char* input = line;

    command* newCommand = (command *)malloc(sizeof(command));

    switch(line[0])
    {
        case 'A': //ADD

        break;
        case 'B': //BEGIN

        break;
        case 'C':

        break;
        case 'D': //DEFINE DIV
            if(line[1] == 'E')
            {

            }
            if(line[1] == 'I')
            {

            }
        break;
        case 'E':

        break;
        case 'F':

        break;
        case 'G':

        break;
        case 'H': //HALT

        break;
        case 'I':

        break;
        case 'J': //JUMP

        break;
        case 'K':

        break;
        case 'L': // LABEL LOAD LOAD_REG
            if(line[1] == 'A')
            {

            }
            if(line[4] == '_')
            {

            }
            if(line[4] == ' ')
            {

            }
        break;
        case 'M': // MUL

        break;
        case 'N': // NOTHING

        break;
        case 'O':

        break;
        case 'P': // POP PUSH
            if(line[1] == 'O')
            {

            }
            if(line[1] == 'U')
            {

            }
        break;
        case 'Q':

        break;
        case 'R': // READ READ_REG RET
            if(line[3] == 'T')
            {

            }
            if(line[4] == ' ')
            {

            }
            if(line[4] == '_')
            {

            }
        break;
        case 'S': // SET SUB
            if(line[1] == 'E')
            {

            }
            if(line[1] == 'U')
            {

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

        break;
    }
}

command* copyCommand(command* original)
{
    command* copy = malloc(sizeof(command));
    copy->instr = original->instr;
    copy->argument = (values *)malloc(sizeof(values));
    copy->argument = original->argument;
    return copy;
}