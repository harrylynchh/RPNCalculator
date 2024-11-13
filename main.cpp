
#include "RPNCalc.h"
#include <iostream>

using namespace std;

/*
 * name:      main( )
 * purpose:   Instantiate RPNCalc object and call the run method in a try-catch
 *            block.  This try catch is present to catch the "end program"
 *            exception thrown by the run() method when "TRUE" is passes as 2nd
 *            param.
 * arguments: none
 * returns:   int (technically)
 * effects:   begins and eventually ends the RPNCalculator
 */
int main() {
    RPNCalc RPNCalculator = RPNCalc();
    // Catch the exception thrown when quit is inputted or end of cin is reached
    try {
        RPNCalculator.run();
    } catch (string endMsg) {
        cerr << endMsg;
    }
    return 0;
}