# My-Own-VirtualMachine
My own virtual machine based on the one I made through the tutorial

A virtual machine is supposed to work like a computer. You have registers, stack, heap, etc that change depending on the commands put into the machine.

Everything I define below is subject to change until I archive this repository

This virtual machine was designed for the C compiler to compile to, hence why we still have a basic machine.

We will use the stack I defined in the C datastructures repository.
The heap will be a huge array of raw bytes that will be allocated dynamically.
We will use 4 registers plus two special ones, an instruction pointer and stack pointer.

A command will consist of the following:
    an Opcode specifying the instruction
    no arguments, 1 argument or a list of arguments

An argument is defined as followed:
    the argument type,
    a union of either
        integer x
        char y
        double z
        string name
        register number

The register number is a number in the set [1..6]
register 1 is the temporary register
2 is reg Var1
3 is reg Var2
4 is reg Result
5 is ip
6 is sp

the VM struct containts the following
    a register struct r
    a frame stack
    a values stack
    a list of arguments, which are the global variables
    a program loaded into it


The parser in this repository is for the results of the C compiler made in Haskell
a C program compiled with that, can be run in here(after I'm finished, obviously)
