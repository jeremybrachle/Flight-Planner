
/*
* Assignment: Sprint 2 - Part 2
* Description: This Program is a flight planner
* Date: 10-12-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

#ifndef QUEUE
#define QUEUE

#include "linkedlist.h"

template<class T>
class Queue{

    public:

        T dequeue();
        T peek();
        void enqueue(T);
        bool isEmpty();

    private:

        LinkedList<T> data;

};

//Write your implementation here

//enqueue onto the queue
template<typename T>
void Queue<T>::enqueue(T val)
{
    this->data.addToBack(val);
}

//dequeue off the queue
template<typename T>
T Queue<T>::dequeue()
{
    return this->data.removeFirst();
}

//peek at the last element in the queue
template<typename T>
T Queue<T>::peek()
{
    return this->data.getLast();
}

//check to see if the queue is empty
template<typename T>
bool Queue<T>::isEmpty()
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
