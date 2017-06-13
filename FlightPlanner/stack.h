

/*
* Assignment: Sprint 2 - Part 2
* Description: This Program is a flight planner
* Date: 10-12-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

#ifndef STACK
#define STACK

#include "linkedlist.h"

template<class T>
class Stack{

    public:

        T pop();
        T peek();
        void push(T);
        bool isEmpty();

    private:

        LinkedList<T> data;

};

//Write your implementation here

//push onto the stack
template<typename T>
void Stack<T>::push(T val)
{
    this->data.addToBack(val);
}

//pop off the stack
template<typename T>
T Stack<T>::pop()
{
    return this->data.removeLast();
}

//peek at the next element
template<typename T>
T Stack<T>::peek()
{
    return this->data.getLast();
}

//check to see if the stack is empty
template<typename T>
bool Stack<T>::isEmpty()
{
    if (this->data.isEmpty() == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}



#endif
