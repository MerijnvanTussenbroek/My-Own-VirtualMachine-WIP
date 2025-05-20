# My-Own-VirtualMachine
My own virtual machine based on the one I made through the tutorial

A virtual machine is supposed to work like a computer. You have registers, stack, heap, etc that change depending on the commands put into the machine.

Everything I define below is subject to change until I archive this repository

This virtual machine was designed for the C compiler to compile to, hence why we still have a basic machine.

We will use the stack I defined in the C datastructures repository.
The heap will be a huge array of raw bytes that will be allocated dynamically.
We will use 4 registers plus a special one for the program pointer.

We will define the following commands:

