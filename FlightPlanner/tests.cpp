
/*
* Assignment: Sprint 2 - Part 2
* Description: This Program is a flight planner
* Date: 10-12-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linkedlist.h"
#include "queue.h"
#include "stack.h"
#include "DSString.h"
#include "vector.h"



TEST_CASE("LinkedList class", "[LinkedList]"){



    SECTION("Destructor"){
        LinkedList<int> a;
        a.addToBack(5);
        a.addToBack(10);
        a.addToBack(20);
    }


    SECTION("Default constructor"){
        LinkedList<int> dIntTest;
        REQUIRE(dIntTest.size() == 0);
        REQUIRE(dIntTest.isEmpty() == true);
        REQUIRE(dIntTest.remove(4) == 0);
        LinkedList<String> dStrTest;
        REQUIRE(dStrTest.size() == 0);
        REQUIRE(dStrTest.isEmpty() == true);
        REQUIRE(dStrTest.remove(555) == "");
    }

    SECTION("Constructor with head"){
        LinkedList<int> hIntTest(4);
        REQUIRE(hIntTest.size() == 1);
        REQUIRE(hIntTest.isEmpty() == false);
        REQUIRE(hIntTest[0] == 4);
        REQUIRE(hIntTest.get(0) == 4);
        REQUIRE(hIntTest.remove(0) == 4);
        LinkedList<String> hStrTest("Hello");
        REQUIRE(hStrTest.size() == 1);
        REQUIRE(hStrTest.isEmpty() == false);
        REQUIRE(hStrTest[0] == "Hello");
        REQUIRE(hStrTest.get(0) == "Hello");
        REQUIRE(hStrTest.remove(0) == "Hello");

    }

    SECTION("Copy constructor"){
        LinkedList<int> ccIntTestRight;
        ccIntTestRight.addToBack(55);
        ccIntTestRight.addToBack(77);
        ccIntTestRight.addToBack(999);
        LinkedList<int> ccIntTestLeft (ccIntTestRight);
        REQUIRE(ccIntTestLeft[0] == ccIntTestRight[0]);
        REQUIRE(ccIntTestLeft[1] == ccIntTestRight[1]);
        REQUIRE(ccIntTestLeft[2] == ccIntTestRight[2]);
        REQUIRE(ccIntTestLeft.size() == ccIntTestRight.size());
        LinkedList<int> ccIntTestNoneRight;
        LinkedList<int> ccIntTestNoneLeft (ccIntTestNoneRight);
        REQUIRE(ccIntTestNoneLeft.size() == 0); //left size should be zero now
        LinkedList<int> ccIntTestOneRight;
        ccIntTestOneRight.addToBack(11);
        LinkedList<int> ccIntTestOneLeft (ccIntTestOneRight);
        REQUIRE(ccIntTestOneLeft.size() == 1); //left size should be 1 now
        REQUIRE(ccIntTestOneLeft[0] == 11); //make sure the value copied over
        LinkedList<int> ccIntTestTwoRight;
        ccIntTestTwoRight.addToBack(222);
        ccIntTestTwoRight.addToBack(444);
        LinkedList<int> ccIntTestTwoLeft (ccIntTestTwoRight);
        REQUIRE(ccIntTestTwoLeft.size() == 2); //make sure the size is 2
        REQUIRE(ccIntTestTwoLeft[0] == 222); //make sure first number carried over
        REQUIRE(ccIntTestTwoLeft[1] == 444); //make sure second number carried over
    }

    SECTION("add"){
        LinkedList<int> aIntTest;
        aIntTest.add(4, 0);
        REQUIRE(aIntTest[0] == 4);
        aIntTest.add(5, 1);
        aIntTest.add(6, 2);
        aIntTest.add(3, 0);
        REQUIRE(aIntTest[0] == 3);
        REQUIRE(aIntTest[1] == 4);
        REQUIRE(aIntTest[2] == 5);
        REQUIRE(aIntTest[3] == 6);
        REQUIRE(aIntTest.size() == 4);
        LinkedList<String> aStrTest;
        aStrTest.add("Hello", 0);
        aStrTest.add("I", 0);
        aStrTest.add("Say", 1);
        REQUIRE(aStrTest[0] == "I");
        REQUIRE(aStrTest[1] == "Say");
        REQUIRE(aStrTest[2] == "Hello");
        REQUIRE(aStrTest.size() == 3);

    }

    SECTION("addToFront"){
        LinkedList<int> fIntTest;
        fIntTest.addToFront(3);
        fIntTest.addToFront(2);
        fIntTest.addToFront(1);
        REQUIRE(fIntTest[0] == 1);
        REQUIRE(fIntTest[1] == 2);
        REQUIRE(fIntTest[2] == 3);
        REQUIRE(fIntTest.size() == 3);
        LinkedList<String> fStrTest;
        fStrTest.addToFront("Goodbye");
        fStrTest.addToFront("Say");
        fStrTest.addToFront("You");
        REQUIRE(fStrTest[0] == "You");
        REQUIRE(fStrTest[1] == "Say");
        REQUIRE(fStrTest[2] == "Goodbye");
        REQUIRE(fStrTest.size() == 3);
    }

    SECTION("addToBack"){
        LinkedList<int> bIntTest(11);
        bIntTest.addToBack(22);
        bIntTest.addToBack(33);
        REQUIRE(bIntTest[0] == 11);
        REQUIRE(bIntTest[1] == 22);
        REQUIRE(bIntTest[2] == 33);
        REQUIRE(bIntTest.size() == 3);
        LinkedList<String> bStrTest("Hello");
        bStrTest.addToBack("Goodbye");
        bStrTest.addToBack("Beatles");
        REQUIRE(bStrTest[0] == "Hello");
        REQUIRE(bStrTest[1] == "Goodbye");
        REQUIRE(bStrTest[2] == "Beatles");
        REQUIRE(bStrTest.size() == 3);
    }

    SECTION("get"){
        LinkedList<int> gIntTest;
        gIntTest.addToBack(0);
        gIntTest.addToBack(1);
        gIntTest.addToBack(10);
        gIntTest.addToBack(11);
        REQUIRE(gIntTest.get(0) == 0);
        REQUIRE(gIntTest.get(1) == 1);
        REQUIRE(gIntTest.get(2) == 10);
        REQUIRE(gIntTest.get(3) == 11);
    }

    SECTION("getFirst"){
        LinkedList<int> gfIntTest(5);
        gfIntTest.addToBack(6);
        REQUIRE(gfIntTest.getFirst() == 5);
        LinkedList<String> gfStrTest;
        gfStrTest.addToBack("hello");
        gfStrTest.addToBack("goodbye");
        REQUIRE(gfStrTest.getFirst() == "hello");
    }

    SECTION("getLast"){
        LinkedList<int> gLIntTest(5);
        gLIntTest.addToBack(6);
        REQUIRE(gLIntTest.getLast() == 6);
        LinkedList<String> gLStrTest;
        gLStrTest.addToBack("hello");
        gLStrTest.addToBack("goodbye");
        REQUIRE(gLStrTest.getLast() == "goodbye");
    }


    SECTION("size"){
        LinkedList<String> sStrTest;
        sStrTest.addToBack("abc");
        sStrTest.addToFront("xyz");
        REQUIRE(sStrTest.size() == 2);
        LinkedList<int> sIntTest(99);
        sIntTest.add(333, 0);
        sIntTest.add(22, 1);
        REQUIRE(sIntTest.size() == 3);

    }

    SECTION("isEmpty()")
    {
        LinkedList<int> eIntTest;
        REQUIRE(eIntTest.isEmpty() == true);
        LinkedList<String> eStrTest("helloGoodbye");
        eStrTest.remove(0);
        REQUIRE(eStrTest.isEmpty() == true);
    }

    SECTION("remove"){
        LinkedList<int> rIntTest(5);
        REQUIRE(rIntTest.remove(0) == 5);
        LinkedList<String> rStrTest;
        rStrTest.addToFront("42");
        rStrTest.addToBack("Blue");
        REQUIRE(rStrTest.remove(1) == "Blue");
        LinkedList<int> rInt2Test;
        rInt2Test.addToBack(33);
        rInt2Test.addToBack(44);
        REQUIRE(rInt2Test.remove(0) == 33);
        REQUIRE(rInt2Test.remove(0) == 44);
        LinkedList<int> rInt3Test (55);
        rInt3Test.addToBack(66);
        rInt3Test.addToBack(77);
        REQUIRE(rInt3Test.remove(0) == 55);
        REQUIRE(rInt3Test.remove(0) == 66);
        REQUIRE(rInt3Test.remove(0) == 77);
        REQUIRE(rInt3Test.isEmpty() == true);
        LinkedList<int> rInt4Test (88);
        rInt4Test.addToBack(99);
        rInt4Test.addToBack(111);
        REQUIRE(rInt4Test.remove(2) == 111);
        REQUIRE(rInt4Test.remove(1) == 99);
        REQUIRE(rInt4Test.remove(0) == 88);
        REQUIRE(rInt4Test.isEmpty() == true);
    }

    SECTION("removeFirst"){
        LinkedList<int> rfIntTest;
        REQUIRE(rfIntTest.removeFirst() == 0);
        REQUIRE(rfIntTest.isEmpty() == true);
        rfIntTest.addToBack(1);
        REQUIRE(rfIntTest.removeFirst() == 1);
        REQUIRE(rfIntTest.isEmpty() == true);
        rfIntTest.addToBack(2);
        rfIntTest.addToBack(3);
        REQUIRE(rfIntTest.removeFirst() == 2);
        REQUIRE(rfIntTest.removeFirst() == 3);
        REQUIRE(rfIntTest.isEmpty() == true);
        rfIntTest.addToBack(4);
        rfIntTest.addToBack(5);
        rfIntTest.addToBack(6);
        REQUIRE(rfIntTest.removeFirst() == 4);
        REQUIRE(rfIntTest.removeFirst() == 5);
        REQUIRE(rfIntTest.removeFirst() == 6);
        REQUIRE(rfIntTest.isEmpty() == true);
    }

    SECTION("removeLast"){
        LinkedList<int> rLIntTest;
        REQUIRE(rLIntTest.removeLast() == 0);
        REQUIRE(rLIntTest.isEmpty() == true);
        rLIntTest.addToBack(1);
        REQUIRE(rLIntTest.removeLast() == 1);
        REQUIRE(rLIntTest.isEmpty() == true);
        rLIntTest.addToBack(2);
        rLIntTest.addToBack(3);
        REQUIRE(rLIntTest.removeLast() == 3);
        REQUIRE(rLIntTest.removeLast() == 2);
        REQUIRE(rLIntTest.isEmpty() == true);
        rLIntTest.addToBack(4);
        rLIntTest.addToBack(5);
        rLIntTest.addToBack(6);
        REQUIRE(rLIntTest.removeLast() == 6);
        REQUIRE(rLIntTest.removeLast() == 5);
        REQUIRE(rLIntTest.removeLast() == 4);
        REQUIRE(rLIntTest.isEmpty() == true);
    }


    SECTION("[] operator"){
        LinkedList<int> ssIntTest(99);
        REQUIRE(ssIntTest[0] == 99);
        LinkedList<String> ssStrTest("dog");
        ssStrTest.addToBack("cat");
        REQUIRE(ssStrTest[0] == "dog");
        REQUIRE(ssStrTest[1] == "cat");
    }

    SECTION("assignment operator"){
        LinkedList<int> aoIntTestRight(100);
        aoIntTestRight.addToBack(200);
        aoIntTestRight.addToBack(300);
        LinkedList<int> aoIntTestLeft = aoIntTestRight;
        REQUIRE(aoIntTestLeft[0] == aoIntTestRight[0]);
        REQUIRE(aoIntTestLeft[1] == aoIntTestRight[1]);
        REQUIRE(aoIntTestLeft[2] == aoIntTestRight[2]);
        REQUIRE(aoIntTestLeft.size() == aoIntTestRight.size());
        LinkedList<String> aoStrTestRight("Twenty");
        aoStrTestRight.addToBack("One");
        aoStrTestRight.addToBack("Pilots");
        LinkedList<String> aoStrTestLeft;
        aoStrTestLeft = aoStrTestRight;
        REQUIRE(aoStrTestLeft[0] == aoStrTestRight[0]);
        REQUIRE(aoStrTestLeft[1] == aoStrTestRight[1]);
        REQUIRE(aoStrTestLeft[2] == aoStrTestRight[2]);
        REQUIRE(aoStrTestLeft.size() == aoStrTestRight.size());
    }



}


TEST_CASE("Stack class", "[stack]"){

    SECTION("Push"){
            Stack<String> coins;
            coins.push("nickel");
            coins.push("dime");
            coins.push("penny");
            REQUIRE(coins.peek() == "penny");
            REQUIRE(coins.pop() == "penny");
    }

    SECTION("Pop"){
            Stack<int> numbers;
            numbers.push(11);
            numbers.push(22);
            numbers.push(33);
            REQUIRE(numbers.pop() == 33);
            REQUIRE(numbers.pop() == 22);
            REQUIRE(numbers.pop() == 11);
    }

    SECTION("Peek"){
            Stack<String> classes;
            classes.push("math");
            classes.push("science");
            classes.push("history");
            classes.push("english");
            REQUIRE(classes.peek() == "english");
            REQUIRE(classes.pop() == "english");
            REQUIRE(classes.peek() == "history");
    }

    SECTION("isEmpty"){
            Stack<char> letters;
            letters.push('A');
            letters.push('B');
            letters.push('C');
            REQUIRE(letters.pop() == 'C');
            REQUIRE(letters.pop() == 'B');
            REQUIRE(letters.pop() == 'A');
            REQUIRE(letters.isEmpty() == true);
            Stack<int> nums;
            nums.push(5);
            REQUIRE(nums.isEmpty() == false);
    }

}

TEST_CASE("Queue class", "[queue]"){

    SECTION("Enqueue"){
            Queue<int> numbers;
            numbers.enqueue(3);
            numbers.enqueue(2);
            numbers.enqueue(1);
            REQUIRE(numbers.peek() == 1);
            REQUIRE(numbers.dequeue() == 3);
    }

    SECTION("Dequeue"){
            Queue<String> people;
            people.enqueue("Bob");
            people.enqueue("Dylan");
            people.enqueue("Mary");
            people.enqueue("Sue");
            REQUIRE(people.dequeue() == "Bob");
            REQUIRE(people.dequeue() == "Dylan");
            REQUIRE(people.dequeue() == "Mary");
            REQUIRE(people.dequeue() == "Sue");
    }

    SECTION("Peek"){
            Queue<String> bands;
            bands.enqueue("Coldplay");
            bands.enqueue("Twenty-One Pilots");
            bands.enqueue("Panic! At The Disco");
            REQUIRE(bands.peek() == "Panic! At The Disco");
            REQUIRE(bands.dequeue() == "Coldplay");
            REQUIRE(bands.peek() == "Panic! At The Disco");
    }

    SECTION("isEmpty"){
            Queue<int> values;
            values.enqueue(10);
            values.enqueue(20);
            values.enqueue(30);
            REQUIRE(values.isEmpty() == false);
            REQUIRE(values.dequeue() == 10);
            REQUIRE(values.dequeue() == 20);
            REQUIRE(values.dequeue() == 30);
            REQUIRE(values.isEmpty() == true);
    }

}

