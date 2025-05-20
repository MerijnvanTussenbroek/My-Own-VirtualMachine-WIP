#include "main.h"


int main()
{
    printf("test");

    frameStack_stack* stack;

    Frame* f = (Frame *)malloc(sizeof(Frame));

    stack = (frameStack_stack *)frameStack_initializateLinkedList(f);


    printf("Program finished without issue");
    return 0;
}