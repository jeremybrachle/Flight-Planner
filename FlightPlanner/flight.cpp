
/*
* Assignment: Sprint 2 - Part 2
* Description: This Program is a flight planner
* Date: 10-12-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//flight.cpp
//implementation file for flights

#include "flight.h"
#include "DSString.h"

//default constructor
Flight::Flight() : city1(""), city2(""), cost(0.0), time(0) {}

//overloaded constructor
Flight::Flight(String c1, String c2, double money, int minutes)
{
    setCity1(c1);
    setCity2(c2);
    setCost(money);
    setTime(minutes);
}

//destructor
Flight::~Flight()
{
    //delete *Flight().city1;
}


//setter for city1
void Flight::setCity1(String city)
{
    city1 = city;
}

//getter for city1
String Flight::getCity1()
{
    return city1;
}

//setter for city2
void Flight::setCity2(String city)
{
    city2 = city;
}

//getter for city2
String Flight::getCity2()
{
    return city2;
}

//setter for cost
void Flight::setCost(double money)
{
    cost = money;
}

//getter for cost
double Flight::getCost()
{
    return cost;
}

//setter for time
void Flight::setTime(int minutes)
{
    time = minutes;
}

//getter for time
int Flight::getTime()
{
    return time;
}



