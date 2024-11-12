/*
 *  DatumStack.h
 *  Harry Lynch
 *  10/10/2024
 *
 *  CS 15 Project 2 RPNCalculator
 *
 *  Interface for the DatumStack class.  Shows all declarations.
 *
 */

#ifndef __DATUM_STACK_H
#define __DATUM_STACK_H

#include "Datum.h"
#include <list>
using namespace std;

class DatumStack {
  public:
    DatumStack();
    DatumStack(Datum arr[], int size);
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum element);

  private:
    list<Datum> stack;

    void exceptHelp(string message);
};
#endif
