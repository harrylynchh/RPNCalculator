/*
 *  RPNCalc.cpp
 *  Harry Lynch
 *  10/10/2024
 *
 *  Main driver for the RPNCalculator program featuring loop among other methods
 *
 */

// These includes are necessary for got_int( )
#include "RPNCalc.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

/*
 * Name: got_int
 * Purpose: determines if a string contains an integer and loads said
 *           integer into an integer variable whose address has been
 *           passed to this function
 * Parameters: a string to check if it contains an integer as well as
 *              a pointer to an integer to load in the event an
 *              integer can be parsed from said string
 * Returns: a boolean where true indicates an integer was successfully
 *           parsed from the provided string (and therefore the
 *           addressed integer has been loaded) and false indicates
 *           an integer could not be read
 * Effects: the integer pointed to by the passed pointer will be updated
 *           with the integer parsed from the string in the event true
 *           is returned (otherwise nothing happens)
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this comment!
 */
bool got_int(string s, int *resultp) {
    /* Holds the first non-whitespace character after the integer */
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name:      RPNCalc( )
 * purpose:   Constructor
 * arguments: None
 * returns:   None
 * effects:   instantiates a fresh stack, the only member of the class.
 */
RPNCalc::RPNCalc() { this->stack.clear(); }

/*
 * name:      run( )
 * purpose:   Main loop for the program, takes in and executes commands from cin
 *            and serves as the outward facing call function for the class.
 * arguments: none
 * returns:   none
 * effects:   calls the overload function defined below/
 */
void RPNCalc::run() { run(cin, true); }

/*
 * name:      run( )
 * purpose:   Main loop for the program, takes in and executes commands from cin
 *            and acts as a helper function to execute rstrings/files within the
 *            calculator
 * arguments: an input stream to read from and a state variable to determine
 *            whether or not to continue the program after the loop ends, only
 *            use true for the main loop and for helper-calls use false.
 * returns:   none
 * effects:   mutates the stack as the prompt requires.
 */
void RPNCalc::run(istream &input, bool isMain) {
    string holder;
    int intHolder;
    while (input >> holder and holder != "quit") {
        if (got_int(holder, &intHolder))
            this->stack.push(Datum(intHolder));
        else if (holder == "#t")
            this->stack.push(Datum(true));
        else if (holder == "#f")
            this->stack.push(Datum(false));
        else if (holder == "{")
            got_RString(input);
        else if (holder == "print")
            print();
        else if (holder == "clear")
            this->stack.clear();
        else if (holder == "drop")
            drop();
        else if (holder == "dup")
            dup();
        else if (holder == "swap")
            swap();
        else if (holder == "not")
            knot();
        else if (holder == "+")
            arithmetic('+');
        else if (holder == "-")
            arithmetic('-');
        else if (holder == "*")
            arithmetic('*');
        else if (holder == "/")
            arithmetic('/');
        else if (holder == "mod")
            arithmetic('%');
        else if (holder == ">")
            comparison('>');
        else if (holder == "<")
            comparison('<');
        else if (holder == "==")
            equals();
        else if (holder == ">=")
            comparison(')');
        else if (holder == "<=")
            comparison('(');
        else if (holder == "exec")
            exec();
        else if (holder == "file")
            file();
        else if (holder == "if")
            conditional();
        else {
            cerr << holder << ": unimplemented" << endl;
        }
    }
    string endMsg = "Thank you for using RPNCalculator.\n";
    if (holder == "quit" or isMain)
        throw endMsg;
}

/*
 * name:      got_RString( )
 * purpose:   Attempt to read in an RString and if it's invalid catch the error
 *            and forward it.
 * arguments: input stream to send to the parser after the first { is read.
 * returns:   none
 * effects:   pushes the formatted rstring to the stack
 */
void RPNCalc::got_RString(istream &input) {
    string result;
    try {
        result = parseRString(input);
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
        return;
    }
    this->stack.push(Datum(result));
}

/*
 * name:      print( )
 * purpose:   print the top item off the stack without removing it
 * arguments: none
 * returns:   none
 * effects:   sends the contents of the topmost Datum object to cout
 */
void RPNCalc::print() {
    Datum first = tryTop();
    if (first.toString() == "NULL")
        return;
    cout << first.toString() << endl;
}

/*
 * name:      drop( )
 * purpose:   remove the top item off the stack, ensure it can be done and catch
 *            the exception otherwise.
 * arguments: none
 * returns:   none
 * effects:   removes the top item off the stack.
 */
void RPNCalc::drop() {
    try {
        this->stack.pop();
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

/*
 * name:      dup( )
 * purpose:   duplicate the top item off the stack
 * arguments: none
 * returns:   none
 * effects:   checks the topmost item and copies it into a new Datum pushed.
 */
void RPNCalc::dup() {
    Datum first = tryTop();
    if (first.toString() == "NULL")
        return;
    this->stack.push(Datum(first));
}

/*
 * name:      swap( )
 * purpose:   Swap the top two elements of the stack
 * arguments: none
 * returns:   none
 * effects:   Takes the first two items off and adds them back in reverse order.
 */
void RPNCalc::swap() {
    Datum oldTop = Datum("NULL");
    Datum newTop = Datum("NULL");
    takeTwo(&oldTop, &newTop);
    if (newTop.toString() == "NULL" or oldTop.toString() == "NULL")
        return;

    this->stack.push(oldTop);
    this->stack.push(newTop);
}

/*
 * name:      knot( )
 * purpose:   execute the 'not' command (had to get creative and couldnt use
 * not) flip the boolean on top of the stack. arguments: none returns:   none
 * effects:   removes the top item, checks if it's boolean, if it is then flip
 *            and add back to the stack.
 */
void RPNCalc::knot() {
    Datum first = tryTop();
    if (first.toString() == "NULL")
        return;
    drop();

    if (not first.isBool()) {
        cerr << "Error: datum_not_bool" << endl;
        return;
    }

    Datum newBool = Datum(not first.getBool());

    this->stack.push(newBool);
}

/*
 * name:      arithmetic( )
 * purpose:   execute all the basic arithmetic operations (+ - * / %) /
 * propogate errors if necessary arguments: character of the proper operation to
 * use. returns:   none effects:   executes the parameritized operation on the
 * top two items on stack.
 */
void RPNCalc::arithmetic(char operation) {
    Datum first = Datum("NULL");
    Datum second = Datum("NULL");
    takeTwo(&first, &second);

    if (first.toString() == "NULL" or second.toString() == "NULL")
        return;

    if (not first.isInt() or not second.isInt()) {
        cerr << "Error: datum_not_int" << endl;
        return;
    }
    if (first.getInt() == 0 and (operation == '/' or operation == '%')) {
        cerr << "Error: division by 0." << endl;
        return;
    }

    int result;
    switch (operation) {
    case '+':
        result = first.getInt() + second.getInt();
        break;
    case '-':
        result = second.getInt() - first.getInt();
        break;
    case '*':
        result = first.getInt() * second.getInt();
        break;
    case '/':
        result = (second.getInt() / first.getInt());
        break;
    case '%':
        result = second.getInt() % first.getInt();
        break;
    }
    this->stack.push(Datum(result));
}

/*
 * name:      comparison( )
 * purpose:   execute the comparison operations (< > <= >=)
 * arguments: character representing requisite operation
 * returns:   none
 * effects:   takes the two top items off to compare and adds a bool back
 * note:      EQUAL OPERATOR IN THE FUNCTION AFTER THIS B/C EQUAL TAKES BOOLS &
 *            INTS
 */
void RPNCalc::comparison(char operation) {
    Datum first = Datum("NULL");
    Datum second = Datum("NULL");
    takeTwo(&first, &second);
    if (first.toString() == "NULL" or second.toString() == "NULL")
        return;
    // Ensure there are two ints on top to compare
    if (not(first.isInt() and second.isInt())) {
        cerr << "Error: datum_not_int" << endl;
        return;
    }

    bool result;
    switch (operation) {
    case '>':
        result = (second.getInt() > first.getInt());
        break;
    case '<':
        result = (second.getInt() < first.getInt());
        break;
    case ')':
        result = (second.getInt() >= first.getInt());
        break;
    case '(':
        result = (second.getInt() <= first.getInt());
        break;
    }
    this->stack.push(Datum(result));
}

/*
 * name:      equals( )
 * purpose:   Execute the final comparison operation, ==, by taking two datum
 * and if they're of the same type, compare them, or otherwise push false
 * arguments: none
 * returns:   none
 * effects:   take top two items off and pop on comparison bool
 * note:      I felt the best way to do this one was to just try to do direct
 *            comparisons and if the exception throws then obviously the two
 *            datum are of inequal type.  I toyed around with some implicit type
 *            definitions but this was the most concrete although not as pretty.
 */
void RPNCalc::equals() {
    Datum first = Datum("NULL");
    Datum second = Datum("NULL");
    takeTwo(&first, &second);
    if (first.toString() == "NULL" or second.toString() == "NULL")
        return;

    try {
        this->stack.push(Datum((first.getInt() == second.getInt())));
        return;
    } catch (runtime_error &e) { /* Intentionally blank*/
    }

    try {
        this->stack.push(Datum((first.getBool() == second.getBool())));
        return;
    } catch (runtime_error &e) { /* Again, intentionally blank */
    }

    try {
        this->stack.push(Datum((first.getRString() == second.getRString())));
        return;
    } catch (runtime_error &e) { /* One more time blank */
    }
    // at this point, we know first and second are of diff types and demo always
    // returns false for differing types
    this->stack.push(Datum(false));
}

/*
 * name:      exec( )
 * purpose:   Run the rstring on top of the stack executing all RPNCalc commands
 *            within and adding them to the stack (using run() as a helper)
 * arguments: none
 * returns:   none
 * effects:   pops a Datum off and runs the rstring inside or throws an error
 */
void RPNCalc::exec() {
    Datum first = tryTop();
    string rString = first.toString();
    if (rString == "NULL")
        return;
    drop();
    if (not first.isRString()) {
        cerr << "Error: cannot execute non rstring" << endl;
        return;
    }
    // Take off the brackets on the front and back of the rstring to prevent
    // weird infinite loops
    rString.erase(rString.begin());
    rString.pop_back();
    istringstream iss(rString);
    // Call with FALSE so program doesn't quit completely on completion.
    run(iss, false);
}

/*
 * name:      file( )
 * purpose:   open and execute the filename within the rstring on the top.
 * arguments: none
 * returns:   none
 * effects:   pulls rstring off the top, open the filename within, check valid,
 *            then pass the filestream to the run() function with FALSE
 * (helper).
 */
void RPNCalc::file() {
    Datum file = tryTop();
    string fileName = file.toString();
    if (file.toString() == "NULL")
        return;
    drop();
    if (not file.isRString()) {
        cerr << "Error: file operand not rstring\n";
        return;
    }
    // Trim the "{ " and " }" off either end of the filename
    fileName.erase(fileName.end() - 2, fileName.end());
    fileName.erase(fileName.begin(), fileName.begin() + 2);
    // Attempt to open, and then run fstream through it's own instance of loop.
    ifstream stream;
    stream.open(fileName);
    if (not stream.is_open()) {
        cerr << "Unable to read " << fileName << endl;
        return;
    }

    try {
        run(stream, false);
        stream.close();
    } catch (string exitMsg) {
        stream.close();
        throw exitMsg;
    }
}

/*
 * name:      conditional( )
 * purpose:   execute the "if" command, taking two rstrings and a boolean off
 * the top and execute the topmost rstring if the conditon is false, and the
 * bottommost if it is true. arguments: none returns:   none effects:   takes 3
 * Datum off stack, evaluates condition if all Datum are valid then test
 * condition and add respective rstring back onto stack, then exec() that
 * rstring.
 */
void RPNCalc::conditional() {
    Datum falseExec = Datum("NULL");
    Datum trueExec = Datum("NULL");
    takeTwo(&falseExec, &trueExec);
    if (falseExec.toString() == "NULL" or trueExec.toString() == "NULL")
        return;

    Datum condition = tryTop();
    if (condition.toString() == "NULL")
        return;
    drop();

    if (not falseExec.isRString() or not trueExec.isRString()) {
        cerr << "Error: expected rstring in if branch" << endl;
        return;
    }
    if (not condition.isBool()) {
        cerr << "Error: expected boolean in if test" << endl;
        return;
    }
    // Ternary for pushing correct rString back to stack
    (condition.getBool()) ? this->stack.push(trueExec)
                          : this->stack.push(falseExec);
    // Run that recently-pushed rstring
    exec();
}

/*
 * name:      takeTwo( )
 * purpose:   helper function to do the repetitive task of collecting and
 * pulling off two Datum from the stack arguments: references to two datum to
 * save values returns:   none effects:   copies the datum currently on top of
 * the stack to the first ref, removes it, then does the same to second ref.
 */
void RPNCalc::takeTwo(Datum *first, Datum *second) {
    *first = tryTop();
    if (first->toString() == "NULL")
        return;
    drop();

    *second = tryTop();
    if (second->toString() == "NULL")
        return;
    drop();
}

/*
 * name:      tryTop( )
 * purpose:   helper function to execute try-catch to grab a datum off the top
 *            this is done to avoid try-catches everywhere
 * arguments: none
 * returns:   copy of topmost datum
 * effects:   none on stack itself
 */
Datum RPNCalc::tryTop() {
    Datum first = Datum('a');
    try {
        first = this->stack.top();
    } catch (runtime_error &e) {
        std::cerr << e.what() << '\n';
        return Datum("NULL");
    }
    return first;
}