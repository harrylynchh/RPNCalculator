/*
 *  parser.cpp
 *  Harry Lynch
 *  10/14/2024
 *
 *  Purpose: Implement parsing methods for the RPNCalc class to interpret input
 *
 */

#include "parser.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * name:      parseRString( )
 * purpose:   translate input into a string containing a full, formatted rstring
 * arguments: input stream to read from
 * returns:   a string containing the formatted rstring
 * effects:   reads from the stream and returns the formatted rstring
 */
string parseRString(istream &input) {
    stringstream ss;
    // add opening bracket + space to final string
    ss << "{" << " ";
    int bracecount = 1;
    string holder = "~";
    const string errorMsg = "Error: rstring braces don't match";

    while (bracecount != 0 and holder != "\0") {
        // hacky way to check for eof (.eof() wasn't working for some reason)
        holder = "\0";
        input >> holder;
        if (holder == "\0")
            continue;

        if (holder == "}") {
            // If braces are unbalanced after decrement, throw an error
            --bracecount;
            if (bracecount < 0)
                throw runtime_error(errorMsg);
        }
        // If another nested rstring begins, account for that in bracecount
        if (holder == "{")
            bracecount++;
        // add the space between elements of rstring
        ss << holder << " ";
    }
    // If there aren't enough closing braces for opening braces, throw err
    if (bracecount != 0)
        throw runtime_error(errorMsg);
    string result = ss.str();
    // Take off the hanging space that will be present from line 48
    result.pop_back();
    return result;
}