#include "parser.h"

#include "list_impl.h"

DEFINE_LIST(command, command);

command* parse()
{

    command* listOfCommands;
    command_list* l = command_listCreate(4);

    FILE* program = fopen("program.txt", "r");

    if(program == NULL)
    {
        exit(-1);
    }

    fseek(program, 0, SEEK_END);
    size_t length = ftell(program);
    rewind(program);

    
    
    fclose(program);

    return listOfCommands;
}


command* parseLine(char* line)
{
    char* input = line;


}