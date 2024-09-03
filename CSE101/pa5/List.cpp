//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 5
// List.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include "List.h"
#include <string>
#include <cassert>
#include <stdexcept>

#define VAL -75

// Class Constructors & Destructors ---------------------------------------------------------------------

// Create new Node in the empty state
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Creates new List in the empty state.
List::List() {
    num_elements = 0;
    pos_cursor = 0;
    frontDummy = new Node(VAL);
    backDummy = new Node(VAL);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
}

// Copy constructor.
List::List(const List& L) {
    // make this an empty list
    num_elements = 0;
    pos_cursor = 0;
    frontDummy = new Node(VAL);
    backDummy = new Node(VAL);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    //load elements of L into this list
    Node *F = L.frontDummy->next;
    while ((F != L.backDummy)) { //&& (B != VAL)) {
        this->insertBefore(F->data);
        F = F->next;
    }
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}
// Access functions -------------------------------------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (!(num_elements > 0)) { // pre-condition
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (!(num_elements > 0)) { // pre-condition
        throw std::length_error("List back(): empty List");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) { // pre-conditions
        throw std::range_error("List peekNext(): cursor not in range");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor <= 0) { // pre-conditions
        throw std::range_error("List peekPrev(): cursor not in range");
    }
    return beforeCursor->data;
}


// Manipulation procedures ------------------------------------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
    pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.·
// pre: position()<length()·
ListElement List::moveNext() {
    if (pos_cursor > num_elements) { // pre_conditions
        throw std::range_error("List moveNext(): cursor not in range");
    }
    pos_cursor ++;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.·
// pre: position()>0
ListElement List::movePrev() {
    if (pos_cursor < 0) { // pre_conditions
        throw std::range_error("List movePrev(): cursor not in range");
    }
    pos_cursor --;
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *s = new Node(x);
    num_elements ++;
    s->next = afterCursor;
    s->prev = beforeCursor;
    beforeCursor->next = s;
    afterCursor->prev = s;
    afterCursor = s;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    pos_cursor ++;
    Node *j = new Node(x);
    j->prev = beforeCursor;
    j->next = afterCursor;
    beforeCursor->next = j;
    afterCursor->prev = j;
    beforeCursor = j;
    num_elements ++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (pos_cursor > num_elements) { // pre_conditions
        throw std::range_error("List setAfter(): cursor out of range");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (pos_cursor < 0) { // pre-conditions
        throw std::range_error("List setBefore(): cursor out of range");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    Node *temp = nullptr;
    if (pos_cursor >= num_elements) { // pre-conditions
        throw std::range_error("List eraseAfter(): cursor out of range");
    }
    temp = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements --;
    delete temp;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    Node *temp = nullptr;
    if (pos_cursor < 0) { // pre-conditions
        throw std::range_error("List erasebefore(): cursor out of range");
    }
    temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements --;
    pos_cursor --;
    delete temp;
}

// Other Functions --------------------------------------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in·
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then·
// returns the final cursor position. If x is not found, places the cursor·
// at position length(), and returns -1.·
int List::findNext(ListElement x) {
    while (afterCursor->next != backDummy) {
        if (afterCursor->data == x) {
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    moveBack();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in·
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor·
// at position 0, and returns -1.·
int List::findPrev(ListElement x) {
    while (beforeCursor->prev != frontDummy) {
        if (beforeCursor->data == x) {
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    moveFront();
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost·
// occurrance of each element, and removing all other occurances. The cursor·
// is not moved with respect to the retained elements, i.e. it lies between·
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // parse theough the list, check every element for duplicates against the first 
    // delete the duplicates as they are discovered
    // then move on to the second element
    // check every remaining element after the 2nd element for duplicates
    // keep looping and deleting until all the elements have been checked
    Node *e = nullptr;
    Node *i = nullptr;
    Node *temp = nullptr;
    for (e = frontDummy->next; e != backDummy; e = e->next) {
        i = e->next;
        while(i != backDummy) {
            if (e->data == i->data) {
                if (i == afterCursor) {
                    eraseAfter();
                }
                else if (i == beforeCursor) {
                    eraseBefore();
                }
                else {
                    temp = i;
                    i->prev->next = i->next;
                    i->next->prev = i->prev;
                    temp = i;
                    i = i->next;
                    delete temp;
                    num_elements --;
                    //pos_cursor --; // how do you know that your node is before the cursor instead of after.
                    continue;
                }
            }
            i = i->next;
        }
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    Node *n = frontDummy->next;
    Node *m = L.frontDummy->next;
    List merge;
    while (n != this->backDummy) {
        merge.insertBefore(n->data);
        n = n->next;
    }
    while (m != L.backDummy) {
        merge.insertBefore(m->data);
        m = m->next;
    }
    merge.moveFront();
    return merge;
}

// to_string()
// Returns a string representation of this List consisting of a comma·
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node *n = nullptr;
    std::string s = "(";
    for (n = frontDummy->next; n != backDummy; n = n->next) {
        if (n == backDummy->prev) {
            s += std::to_string(n->data);
        }
        else {
            s += std::to_string(n->data) + ", ";
        }
    }
    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    Node *n = nullptr;
    Node *m = nullptr;
    if (num_elements != R.num_elements) {
        return false;
    }
    n = frontDummy->next;
    m = R.frontDummy->next;
    while ((n != backDummy) && (m != R.backDummy)) {
        if (n->data != m->data) {
            return false;
        }
        n = n->next;
        m = m->next;
    }
    if ((n != backDummy) && (m != R.backDummy)) {
        return false;
    }
    return true;
}

// Overriden Operators -----------------------------------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The·
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
   if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;
      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
   }
   // return this with the new data installed
   return *this;
   // the copy, if there is one, is deleted upon return
}
