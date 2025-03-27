/*
*James Huang, hhuan143
*2023 spring CSE101 PA#5
*List.cpp
*writes the functions of List.h
*/

#include<string>
#include<iostream>
#include<stdexcept>
#include<stdlib.h>
#include"List.h"

//private constructors
//node constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}
//class constructors and destructors

List::List(){
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L){
   // make this an empty List
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
   // if L is non-empty, load its elements into this L
	Node* temp = L.frontDummy->next;
	while(temp != L.backDummy){
		insertBefore(temp->data);
		temp = temp->next;
	}
   
}

List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if (num_elements <= 0){
		throw std::length_error("List: front(): empty list");
	}
	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if (num_elements <= 0){
		throw std::length_error("List: front(): empty list");
	}
	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return pos_cursor;	
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if (pos_cursor >= num_elements){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if (pos_cursor <= 0){
		throw std::range_error("List: peekNext(): cursor at front");
	}
	return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	Node * temp = frontDummy->next;
	Node *N = nullptr;

	while(temp != backDummy){
		N = temp->next;
		delete temp;
		temp = N;	
	}
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;	
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	beforeCursor = frontDummy; 
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if (pos_cursor > num_elements){
		throw std::range_error("List: moveNext(): cursor at back");
	}
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	pos_cursor++;
	return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if (pos_cursor <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor--;
	return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	N->next = afterCursor;
	N->prev = beforeCursor;
	afterCursor->prev = N;
	beforeCursor->next = N;
	afterCursor = N;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if (pos_cursor >= num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if (pos_cursor <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	}
	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if (pos_cursor >= num_elements){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
	Node* gone = afterCursor;

   afterCursor = gone->next;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;

	// afterCursor = afterCursor->next;
	// afterCursor->prev = beforeCursor;
	// beforeCursor->next = afterCursor;

   delete gone;
   num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if (pos_cursor <= 0){
		throw std::range_error("List: eraseAfter(): cursor at front");
	}
	Node* gone = beforeCursor;
   beforeCursor = gone->prev;
   afterCursor->prev = beforeCursor;
   beforeCursor->next = afterCursor;    
   delete gone;
   num_elements--;
   pos_cursor--;
}
// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	while(pos_cursor < num_elements){
		if(peekNext() == x){
			moveNext();
			return pos_cursor;
		}else{
			moveNext();
		}
	}
	moveBack();
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	while(pos_cursor > 0){
		if(peekPrev() == x){
			movePrev();
			return pos_cursor;
		}else{
			movePrev();
		}
	}
	moveFront();
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){	
	int ogpos = pos_cursor;
	int new_ogpos = pos_cursor;
	int n = 0;
	int m = 0;
	moveFront();
	while(pos_cursor < num_elements){
		moveNext();
		if (findNext(peekPrev()) != -1){
			// std::cout << "prev = " << peekPrev() << std::endl;
			eraseBefore();
			if (pos_cursor < new_ogpos){
				// std::cout << "pos_cursor = " << pos_cursor << std::endl;
				n++;
				new_ogpos--;
			}
		}else{
			m++;
		}
		moveFront();
		for (int i = 0; i < m; i++){
			moveNext();
		}
	}
	moveFront();
	// std::cout << "ogpos = " << ogpos << std::endl;
	// std::cout << "n = " << n << std::endl;
	for (int i = 0; i < (ogpos - n); i++){
		moveNext();
	}
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List newList;
	Node* temp1 = this->frontDummy->next;
	Node* temp2 = L.frontDummy->next;
	while(temp1 != this->backDummy){
		newList.insertBefore(temp1->data);
		temp1 = temp1->next;
	}
	while(temp2 != L.backDummy){
		newList.insertBefore(temp2->data);
		temp2 = temp2->next;
	}
	newList.moveFront();
	return newList;
}



// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	Node* N = frontDummy->next;
   std::string s = "(";
   while(N->next != backDummy){
      s += std::to_string(N->data)+", ";
      N = N->next;
   }
   s += std::to_string(N->data);
   s += ")";
   return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = (this->num_elements == R.num_elements);
   N = this->frontDummy->next;
   M = R.frontDummy->next;
   while(eq && N != this->backDummy){
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if(this != &L){
   	List temp = L;
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
   }
   return *this;
}

// List A = B


