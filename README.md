Reverse Polish Notation Calculator\
Author: Harry Lynch 10/10/2024

**Summary:**
------------------------------

   This program is an implementation of Reverse Polish Notation (postfix notation)
style calculator which, at it's core, uses a basic stack to maintain the order
of operations and execute calculations.  Taking input from cin, the calculator 
is capable of executing boolean comparisons, conditional execution, 
and arithmetic.  Also note that this calculator is technically turing complete.

**SEE:** https://en.wikipedia.org/wiki/Reverse_Polish_notation

**Compilation and Execution:**
-------------------------------

To compile the program, run 'make' in a command line in the installed 
directory. NOTE: program uses **clang++** to compile.

To run the program, execute the resulting RPNCalculator executable w/:
**./RPNCalculator**


**Commands/Usage:**
-----------------------------
#t: adds boolean true\
#f: adds boolean false\
not: flips value of a boolean on top of the stack.\
print: prints the top value of the stack without removing it.\
clear: clears all calculator data\
drop: removes top element\
dup: duplicates top element\
swap: swaps the first and second elements on the stack\
quit: exits program\

arithmetic operators (+, -, *, /, mod): execute the respective operation on the\
                    top two elements on the stack (must be integers)

comparison operators (<, >, <=, >=, ==): takes two elements off, preforms\
                    comparison, and places the boolean result back on stack.

rstrings: A sequence of commands to be executed wrapped in curly braces\
          (e.g { 2 2 + } is an rstring that calculates 2 + 2 = 4)

exec: executes the top element on the stack (must be an rstring)\

file: executes the top element on the stack (must be an rstring containing a filename),\
      runs the file which must contain RPNCalculator commands and returns the \
      result to the stack.\

if: takes top two (rstring) elements off the stack then a boolean.  Evaluates\
    the boolean and if true, it 'exec's the second rstring off the stack.  If false,\
    it executes the first rstring off the stack.\

**Provided Files:**
-------------------------------
    
main.cpp: main driver file for the program\
Makefile: means of compiling the program with 'make'.\
Datum.h:  provided interface object to hold and interpret various datatypes.\
Datum.o:  Compiled implementation of a Datum object\
DatumStack.h:   interface for the DatumStack class.\
DatumStack.cpp: implementation of a Stack of Datum Objects\
parser.cpp:  Implementation of the rstring parser\
parser.h:    Interface for parser\
RPNCalc.cpp: Main implementation of Calculator functionality\
RPNCalc.h:   Interface for RPNCalc\
