/*
 *  DatumStack.cpp
 *  Harry Lynch
 *  10/10/2024
 *
 *  Implementation of the DatumStack class and methods.
 *
 */

#include "DatumStack.h"
#include <stdexcept>
using namespace std;

/*
 * name:      DatumStack( )
 * purpose:   basic constructor
 * arguments: none
 * returns:   none
 * effects:   clears the stack.
 */
DatumStack::DatumStack() { this->stack.clear(); }

/*
 * name:      DatumStack( )
 * purpose:   array-size constructor to fill the stack as it's constructed
 * arguments: array of Datum objects and size of array
 * returns:   none
 * effects:   fills the stack with the datum provided in array order.
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; i++) {
        this->push(arr[i]);
    }
}

/*
 * name:      isEmpty( )
 * purpose:   determine if stack is empty
 * arguments: none
 * returns:   boolean if the stack is empty
 * effects:   none
 */
bool DatumStack::isEmpty() { return this->stack.empty(); }

/*
 * name:      clear( )
 * purpose:   remove all items from the stack
 * arguments: none
 * returns:   none
 * effects:   clears all Datum out of the Stack
 */
void DatumStack::clear() { this->stack.clear(); }

/*
 * name:      size( )
 * purpose:   find number of Datum in stack
 * arguments: none
 * returns:   integer of size
 * effects:   none
 */
int DatumStack::size() { return this->stack.size(); }

/*
 * name:      top( )
 * purpose:   return but don't remove top item on the stack
 * arguments: none
 * returns:   Datum containing the item on top of the stack
 * effects:   none
 */
// Throw an exception if trying to pop from empty
Datum DatumStack::top() {
    // Throw an exception if trying to pop from empty
    exceptHelp("Error: empty_stack");
    return this->stack.back();
}

/*
 * name:      pop( )
 * purpose:   remove one item off top of the stack
 * arguments: none
 * returns:   none
 * effects:   removes top item
 */
void DatumStack::pop() {
    // Throw an exception if trying to pop from empty
    exceptHelp("Error: empty_stack");
    this->stack.pop_back();
}

/*
 * name:      push( )
 * purpose:   add an element to the top of the stack
 * arguments: Datum element to add
 * returns:   none
 * effects:   adds a datum on a list
 */
void DatumStack::push(Datum element) { this->stack.push_back(element); }

/*
 * name:      exceptHelp( )
 * purpose:   Helper function to throw exceptions on empty list operations
 * arguments: message to throw
 * returns:   none
 * effects:   thorws an exception if empty
 */
void DatumStack::exceptHelp(string message) {
    if (this->isEmpty()) {
        throw runtime_error(message);
    }
}