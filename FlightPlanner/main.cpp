
/*
* Assignment: Sprint 2 - Part 2
* Description: This Program is a flight planner
* Date: 10-12-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

/*
Online sources I referenced:
cplusplus.com
tutorialspoint.com
cppreference.com
stackoverflow.com
*/

//CATCH_CONFIG_RUNNER tells the catch library that this
//project will now explicitly call for the tests to be run.
#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "vector.h"
#include "linkedlist.h"
#include "stack.h"
#include "queue.h"
#include "flight.h"

using namespace std;

//custom functions:
//return the index of a given origin city
int getIndex(Vector< LinkedList<String> >, String);
//return a Vector of a Stack of Strings that will hold all paths, given adjacency list and two cities
void findPath(Vector< Stack<String> >&, Vector< LinkedList<String> >, String, String);
//remove erroneous values from previously traveled cities
void removeErroneousCities(LinkedList<String>&, Stack<String>);
//find the top 3 routes based on the Vector of Paths given, the String message Queue (to be displayed), the flag, the cost Queue(to be displayed), the time Queue(to be displayed), and the vector of flight objects
void findTopRoutes(Vector< Stack<String> >, Queue<String>&, String, Queue<double>&, Queue<int>&, Vector<Flight>);


//A macro used in main to determine if you want to run
//the tests or not. If you don't want to run your tests,
//change true to false in the line below.
#define TEST false



/*
* runCatchTests will cause Catch to go ahead and
* run your tests (that are contained in the tests.cpp file.
* to do that, it needs access to the command line
* args - argc and argv. It returns an integer that
* ultimately gets passed back up to the operating system.
* See the if statement at the top of main for
* a better overview.
*/



int runCatchTests(int argc, char* const argv[])
{
    //This line of code causes the Catch library to
    //run the tests in the project.
    return Catch::Session().run(argc, argv);
}

int main( int argc, char* const argv[] )
{


    //If the TEST macro is defined to be true,
    //runCatchTests will be called and immediately
    //return causing the program to terminate. Change TEST
    //to false in the macro def at the top of this file
    //to skip tests and run the rest of your code.
    if (TEST)
    {
        return runCatchTests(argc, argv);
    }


//------------------------------------------------BEGIN MAIN HERE---------------------------------------------------------

/*
     Hierarchy for how this program will work:
     Section 1. Open Flight Data File
        A. Create a vector of flight paths
        B. Create a new flight object for each line
            i. Add corresponding data between pipes to the flight object (city 1, city 2, cost, time)
     Section 2. Create a vector of Linked Lists as the Adjacency List
        A. First element of eahc Linked List will be the Unique City
        B. For Each Unique City, add a node for cities that can be flown to from there
     Section 3. Open Paths File
        A. Exhaustively Search Adjacency List looking for paths
        B. Print the best 3 (or 2, 1, or 0) routes in order based on either cost or time
     Section 4. Close All Files That were opened

*/


    //Variables:
    //Vector of Flight Paths
    Vector<Flight> flights;
    //ifstrem object for reading flight data
    ifstream flightData;
    //open the Flight Data File
    flightData.open(argv[1]);
    //buffer for reading flight data
    //the buffer is 187 to account for the world's longest city name which is:
    //Krung Thep Mahanakhon Amon Rattanakosin Mahinthara Yuthaya Mahadilok Phop Noppharat Ratchathani Burirom Udomratchaniwet Mahasathan Amon Piman Awatan Sathit Sakkathattiya Witsanukam Prasit
    //this is an alternate name for Bankok
    char lineOfFlights[187];
    //number of paths
    int numFlights = 0;
    //workable String objects
    String word;
    //adjacency list
    Vector<LinkedList<String> > adjList;
    //ifstream object for reading the paths file
    ifstream paths;
    //open the path file
    paths.open(argv[2]);
    //buffer for reading paths
    char lineOfPaths[187];
    //number of requests
    int requests;
    //Strings for beginning city, ending city, and flag for cost or time
    String beg;
    String end;
    String flag;
    //ofstream object for output
    ofstream routes;
    //open the output file
    routes.open(argv[3]);



//------------------------------------------SECTION 1--------------------------------------------

    //make sure the file could be opened
    if (flightData.is_open() == false)
    {
        cout<<"The Flight Data File could not be read"<<endl;
        return 0;
    }

    //read the first line of the flight data file to get size
    flightData.getline(lineOfFlights, 187);
    //set the size
    numFlights = atoi(lineOfFlights);


    //loop through the file and put the flight paths into a vector
    for (int i = 0; i < numFlights; i ++)
    {
        //get the first city:
        flightData.getline(lineOfFlights, 187, '|');
        //make a string of this city
        word = lineOfFlights;
        //create a flight object
        Flight f;
        //set the first city
        f.setCity1(word);
        //get the second city:
        flightData.getline(lineOfFlights, 187, '|');
        //make a string of this city
        word = lineOfFlights;
        //set the second city
        f.setCity2(word);
        //get the cost:
        flightData.getline(lineOfFlights, 187, '|');
        //make a string of the cost
        word = lineOfFlights;
        //make an int of the cost
        double dollars = atoi(word.c_str());
        //set the cost
        f.setCost(dollars);
        //get the time:
        flightData.getline(lineOfFlights,187);
        //make a string of the time
        word = lineOfFlights;
        //make an int of the time
        int num = atoi(word.c_str());
        //set the time
        f.setTime(num);
        //add this flight to the vector
        flights.add(f);
    }

//--------------------------------------------SECTION 2-------------------------------------

    //add unique cities to a vector of linked lists
    for (int i = 0; i < flights.size(); i ++)
    {
        //check to see if the first city is in the vector
        LinkedList<String> city1(flights[i].getCity1());
        if (!(adjList.isAnElement(city1)))
        {
            //add this city if it is unique
            adjList.add(city1);
        }
        //check the second city
        LinkedList<String> city2(flights[i].getCity2());
        if (!(adjList.isAnElement(city2)))
        {
            //add if unique
            adjList.add(city2);
        }
    }

    //add adjacent cities to the linked list element head
    for (int i = 0; i < adjList.size(); i ++)
    {
        //iterate through the flights
        for (int j = 0; j < flights.size(); j ++)
        {
            //if the first city is the starting city...
            if (flights[j].getCity1() == adjList[i][0])
            {
                //...then add the second city to the Linked List of adjacent cities
                adjList[i].addToBack(flights[j].getCity2());
            }
            //if the second city is the starting city...
            else if (flights[j].getCity2() == adjList[i][0])
            {
                //...then add the first city to the Linked List of adjacent cities
                adjList[i].addToBack(flights[j].getCity1());
            }
        }
    }


//---------------------------------------------SECTION 3--------------------------------------


    //open file
    if (paths.is_open() == false)
    {
        cout<<"File could not be read"<<endl;
        return 0;
    }

    //get the first line
    paths.getline(lineOfPaths, 80);
    //set the number of path requests
    requests = atoi(lineOfPaths);

    //loop through the adjacency list and add the
    for (int i = 0; i < requests; i ++)
    {
        //get the beginning city
        paths.getline(lineOfPaths,80, '|');
        //set the beginning city
        beg = lineOfPaths;
        //get the ending city
        paths.getline(lineOfPaths,80, '|');
        //set the ending city
        end = lineOfPaths;
        //get the flag
        paths.getline(lineOfPaths, 80);
        //set the flag
        flag = lineOfPaths;
        //vector of Stack of String objects for all paths
        Vector< Stack<String> > allPaths;
        findPath(allPaths,adjList, beg, end);

        //check the flag
        //if cost
        if (flag == "C")
        {
            //finish the flag spelling for Cost
            flag = flag + "ost";
        }
        //if time
        else if (flag == "T")
        {
            //finish the flag spelling for Time
            flag = flag + "ime";
        }
        //output the first line of output:
        routes<<"Flight "<<(i +1)<<": "<<beg<<", "<<end<<" ("<<flag<<")\n";

        //create variables that will be passed by reference:
        //String variable for the output
        Queue<String> flightPath;
        //double variable for the cost
        Queue<double> costs;
        //integer variable for the time
        Queue<int> times;

        //call the function for finding top 3(max) routes
        //the top 3(max) options will be in order for flightPath, cost, time
        //the data will be passed by reference
        findTopRoutes(allPaths, flightPath, flag, costs, times, flights);

        //check to see if no paths
        if (flightPath.peek() == "There is no route between these two cities.")
        {
            routes<<flightPath.dequeue()<<"\n\n";
        }
        //if there ARE routes
        else
        {
            //make a counter to number the paths
            int counter = 1;

            //loop through the most efficient routes
            while (flightPath.isEmpty() == false)
            {
                //output the data
                routes<<"Path "<<counter<<": "<<flightPath.dequeue()<<". Time: "<<times.dequeue()<<" Cost: "<<setprecision (2)<<fixed<<costs.dequeue()<<"\n";
                //update the counter
                counter++;
            }
            routes<<"\n";
        }

    }


//-----------------------------------------------SECTION 4---------------------------------------


    //close the 3 flight files
    flightData.close();
    paths.close();
    routes.close();


    return 0;
}


//-------------------------------END OF PROGRAM. BEGIN FUNCTION IMPLEMENTATION-------------------------

//custom functions implementation:
//get the index of a given origin city
int getIndex(Vector< LinkedList<String> > aList, String city)
{
    //loop through the vector
    for (int i = 0; i < aList.size(); i ++)
    {
        //check every first element
        if (aList[i].getFirst() == city)
        {
            //return the index
            return i;
        }
    }
}

//find all paths
void findPath(Vector< Stack<String> > &paths, Vector< LinkedList<String> > aList, String startingLocation, String finalDestination)
{
    //check to see if the two cities are the same
    if (!(startingLocation == finalDestination))
    {
    //create the stack
    Stack<String> onePath;
    //create a list of previously traveled to cities
    LinkedList<String> previouslyTraveled;
    //automatically at the starting city to previously traveled to
    previouslyTraveled.addToBack(startingLocation);
    //add the beginning city automatically to the stack
    onePath.push(startingLocation);

    //loop through until all the possibilities from the beginning city have been exhuasted
    for (int i = 1; i < aList[getIndex(aList, startingLocation)].size(); i ++)
    {
        //make a variable for the i'th element so the for loop can go to next iteration if this is reached
        String firstRowCity = aList[getIndex(aList, startingLocation)][i];
        //if the i'th city is the final destination
        if (firstRowCity == finalDestination)
        {
            //if this city is the destination, then add it to the stack and send off
            onePath.push(firstRowCity);
            paths.add(onePath);
            //pop off the last element
            onePath.pop();
        }
        //if the i'th city is NOT the final destination
        else
        {
            //go to this city and add it to the stack
            removeErroneousCities(previouslyTraveled, onePath);
            onePath.push(firstRowCity);
            //add to the previously traveled cities
            previouslyTraveled.addToBack(firstRowCity);
            //now check the next location from this city
            String nextCity = aList[getIndex(aList, firstRowCity)].getNext(firstRowCity);
            //make a copy of leftmost city
            String leftCity = firstRowCity;
            //make a pop variable:
            String popV = "";
            //loop through cities
            do
            {
                //check if this city is the destination AND there is a next city from here
                if (nextCity == finalDestination && aList[getIndex(aList, leftCity)].isNext(nextCity))
                {
                    //if yes, then add to stack and send off
                    onePath.push(nextCity);
                    paths.add(onePath);
                    //pop off final destination from stack for next iteration
                    //because the firstRow city was already compared to the final destination, this will not stop do-while from continuing
                    popV = onePath.pop();
                    //remove erroneous values from previously traveled
                    removeErroneousCities(previouslyTraveled, onePath);
                    //set the next city since it exists
                    nextCity = aList[getIndex(aList, leftCity)].getNext(nextCity);
                }
                //check if this city is the destination and there is NOT a next city from here
                else if (nextCity == finalDestination && !(aList[getIndex(aList, leftCity)].isNext(nextCity)))
                {
                    //if yes, then add to stack and send off
                    onePath.push(nextCity);
                    paths.add(onePath);
                    //pop off final destination from stack for next iteration
                    //because the firstRow city was already compared to the final destination, this will not stop do-while from continuing
                    popV = onePath.pop();
                    //remove erroneous values from previously traveled
                    removeErroneousCities(previouslyTraveled, onePath);
                    //since there is no next city, pop the left most city
                    popV = onePath.pop();
                    //update left city
                    leftCity = onePath.peek();
                    //update the next city
                    nextCity = popV;
                }
                //check if previously traveled AND there is a next element
                else if (previouslyTraveled.isAnElement(nextCity) && aList[getIndex(aList, leftCity)].isNext(nextCity))
                {
                        //if there is a next, go there
                        nextCity = aList[getIndex(aList, leftCity)].getNext(nextCity);
                }
                //if previously traveled and NO next element
                else if (previouslyTraveled.isAnElement(nextCity) && !(aList[getIndex(aList, leftCity)].isNext(nextCity)))
                {
                        //update the list of previously traveled to cities
                        removeErroneousCities(previouslyTraveled, onePath);
                        //since there is no next city, pop the left most city
                        popV = onePath.pop();
                        //update left city
                        leftCity = onePath.peek();
                        //update the next city
                        nextCity = popV;
                }
                //if completely new city
                else
                {
                    //go to this new city
                    leftCity = nextCity;
                    //push to stack
                    onePath.push(nextCity);
                    //add to previously traveled
                    previouslyTraveled.addToBack(nextCity);
                    //update next
                    nextCity = aList[getIndex(aList, leftCity)].getNext(nextCity);
                    //update the list of previously traveled to cities
                    removeErroneousCities(previouslyTraveled, onePath);
                }
                //removeErroneousCities(previouslyTraveled, onePath);
            }while (!(popV == firstRowCity));
        }

    }
    //if there is no path found
    if (paths.size() == 0)
    {
        //pop the paths that were on the stack before the loop ended
        while (!onePath.isEmpty())
        {
            //pop off while the stack is not empty
            onePath.pop();
        }
        //push on the error message
        onePath.push("There is no route between these two cities.");
        //add this stack to the vector
        paths.add(onePath);
    }

    }
    //if the starting city == the destination city
    else
    {
        //create a Stack of Strings that will just hold the error message
        Stack<String> noRoute;
        //push the error message
        noRoute.push("There is no route between these two cities.");
        //add this stack to the vector
        paths.add(noRoute);
    }

}

//remove erroneous cities from previously traveled
void removeErroneousCities(LinkedList<String> &allCities, Stack<String> path)
{
    //make a temp linked list
    LinkedList<String> temp;

    //loop through the path stack
    while (!path.isEmpty())
    {
        //add the pop to the temp list
        temp.addToFront(path.pop());
    }

    //loop through the given list and remove the erroneous values
    for (int i = 0; i < allCities.size(); i ++)
    {
        //if this item is not in the given paths
        if (!(temp.isAnElement(allCities[i])))
        {
            //remove it
            allCities.remove(i);
            //decrement counter to account for deletion
            i--;
        }
    }
}

//find the top 3 routes
void findTopRoutes(Vector< Stack<String> >paths, Queue<String> &message, String order, Queue<double> &money, Queue<int> &minutes, Vector<Flight> options)
{
    //create temporary variables for totalling up numbers during iterations
    double cost = 0.0;
    int time = 0;

    //create a workable string object
    String workable = "";

    //create vectors of doubles, ints, and strings where the index of these will be key for later
    Vector<double> dollars;
    Vector<int> durations;
    Vector<String> distances;

    //make a current string variable for each city
    String curr = "";
    //make a next string variable for the next one
    String next = "";

    //only do calculations if there are actually paths
    if (!(paths[0].peek() == "There is no route between these two cities."))
    {
        //check to see if only one path
        if (paths.size() == 1)
        {
            //get first element
            curr = paths[0].pop();
            //update the string
            workable = curr;
            //make a counter to check for direct flights
            int direct = 0;

            //calculate the cost and time
            while (paths[0].isEmpty() == false)
            {
                //update next
                next =  paths[0].peek();

                //loop through the flights to see which one has both next and curr and then total up the cost and time
                for (int i = 0; i < options.size(); i ++)
                {
                    //check for when next and curr are on the same flight
                    if (((options[i].getCity1() == curr) && (options[i].getCity2() == next)) || ((options[i].getCity2() == curr) && (options[i].getCity1() == next)))
                    {
                        //total up cost and time
                        cost = cost + options[i].getCost();
                        time = time + options[i].getTime();
                        //since there will only ever be one flight between the two cities, break out of the for loop
                        break;
                    }
                }
                //update current
                curr = paths[0].pop();
                //update the direct flight count checker
                direct++;
                //check to see if only one other city has been traveled
                if (paths[0].isEmpty() && direct == 1 )
                {
                    //if only one city has been popped and the paths are now empty, this means direct flight
                    workable = curr + " -> " + workable;
                    String directFlight = "(This is a direct Flight!) ";
                    workable = directFlight + workable;
                }
                //if not a direct flight
                else
                {
                    //update the string
                    workable = curr + " -> " + workable;
                }
            }
            //add the elements to their respective queues
            money.enqueue(cost);
            minutes.enqueue(time);
            message.enqueue(workable);
        }
        //if more than one possible flight path, look for best 3 (max) based on the flag that was sent
        else if (paths.size() > 1)
        {
            //loop through the paths
            for (int i = 0; i < paths.size(); i ++)
            {
                //get first element
                curr = paths[i].pop();
                //update the string
                workable = curr;
                //make a counter to check for direct flights
                int direct = 0;

                //calculate the cost and time
                while (paths[i].isEmpty() == false)
                {
                    //update next
                    next =  paths[i].peek();

                    //loop through the flights to see which one has both next and curr and then total up the cost and time
                    for (int j = 0; j < options.size(); j ++)
                    {
                        //check for when next and curr are on the same flight
                        if (((options[j].getCity1() == curr) && (options[j].getCity2() == next)) || ((options[j].getCity2() == curr) && (options[j].getCity1() == next)))
                        {
                            //total up cost and time
                            cost = cost + options[j].getCost();
                            time = time + options[j].getTime();
                            //since there will only ever be one flight between the two cities, break out of the for loop
                            break;
                        }
                    }

                    //update current
                    curr = paths[i].pop();
                    //update the direct flight count checker
                    direct++;
                    //check to see if only one other city has been traveled
                    if (paths[i].isEmpty() && direct == 1 )
                    {
                        //if only one city has been popped and the paths are now empty, this means direct flight
                        workable = curr + " -> " + workable;
                        String directFlight = "(This is a direct Flight!) ";
                        workable = directFlight + workable;
                    }
                    //if not a direct flight
                    else
                    {
                        //update the string
                        workable = curr + " -> " + workable;
                    }
                }
                //add the elements to their respective vectors. note that each vector with each set of information has the same index. this will be key when ordering
                dollars.add(cost);
                durations.add(time);
                distances.add(workable);

                //reset variables
                cost = 0;
                time = 0;
            }

            //now that all the data has been collected, find the best 3 (max) routes based on the given flag
            //make a counter to only record up to 3 routes
            int maxThree = 0;

            //if cost is the flag
            if (order == "Cost")
            {
                //make a sorted copy of the cost vector
                Vector<double> copy = dollars;
                copy.sort();


                //loop through the sorted vector
                for (int i = 0; i < copy.size(); i ++)
                {
                    //make a copy of the i'th element
                    double min = copy[i];
                    //find the index that this value is at in the dollars vector
                    for (int j = 0; j < dollars.size(); j ++)
                    {
                        //check to see if min equals the value in dollars at index j and check if the queue is empty
                        if (min == dollars[j] && money.isEmpty() == true)
                        {
                            //if queue is empty, then add the corresponding values at the the right indexes
                            money.enqueue(dollars[j]);
                            minutes.enqueue(durations[j]);
                            message.enqueue(distances[j]);
                            maxThree++;
                        }
                        //make sure that this value hasn't already been added yet
                        else if (min == dollars[j] && money.isEmpty() == false && min != money.peek() && maxThree < 3)
                        {
                            //if this element has not been added yet, then add it
                            money.enqueue(dollars[j]);
                            minutes.enqueue(durations[j]);
                            message.enqueue(distances[j]);
                            maxThree++;
                        }
                    }

                }

            }
            //if time is the flag
            else if (order == "Time")
            {
                //make a sorted copy of the time vector
                Vector<int> copy = durations;
                copy.sort();


                //loop through the sorted vector
                for (int i = 0; i < copy.size(); i ++)
                {
                    //make a copy of the i'th element
                    int min = copy[i];
                    //find the index that this value is at in the dollars vector
                    for (int j = 0; j < durations.size(); j ++)
                    {
                        //check to see if min equals the value in dollars at index j and check if the queue is empty
                        if (min == durations[j] && minutes.isEmpty() == true)
                        {
                            //if queue is empty, then add the corresponding values at the the right indexes
                            money.enqueue(dollars[j]);
                            minutes.enqueue(durations[j]);
                            message.enqueue(distances[j]);
                            maxThree++;
                        }
                        //make sure that this value hasn't already been added yet
                        else if (min == durations[j] && minutes.isEmpty() == false && min != minutes.peek() && maxThree < 3)
                        {
                            //if this element has not been added yet, then add it
                            money.enqueue(dollars[j]);
                            minutes.enqueue(durations[j]);
                            message.enqueue(distances[j]);
                            maxThree++;
                        }
                    }

                }
            }

        }
    }
    //if no paths
    else if (paths[0].peek() == "There is no route between these two cities.")
    {
        message.enqueue("There is no route between these two cities.");
    }

}

//----------------------------------------------------END OF FUNCTION IMPLEMENTATION------------------------------------
