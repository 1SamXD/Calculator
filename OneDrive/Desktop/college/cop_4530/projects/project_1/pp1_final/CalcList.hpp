#ifndef CALCLIST_HPP
#define CALCLIST_HPP

//gets required header file
#include "CalcListInterface.hpp"
#include <iostream>
//gets required header file
#include <sstream>

//creates node for single linked list
class SNode {
    public:
        FUNCTIONS func;
        double operand;
        double nodeTotal;
        SNode* next;

        //intializes the node
        SNode(FUNCTIONS f, double op, double total) {
            this->func = f;
            this->operand = op;
            this->nodeTotal = total;
            this->next = nullptr;
        }
};

//implenting stack to single linked list
class LinkedStack {
    public:
        SNode* head = nullptr;
        LinkedStack();
        ~LinkedStack();
        bool empty() const;
        void push(FUNCTIONS f, double op, double total);
        void pop();
        double top_total() const;
        const SNode* top() const;
        int size() const;
    private:
        int cap;
};

//calculator class inherited from header file
class CalcList: public CalcListInterface {    
    public:    
        LinkedStack stack;
        CalcList();
        double total() const override;
        void newOperation(const FUNCTIONS func, const double operand) override;
        void removeLastOperation() override;
        std::string toString(unsigned short precision) const override;
    private:
        double currTotal;
};

//classes to handle erros 
class Exceptions {
    public:
        Exceptions(const std::string& msg) : message(msg) {}
        std::string printError() {
            return message;
        }
    private:
        std::string message;
};

//handles division by zero
class DivisionbyZero : public Exceptions {
    public:
        DivisionbyZero(const std::string& msg) : Exceptions(msg) {}
};

//handles if stack is empty and cannot retrieve node
class EmptyStack : public Exceptions {
    public:
        EmptyStack(const std::string& msg) : Exceptions(msg) {}
};

//handles if the function is not valid
class InvalidOperation : public Exceptions {
    public:
        InvalidOperation(const std::string& msg) : Exceptions(msg) {}
};

#endif