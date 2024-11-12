/*
 *  Datum.h
 *  Harry Lynch
 *  10/10/2024
 *
 *  Interface for the Datum class which is the primary way to store input into
 *  the RPNCalculator stack
 *
 */
#ifndef DATUM_H
#define DATUM_H

#include <string>

class Datum {
  public:
    Datum(const Datum &d);
    explicit Datum(int i);
    explicit Datum(bool b);
    explicit Datum(const char *s);
    explicit Datum(std::string s);

    bool isInt() const;
    bool isBool() const;
    bool isRString() const;

    Datum &operator=(const Datum &d);
    bool operator==(Datum &d) const;
    bool operator<(Datum &d) const;

    int getInt() const;
    bool getBool() const;
    std::string getRString() const;
    std::string toString() const;

  private:
    typedef enum { D_INT = 0, D_BOOL, D_RSTRING } datumty;

    datumty ty;

    int idata;
    bool bdata;
    std::string sdata;
};

#endif
