#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"
using namespace std;

//1 case popL, popR
TEST_CASE("2"){
    Deque<int> deque;
    deque.pushR(1);
    REQUIRE( deque.popL() == 1);
    REQUIRE(deque.isEmpty());
    deque.pushR(1);
    REQUIRE( deque.popR() == 1);
    REQUIRE(deque.isEmpty());
    cout <<"222" << endl;
}
//base case push
TEST_CASE("3"){
    Deque<int> deque;
    deque.pushR(1);
    REQUIRE(deque.peekL()==1);
    REQUIRE(deque.peekR()==1);
    cout<< "333" <<endl;
}

TEST_CASE("4"){
    Deque<int> deque;
    deque.pushR(1);
    deque.pushR(2);
    deque.pushR(3);
    REQUIRE(deque.getk2()==3);

    REQUIRE(deque.peekL()==1);
    REQUIRE(deque.peekR()==3);

    REQUIRE(deque.popR()==3);
    REQUIRE(deque.getk2()==2);

    REQUIRE(deque.popL()==1);

    REQUIRE(deque.getk1()==0);
    REQUIRE(deque.getk2()==1);
}

TEST_CASE("5") {
    Deque<int> deque;
    deque.pushR(1);
    deque.pushR(2);
    deque.pushR(3);
    deque.pushR(4);
    deque.pushR(5);
    deque.pushR(6);

    REQUIRE(deque.popL()==1);
    REQUIRE(deque.popR()==6);
    REQUIRE(deque.popL()==2);

    REQUIRE(deque.getk1()==2);
    REQUIRE(deque.getk2()==3);

    deque.popL();
    REQUIRE(deque.getk1()==0);
    REQUIRE(deque.getk2()==2);
}

TEST_CASE("6") {
    Deque<int> deque;
    deque.pushR(1);
    deque.pushR(2);
    deque.pushR(3);
    deque.pushR(4);
    deque.pushR(5);
    deque.pushR(6);

    deque.popR();
    deque.popR();
    deque.popR();
    REQUIRE(deque.getk1()==0);
    REQUIRE(deque.getk2()==3);
}
TEST_CASE("7") {
    Deque<int> deque;
    deque.pushR(1);
    deque.pushR(2);
    deque.pushR(3);
    deque.pushR(4);
    deque.pushR(5);
    deque.pushR(6);

    deque.popL();
    deque.popL();
    deque.popL();
    REQUIRE(deque.getk1()==0);
    REQUIRE(deque.getk2()==3);
}

TEST_CASE("8") {
    Deque<int> deque;
    deque.pushR(1);
    deque.pushR(2);
    deque.pushR(3);
    deque.pushR(4);
    deque.pushR(5);
    deque.pushR(6);

    deque.popL(); //1
    deque.popR();//6
    REQUIRE(deque.getk1()==1);
    deque.popR();//5
    deque.popR();//4
    REQUIRE(deque.peekL()==2);
    REQUIRE(deque.peekR()==3);
    deque.popR();
    REQUIRE(deque.getk2()==1);
    REQUIRE(deque.getk1()==0);
}


//TEST_CASE("GIVEN queue::","[weight=1][part=stack]"){
//    Queue<int> intQueue;
//    intQueue.enqueue(1);
//    REQUIRE( intQueue.dequeue() == 1);
//}
//


TEST_CASE("GIVEN stack::add() and peek()","[weight=1][part=stack]"){
    Stack<int> intStack;
    intStack.add(1);
    REQUIRE( intStack.peek() == 1);
}

TEST_CASE("GIVEN stack::add,remove,add,peek ","[weight=1][part=stack]"){
    Stack<int> intStack;
    intStack.add(1);
    int i = intStack.remove();
    intStack.add(2);

    REQUIRE( intStack.peek() == 2);
    cout << "goooooo" <<endl;
}

TEST_CASE("GIVEN stack::basic functions","[weight=1][part=stack]"){
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}

TEST_CASE("GIVEN queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE(result == expected);
    cout << "kkkkkk" << endl;
}
