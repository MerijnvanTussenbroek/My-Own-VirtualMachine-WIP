#pragma once
#include "virtualmachine.h"

void DEFINE_func(VM* vm);
void SET_func(VM* vm);
void LOAD_func(VM* vm);
void PUSH_func(VM* vm);
void POP_func(VM* vm);
void LABEL_func(VM* vm);
void JUMP_func(VM* vm);
void RET_func(VM* vm);
void ADD_func(VM* vm);
void MIN_func(VM* vm);
void MUL_func(VM* vm);
void DIV_func(VM* vm);
void LESS_func(VM* vm);
void MORE_func(VM* vm);
void EQUAL_func(VM* vm);
void AND_func(VM* vm);
void OR_func(VM* vm);
void NOT_func(VM* vm);