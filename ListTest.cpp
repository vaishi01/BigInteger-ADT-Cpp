/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 6
 Due date - March 4th, 2024
 File name - ListTest.cpp
*/

#include "List.h"
#include <iostream>

void testBasicFunctionality() {
    List myList;

    std::cout << "Initial list state: Length = " << myList.length() << std::endl;

    myList.insertBefore(10);
    std::cout << "Inserted 10 before; front = " << myList.front() << ", back = " << myList.back() << ", length = " << myList.length() << std::endl;

    myList.insertAfter(20);
    std::cout << "Inserted 20 after; back = " << myList.back() << ", length = " << myList.length() << std::endl;

    myList.moveFront();
    std::cout << "Moved cursor to front; position = " << myList.position() << std::endl;

    myList.moveNext();
    std::cout << "Moved cursor to next; position = " << myList.position() << std::endl;

    std::cout << "Peeked prev: " << myList.peekPrev() << ", Peeked next: " << myList.peekNext() << std::endl;

    myList.eraseBefore();
    std::cout << "Erased before; length = " << myList.length() << ", front = " << myList.front() << std::endl;

    myList.clear();
    std::cout << "Cleared list; length = " << myList.length() << std::endl;

    myList.insertBefore(30);
    myList.insertBefore(40);
    myList.moveFront();
    myList.eraseAfter();
    std::cout << "Erased after; length = " << myList.length() << ", front = " << myList.front() << std::endl;

    List copyList(myList);
    std::cout << "Copied list; length = " << copyList.length() << ", front = " << copyList.front() << std::endl;

    List assignedList;
    assignedList = myList;
    std::cout << "Assigned list; length = " << assignedList.length() << ", front = " << assignedList.front() << std::endl;
}

int main() {
    testBasicFunctionality();
    std::cout << "All List class tests completed." << std::endl;
    return 0;
}

/*
Expected Output -
Initial list state: Length = 0
Inserted 10 before; front = 10, back = 10, length = 1
Inserted 20 after; back = 20, length = 2
Moved cursor to front; position = 0
Moved cursor to next; position = 1
Peeked prev: 10, Peeked next: 20
Erased before; length = 1, front = 20
Cleared list; length = 0
Erased after; length = 1, front = 40
Copied list; length = 1, front = 40
Assigned list; length = 1, front = 40
All List class tests completed.
*/