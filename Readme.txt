Inter-Process Communication Example Using Pipes and fork
Overview
This program demonstrates inter-process communication (IPC) between a parent process and a child process using pipes in a Unix-like operating system. The parent process sends messages to the child process, which then replies back. The communication is performed using two pipes: one for sending messages from the parent to the child, and another for sending responses from the child to the parent.

Requirements
A Unix-like operating system (Linux, macOS, etc.)
A C compiler (e.g., gcc)
Compilation
To compile the program, use the following command:

Using the Shell to run the program; run the following code: 
gcc -o My_program main.c

./My_program
