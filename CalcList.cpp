#include "CalcList.hpp"
#include <iostream>
#include <sstream>

//intializes the list
LinkedStack::LinkedStack() {
    this->head = nullptr;
    //cap counts steps
    this->cap = 0;
}

//deallocates list
LinkedStack::~LinkedStack() {
    while ( !empty() ) {
        pop();
    }
}

//if stack is empty, returns true
bool LinkedStack::empty() const {
    return head == nullptr;
}

//creates a node, saves the data, and increase step counter
void LinkedStack::push(FUNCTIONS f, double op, double total) {
    SNode* newNode = new SNode(f, op, total);
    newNode->next = head;
    head = newNode;
    cap++;
}

//removes node, deletes the data, decreases step counter, and is used to undo operation
void LinkedStack::pop() {
    if ( this->empty() ) {
        throw EmptyStack("Error: Stack is empty, no operations to remove");
    }
    else {
        SNode* temp = head;
        head = head->next;
        delete temp;
        cap--;
    }
}

//returns the total of the previous step or 0 if no previous step
double LinkedStack::top_total() const {
    if ( empty() ) {
        throw EmptyStack("Error: Stack is empty, cannot retrieve total");
    }
    else {
        return head->nodeTotal;
    }
}

//returns a node containing all data
const SNode* LinkedStack::top() const {
    if ( empty() ) {
        throw EmptyStack("Error: Stack is empty");
    }
    return head;                
    
}

//returns the amount of steps
int LinkedStack::size() const {
    return cap;
}

//intializes the total to 0
CalcList::CalcList() {
    currTotal = 0.0;
}        

//returns the current total of the step
double CalcList::total() const {
    return currTotal;
}

//runs the operations, the pushes new data onto stack
void CalcList::newOperation(const FUNCTIONS func, const double operand) {
    switch(func) {
            case ADDITION:
            currTotal += operand;
            break;
        case SUBTRACTION:
            currTotal -= operand;
            break;
        case MULTIPLICATION:
            currTotal *= operand;
            break;
        case DIVISION:
            if ( operand == 0 ) {
                throw DivisionbyZero("Error: Division by zero is not allowed");
                break;
            }
            currTotal /= operand;
            break;
        default:
            throw InvalidOperation("Error: Invalid operation");
            return;
    }
    stack.push(func, operand, currTotal);
}

//undo the last operation, then saves the previous total
void CalcList::removeLastOperation() {
    if ( stack.empty() ) {
        throw EmptyStack("Error: Stack is empty, no operations to undo");
    }

    stack.pop();
    if ( stack.empty() ) {
        currTotal = 0.0;
    }
    else {
        currTotal = stack.top_total();
    }
}

//prints all the steps with given precision
std::string CalcList::toString(unsigned short precision) const {
    if ( stack.empty() ) {
        throw EmptyStack("Error: Stack is empty, nothing to show");
    }

    std::ostringstream oss;

    SNode* current = stack.head;
    int size = stack.size();

    while ( current != nullptr ) {
        oss.precision(precision);
        oss << std::fixed;
        oss << size-- << ": ";

        switch(current->func) {
            case ADDITION:
                oss << current->nodeTotal - current->operand << "+";
                break;
            case SUBTRACTION:
                oss << current->nodeTotal + current->operand << "-";
                break;
            case MULTIPLICATION:
                oss << current->nodeTotal / current->operand << "*";
                break;
            case DIVISION:
                oss << current->nodeTotal * current->operand << "/";
                break;
        }

        oss << current->operand << "=" << current->nodeTotal << "\n";

        current = current->next;
    }

    return oss.str();
}

int main() {
    CalcList c;
    c.removeLastOperation();
    return 0;
}