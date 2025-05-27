#pragma once

#include "commands.h"
#include "string.h"

DEFINE_LIST(command, command);

command* parse();
command* parseLine(char* line);