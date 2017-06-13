#LinkedLists, Stacks, Queues, and The Flight Planner!
Sprint 2 - CSE 2341 - Fall 2016

## Introduction
In Sprint 2, you will implement a LinkedList, a Stack, and a Queue in C++, and you will use the classes as part of a Flight Planner. You will use the classes you build for additional projects later in the semester, so it works in your favor to build a robust implementation of each class. For the classes you build, you will use the CATCH framework for unit-testing. The header file for the CATCH framework is included in this sprint folder.

## The LinkedList, Stack, and Queue Classes

### The LinkedList Class
The LinkedList class shall be an implementation of a doubly linked list.  A separate class to represent the node shall also be included.  Both classes should be templated so that a doubly linked list can support any kind of data payload.  Pay special attention to dynamic memory management and include method implementations consistent with Rule of 3.   

We provide an initial interface (.h header) for your LinkedList class. You may add, remove, or modify methods and private data members from the header as you see fit. Your LinkedList class must include some mechanism to allow other code (client code) to iterate over the list without exposing the underlying implementation.  What this means is that a programmer using your LinkedList class should be able to step through the sequence of elements contained within (minimally, from front of list to end of list) without concern for how such iterating is accomplished (you may consider implementing an entire iterator class, or something similar). 

### The Stack and Queue Classes
The Stack and Queue classes shall represent LIFO/FIFO data structures, respectively, and should include the standard methods associated with stacks and queues (push, pop, peek, enqueue, dequeue, and isEmpty). The Stack and Queue classes should be composed of a LinkedList object (i.e. a Stack object should have a LinkedList as a private data member).  You can think of the stack class and queue class as **adapting** the functionality of a LinkedList object to achive the interface neede for said classes.  We will provide an interface (.h header) for your Stack and Queue classes. You may add, remove, or modify methods and private data members from the header as you see fit. These two classes will be much simpler than the classes you've built so far.

### Dynamic Memory Management
Any class which manages dynamic memory (the LinkedList will) needs to include an overloaded assignment operator, a copy constructor, and a destructor. Omitting any of these functions could cause segmentation faults, memory leaks, and shallow copy-related problems.

### Testing Your Classes
It is expected that, along with your Stack, Queue, and LinkedList implementations, you include unit tests, run with the CATCH interface. This sprint handout includes a skeleton of a test.cpp file that you can use to build your tests for your classes.  Your test cases should convince a reasonable person (TA or Prof. Fontenot) that you've given a great deal of thought to edge cases and special scenarios.  Thinking about what these edge cases and special scenarios are is a great task to take on with a partner from the class.  Don't write code together.  Instead, find a white board and talk through all the ways to "break" a typical linked list, stack or queue. 


## The Flight Planner

### Introduction
In this project, you will determine all possible flight plans for a person wishing to travel between two different cities serviced by an airline (assuming a path exists). You will also calculate the total cost incurred for all parts of the trip. For this project, you will use information from two different input files in order to calculate the trip plan and total cost.

1. **Origination and Destination Data** – This file will contain a sequence of city pairs representing different legs of flights that can be considered in preparing a flight plan. For each leg, the file will also contain a dollar cost for that leg and a time to travel. For each pair in the file, you can assume that it is possible to fly both directions.

2. **Requested Flights** – This file will contain a sequence of origin/destination city pairs. For each pair, your program will determine if the flight is or is not possible. If it is possible, it will output to a file the flight plan with the total cost for the flight. If it is not possible, then a suitable message will be written to the output file.

The names of the two input files as well as the output file will be provided via command line arguments.

### Flight Data
Consider a flight from Dallas to Paris. It’s possible that there is a direct flight, or it may be the case that a stop must be made in Chicago. One stop in Chicago would mean the flight would have two legs. We can think of the complete set of flights between different cities serviced by our airline as an undirected graph. An example of an undirected graph is given in Figure 1.

![alt text](https://raw.githubusercontent.com/MarkFontenot/16S-CSE2341-Projects/proj05/ProgAssign05/figure01.png "Figure 1")
Figure 1

In this example, a line from one city to another indicates a flight path both ways between the cities. The price and flight time is the same for both directions. If we wanted to travel from El Paso to Chicago, we would have to pass through Detroit. This would be a trip with two legs. It is possible that there might not be a path from one city to another city.  In this case, you’d print an error message indicating such.

In forming a flight plan from a set of flight legs, one must consider the possibility of cycles. In Figure 1, notice there is a cycle involving Chicago, Fresno, and Greensboro. In a flight plan from city X to city Y, a particular city should appear no more than one time.

The input file for flight data will represent a sequence of origin/destination city pairs with a cost of that flight. The first line of the input file will contain an integer which indicates the total number of origin/destination pairs contained in the file.  

### Sample Data
#### Flight Data
Here is an example of a flight data input file (it is not one that goes with Figure 1):
```
4
Dallas|Austin|98|47
Austin|Houston|95|39
Dallas|Houston|101|51
Austin|Chicago|144|192
```

The first line of the file will contain an integer indicating how many rows of data will be in the file.  Each subsequent row will contain two city names, the cost of the flight, and the number of minutes of the flight.  Each field will be separated with a pipe (shift-\ on most keyboards).

#### Requested Flight Plans
A sample input file for requested flight plans is shown below.  The first line will contain an integer indicating the number of flight plans requested.  The subsequent lines will contain a pipe-delimited list of city pairs with a trailing character to indicate sorting the output of flights by time (T) or cost (C).  Your solution will find all flight paths between these two cities (if any exists) and calculate the total cost of the flights and the total time in the air.   

```
2
Dallas|Houston|T
Chicago|Dallas|C
```

#### Output File
For each flight in the Requested Flight Plans file, your program will print the three most efficient flight plans available based on whether the request was to order by time or cost.  If there are fewer than three possible plans, output all of the possible plans.  If no flight plan can be created, then an error message should be output. If there is a tie between two flight plans on the sorting condition (time or cost), then the order of those paths that tie is inconsequential.  Here is an example:

```
Flight 1: Dallas, Houston (Time)
Path 1: Dallas -> Houston. Time: 51 Cost: 101.00
Path 2: Dallas -> Austin -> Houston. Time: 86 Cost: 193.00

Flight 2: Chicago, Dallas (Cost)
Path 1: Chicago -> Austin -> Dallas. Time: 237 Cost: 242.00
Path 2: Chicago -> Austin -> Houston -> Dallas. Time: 282 Cost: 340.00
```

### Implementation Details and Requirements
In order to store the structure representing flights serviced by the company, you will implement a simple adjacency list data structure. Essentially, it will be a container of linked lists (i.e. a linked list of linked lists, or a vector of linked lists). There will be one linked list for every distinct city. Each list will contain the cities (and other needed info) that can be reached from this city. Figure 2 is an example representation of an adjacency list for the graph in Figure 1.

![alt text](https://raw.githubusercontent.com/MarkFontenot/16S-CSE2341-Projects/proj05/ProgAssign05/figure02.png "Figure 1") Figure 2

The larger squares on the left represent the container of cities (with one node for each city). The list to which each node is pointing represents a city from which you can get to from the parent node. For example, from city A, it is possible to fly to cities B and D.

To solve this problem, you’ll need to implement an exhaustive search of all possible flights originating from a particular city. To achieve this, you’ll implement an iterative backtracking algorithm (using a stack). As you are calculating the flight path, you will use the stack to “remember” where you are in the search. The stack will also be used in the event that you've gone down a path that does not lead to the destination city. This algorithm method will be discussed in lecture, and you are encouraged to do some of your own research.  See https://en.wikipedia.org/wiki/Backtracking as one source of information.

For this project, you may NOT use any of the STL container classes or associated algorithms.  You MAY use any classes which you've built for previous sprints or the ones built for this sprint. 

Your implementation should be object-oriented in both design and implementation.  Minimize the amount of code you have in your main method.  Note that implementing a single class in which you have multiple methods does not make your solution object oriented in design.

### Executing Your Program
The final version of your program will be run from the command line with the following arguments:
```
./flightPlan <FlightDataFile> <PathsToCalculateFile> <OutputFile>

```

### What to Submit

By Monday, Sept 26 @ 6am, you should have pushed the following to Github and opened a pull request (following the protocol from Sprint 0):
*  LinkedList class TDD test source code
*  Stack & Queue class TDD test source code
*  Completed LinkedList, Stack, & Queue classes that pass all of your tests

During labs the week of Oct 3:
*  Check-ins with your TAs will happen during lab time
*  You should have begun work on your FlightPlanner by the time this check-in occurs

By Wednesday, Oct 12 @ 6am, you should have pushed the following to Github and opened a pull request (following the protocol from Sprint 0):
*  LinkedList and Stack/Queue TDD files
*  Completed LinkedList and Stack/Queue classes
*  Completed FlightPlanner project source
*  qmake .pro file from QtCreator

All code submitted should :
*  be well formatted and documented
*  follow all best practices covered in lecture and lab
*  follow good design principles for object oriented programming


## Submission
You must push your work to GitHub by the due date. Your git repository must contain all of your code, design documents, and test cases. You must open a pull request from a feature branch into the master branch. Do not close or merge your pull request.

## Grading
Your project will be graded by one of the TAs for the course.  They've all taken the course, performed well, and understand the expectations of Professor Fontenot.  

|Outcome                  		 	| Points | Points Earned |
|:------------------------			|:----------:|---------------|
|Design of LinkedList Class      			| 20        |               |
|Design of Stack/Queue Classes      			| 20        |               |
|LinkedList Class Tests    			| 30        |               |
|Stack/Queue Class Tests     			| 30        |               |
|Design of FlightPlanner   			| 30        |               |
|Source Code Quality    			| 30        |               |
|FlightPlanner Functionality     			| 40        |               |

**Please note that if any memory leaks exist in any of your classes, you will lose up to 30 points per data structure**
