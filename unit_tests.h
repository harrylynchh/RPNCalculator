/*
 *  unit_tests.h
 *  Harry Lynch
 *  10/10/2024
 *
 *  Implementation of tests for methods associated with the Datum Stack and
 *  parser classes
 *
 *  NOTE: In order to run, use AutumnMoon.cpp-unit_test Vscode extension and the
 *  in-editor play button
 *
 */
#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

// test for DatumStack constructors
void DS_constructorTest() {
    // check that stack is initialized and that items can be pushed to the stack
    DatumStack stack = DatumStack();
    assert(stack.isEmpty());
    stack.push(Datum(5));
    assert(stack.size() == 1);
    // Check that array constructor works and that the stack is formed properly
    Datum arr[5] = {Datum("here"), Datum(5), Datum(-3), Datum(true), Datum(1)};
    DatumStack stack2 = DatumStack(arr, 5);
    assert(stack2.size() == 5);
    assert(stack2.top() == arr[4]);
}

// Check the isEmpty method of Datum Stack
void DS_isEmptyTest() {
    DatumStack stack = DatumStack();
    assert(stack.isEmpty());

    Datum arr[5] = {Datum("here"), Datum(5), Datum(-3), Datum(true), Datum(1)};
    DatumStack stack2 = DatumStack(arr, 5);
    assert(not stack2.isEmpty());
}

// Check clear method of Datum Stack
void DS_clearTest() {
    Datum arr[5] = {Datum("here"), Datum(5), Datum(-3), Datum(true), Datum(1)};
    DatumStack stack2 = DatumStack(arr, 5);
    assert(stack2.size() == 5);
    stack2.clear();
    assert(stack2.size() == 0);
    assert(stack2.isEmpty());
}

// Check size method of DatumStack
void DS_sizeTest() {
    Datum arr[5] = {Datum("here"), Datum(5), Datum(-3), Datum(true), Datum(1)};
    DatumStack stack2 = DatumStack(arr, 5);
    assert(stack2.size() == 5);
    stack2.pop();
    assert(stack2.size() == 4);
    stack2.clear();
    assert(stack2.size() == 0);
}

// Check that top is consistently correct for DatumStack
void DS_topTest() {
    Datum arr[5] = {Datum("here"), Datum(5), Datum(-3), Datum(true), Datum(1)};
    DatumStack stack = DatumStack(arr, 5);
    assert(stack.top() == arr[4]);
    stack.pop();
    assert(stack.top() == arr[3]);
    stack.pop();
    assert(stack.top() == arr[2]);
    stack.pop();
    assert(stack.top() == arr[1]);
    stack.pop();
    assert(stack.top() == arr[0]);
}

// Check if top throws the proper exception when attempting to take from empty
void DS_topExceptionTest() {
    DatumStack stack = DatumStack();
    bool thrown = false;
    assert(stack.size() == 0);
    try {
        stack.top();
    } catch (const runtime_error &e) {
        std::cerr << e.what() << '\n';
        thrown = true;
    }
    assert(thrown);
}

// Check pop method of DS class loopily
void DS_popTest() {
    Datum arr[5] = {Datum("here"), Datum(5), Datum(-3), Datum(true), Datum(1)};
    DatumStack stack = DatumStack(arr, 5);
    int i = 5;
    while (not stack.isEmpty()) {
        assert(stack.size() == i);
        stack.pop();
        i--;
    }
}

// Check if pop throws the proper exception when attempting to take from empty
void DS_popExceptionTest() {
    DatumStack stack = DatumStack();
    bool thrown = false;
    assert(stack.size() == 0);
    try {
        stack.pop();
    } catch (const runtime_error &e) {
        std::cerr << e.what() << '\n';
        thrown = true;
    }
    assert(thrown);
}

// Check push method loopily
void DS_pushTest() {
    int ctr = 0;
    DatumStack stack = DatumStack();
    for (int i = 0; i < 100; i++) {
        stack.push(Datum(5));
        stack.push(Datum("string"));
        stack.push(Datum(true));
        ctr += 3;
    }
    assert(stack.size() == ctr);
}

/******************************************************************************/
// **PARSER TESTS**

// Base case check for parsing a basic rString
void P_basicRStringTest() {
    istringstream iss(" 2 2 + }");
    string res = parseRString(iss);
    assert(res == "{ 2 2 + }");
}

// Tests if there's an extra open brace with no close brace (don't believe we
// need to implement this behavior but should throw exception)
void P_ImproperRStringTest() {
    istringstream iss(" 2 2 { + }");
    string res;
    try {
        res = parseRString(iss);
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << res;
}

// Tests cases of nested rstrings and handling multiple braces
void P_NestedRStringTest() {
    istringstream iss(" 2 { 1 2 / } 2 + } ");
    string res = parseRString(iss);
    cout << res;
    assert(res == "{ 2 { 1 2 / } 2 + }");
}

// Test examples from the spec
void P_SpecExampleTests() {
    istringstream iss(" 1 2 + } ");
    string res = parseRString(iss);
    assert(res == "{ 1 2 + }");

    istringstream iss2(" 1 { 4 2 / } / } ");
    res = parseRString(iss2);
    assert(res == "{ 1 { 4 2 / } / }");
}

// Test whitespace example from the spec
void P_SpecWhitespaceTests() {
    istringstream iss(" 1 \n 2 \n + }");
    string res = parseRString(iss);
    assert(res == "{ 1 2 + }");
}

// Test how parser handles strings of characters and not separating the chars
void P_StringTest() {
    istringstream iss(" Lorem ipsum dolor sit amet. }");
    string res = parseRString(iss);
    assert(res == "{ Lorem ipsum dolor sit amet. }");
}

//  Tests nesting with strings
void P_NestedStringTest() {
    istringstream iss(" Lorem { ipsum dolor } sit amet. }");
    string res = parseRString(iss);
    assert(res == "{ Lorem { ipsum dolor } sit amet. }");
}

// Tests both strings and ints
void P_ChaChaChaTest() {
    istringstream iss(" one two { 1 + 2 } { cha cha cha } { cha cha } }");
    string res = parseRString(iss);
    assert(res == "{ one two { 1 + 2 } { cha cha cha } { cha cha } }");
}

// Tests if filenames are parsed correctly.
void P_fileTest() {
    istringstream iss(" test20.cyl }");
    string res = parseRString(iss);
    assert(res == "{ test20.cyl }");
}