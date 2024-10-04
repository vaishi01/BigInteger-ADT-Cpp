/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 6
 Due date - March 4th, 2024
 File name - List.cpp
*/
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>


#define DUMMY 0

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

List::List() : frontDummy(new Node(0)), backDummy(new Node(0)), beforeCursor(frontDummy), afterCursor(backDummy), pos_cursor(0), num_elements(0) {
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    afterCursor = backDummy;
    beforeCursor = frontDummy;
}

List::List(const List& L) {
    // Initialize the list to an empty state
    frontDummy = new Node(DUMMY);
    backDummy = new Node(DUMMY);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // Copy elements from L
    Node* currentNode = L.frontDummy->next;
    while (currentNode != L.backDummy) {
        this->insertBefore(currentNode->data); 
        currentNode = currentNode->next;
    }

    this->moveFront();

    for (int i = 0; i < L.pos_cursor; ++i) {
        this->moveNext();
    }
}


List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (length() <= 0) throw std::length_error("List::front() called on an empty List");
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (length() <= 0) throw std::length_error("List::back() called on an empty List");
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (position() >= length()) throw std::range_error("List::peekNext() called at end of List");
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (position() <= 0) throw std::range_error("List::peekPrev() called at start of List");
    return beforeCursor->data;
}

void List::clear() {
    moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
}

void List::moveFront() const {
    this->beforeCursor = this->frontDummy;
    this->afterCursor = this->frontDummy->next;
    this->pos_cursor = 0;
}

void List::moveBack() const {
    this->beforeCursor = this->backDummy->prev;
    this->afterCursor = this->backDummy;
    this->pos_cursor = this->num_elements;
}

ListElement List::moveNext() const {
    if (afterCursor == backDummy) throw std::range_error("List::moveNext() called at end of List");
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() const {
    if (beforeCursor == frontDummy) throw std::range_error("List::movePrev() called at start of List");
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    afterCursor->prev = newNode;
    beforeCursor->next = newNode;
    afterCursor = newNode;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    beforeCursor = newNode;
    num_elements++;
    pos_cursor++;
}


void List::eraseAfter() {
    if (afterCursor == backDummy) 
        throw std::range_error("List::eraseAfter() called at end of List");
    Node* toDelete = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor ;
    afterCursor->prev = beforeCursor;
    num_elements--;
    delete toDelete;
}

void List::eraseBefore() {
    if (beforeCursor == frontDummy) 
        throw std::range_error("List::eraseBefore() called at start of List");
    Node* toDelete = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    pos_cursor--;
    delete toDelete;
}

int List::findNext(ListElement x) {
    Node* newNode = afterCursor;
    int steps = 1;
    while (newNode != backDummy) {
        if (newNode->data == x) {
            pos_cursor += steps;
            beforeCursor = newNode;
            afterCursor = newNode->next;
            return pos_cursor;
        }
        newNode = newNode->next;
        steps++;
    }
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor =afterCursor->prev;
    return -1;
}


int List::findPrev(ListElement x) {
    Node* newNode = beforeCursor; 
    int l = 1;  
    
    while (newNode != frontDummy) { 
        if (newNode->data == x) { 
            beforeCursor = newNode->prev; 
            afterCursor = newNode; 
            pos_cursor -= l; 
            return pos_cursor; 
        }
        newNode = newNode->prev; 
        l++; 
    }


    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
    pos_cursor = 0; 
    return -1; 
}


void List::cleanup() {
    Node* newNode = this->frontDummy->next; 
    int outter_pos = 0; 
    while (newNode != this->backDummy) { 
        int i = newNode->data; 
        Node* newNode2 = newNode->next; 
        int inner_pos = outter_pos + 1; 
        while (newNode2 != this->backDummy) { 
            int j = newNode2->data; 
            Node* before = newNode2->prev;
            Node* after = newNode2->next;
            Node* erase = newNode2; 
            newNode2 = after; 
            if (j == i) { 
                before->next = after; 
                after->prev = before;
                delete erase;
                this->num_elements--; 
                if (inner_pos <= this->pos_cursor) { 
                    this->pos_cursor--;
                }
            }
            inner_pos++; 
        }
        outter_pos++; 
        newNode = newNode->next; 
    }
   
    int pos = this->pos_cursor;
    this->moveFront(); 
    while (this->position() != pos) { 
        this->moveNext();
    }
}


void List::setAfter(ListElement x) {
    if (afterCursor == backDummy) throw std::range_error("List::setAfter() called at end of List");
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (beforeCursor == frontDummy) throw std::range_error("List::setBefore() called at start of List");
    beforeCursor->data = x;
}

List List::concat(const List& L) const {
    List newList;
    Node* newNode;

    newList.moveBack();

    for (newNode = this->frontDummy->next; newNode != this->backDummy; newNode = newNode->next) {
        newList.insertBefore(newNode->data); 
    }

    for (newNode = L.frontDummy->next; newNode != L.backDummy; newNode = newNode->next) {
        newList.insertBefore(newNode->data); 
    }

    newList.moveFront();

    return newList;
}

std::string List::to_string() const {
    std::string listStr = "(";
    Node* current = frontDummy->next;
    while (current != backDummy) {
        listStr += std::to_string(current->data);
        if (current->next != backDummy) {
            listStr += ", ";
        }
        current = current->next;
    }
    listStr += ")";
    return listStr;
}

bool List::equals(const List& R) const {
    if (this->num_elements != R.num_elements) return false;
    Node* newNode = this->frontDummy->next;
    Node* newNode2 = R.frontDummy->next;
    while (newNode != this->backDummy && newNode2 != R.backDummy) {
        if (newNode->data != newNode2->data) return false;
        newNode = newNode->next;
        newNode2 = newNode2->next;
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        List temp(L);
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}
