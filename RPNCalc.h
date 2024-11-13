/*
 *  RPNCalc.h
 *  Harry Lynch
 *  10/10/2024
 *
 *  Interface for the RPNCalc driver class, use the only public method, run(),
 * to use the RPNCalculator
 *
 */
#ifndef __RPN_CALC_H__
#define __RPN_CALC_H__

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include <iostream>

class RPNCalc {
  public:
    RPNCalc();
    void run();

  private:
    DatumStack stack;
    void run(istream &input, bool isMain);
    void got_RString(istream &input);
    void print();
    void drop();
    void dup();
    void swap();
    void knot();
    void arithmetic(char operation);
    void comparison(char operation);
    void equals();
    void exec();
    void file();
    void conditional();
    void takeTwo(Datum *first, Datum *second);
    Datum tryTop();
};

#endif