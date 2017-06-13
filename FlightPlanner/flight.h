
/*
* Assignment: Sprint 2 - Part 2
* Description: This Program is a flight planner
* Date: 10-12-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//flight.h
//header file for flight objects

#ifndef FLIGHTS_H
#define FLIGHTS_H

#include "DSString.h"

class Flight
{

public:
    //default constructor
    Flight();

    //destructor
    ~Flight();

    //overloaded constructor
    Flight(String, String, double, int);

    //getters and setters for cities
    void setCity1(String);
    String getCity1();
    void setCity2(String);
    String getCity2();

    //getter/setter for cost
    void setCost(double);
    double getCost();

    //getter/setter for time
    void setTime(int);
    int getTime();

private:
    //private data for flights
    String city1;
    String city2;
    double cost;
    int time;

};

#endif
