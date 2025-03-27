/*
*James Huang, hhuan143
*2023 spring CSE101 PA#7
*Dictionary.cpp
*cpp for ADT
*/

#include<string>
#include<iostream>
#include<stdexcept>
#include<stdlib.h>
#include"Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
	//set key to k, val to v, left & right & parent nodes to null pointers
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if (R != nil){
		inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if (R != nil){
		s += R->key + "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if (R != N){
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
	if (R != nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		remove(R->key);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if (R == nil || k == R->key){
		return R;
	}else if(k < R->key){
		return search(R->left, k);
	}else{
		return search(R->right, k);
	}
	
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
	Node* temp = R;
	if (temp != nil){
		while(temp->left != nil){
			temp = temp->left;
		}
	}
	return temp;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	Node* temp = R;
	if (temp != nil){
		while(temp->right != nil){
			temp = temp->right;
		}
	}
	return temp;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if (N == nil){
		return nil;
	}else if (N->right != nil){
		return findMin(N->right);
	}else{
		Node* temp = N->parent;
		while(temp != nil && N == temp->right){
			N = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if (N == nil){
		return nil;
	}else if (N->left != nil){
		return findMax(N->left);
	}else{
		Node* temp = N->parent;
		while(temp != nil && N == temp->left){
			N = temp;
			temp = temp->parent;
		}
		return temp; 
	}
}

// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	nil = new Node("abcdefghijkl", 999);
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("abcdefghijkl", 999);
	root = nil;
	current = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
	postOrderDelete(this->root);
	delete nil;
}

// // Access functions --------------------------------------------------------

// // size()
// // Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

// // contains()
// // Returns true if there exists a pair such that key==k, and returns false
// // otherwise.
bool Dictionary::contains(keyType k) const{
	Node* N = search(root, k);
	return (N != nil);
}

// // getValue()
// // Returns a reference to the value corresponding to key k.
// // Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
	Node* N = search(root, k);
	if (N == nil){
		throw std::logic_error("Dictionary: getValue(): key \""+k+"\" does not exist");
	}
	return N->val;
}
// // hasCurrent()
// // Returns true if the current iterator is defined, and returns false 
// // otherwise.
bool Dictionary::hasCurrent() const{
	return (current != nil);
}

// // currentKey()
// // Returns the current key.
// // Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
	if (this->hasCurrent() == false){
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->key;
}

// // currentVal()
// // Returns a reference to the current value.
// // Pre: hasCurrent()
valType& Dictionary::currentVal() const{
	if (this->hasCurrent() == false){
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->val;
}

// // Manipulation procedures -------------------------------------------------

// // clear()
// // Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	postOrderDelete(root);
	root = nil;
	current = nil;
	num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node* tempR = root;
	Node* tempP = nil;
	while (tempR != nil){
		tempP = tempR;
		if (k < tempR->key){
			tempR = tempR->left;
		}else if (k > tempR->key){
			tempR = tempR->right;
		}else{
			//setValue(tempR->key, tempR->val);
			tempR->val = v;
			return;
		}
	}
	Node* tempN = new Node(k, v);
	if (tempP == nil){
		tempN->left = nil;
		tempN->right = nil;
		tempN->parent = nil;
		root = tempN;
	}else if (k < tempP->key){
		tempP->left = tempN;
		tempN->parent = tempP;
		tempN->left = nil;
		tempN->right = nil;
	}else{
		tempP->right = tempN;
		tempN->parent = tempP;
		tempN->right = nil;
		tempN->left = nil;
	}
	num_pairs++;

}

//helper for remove
void Dictionary::transplant(Node* u, Node* v){
	if (u->parent == nil){
		root = v;
	}else if (u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	if (v != nil){
		v->parent = u->parent;
	}
}

// // remove()
// // Deletes the pair for which key==k. If that pair is current, then current
// // becomes undefined.
// // Pre: contains(k).
void Dictionary::remove(keyType k){
	Node* N = search(root, k);
	if (N == nil){
		throw std::logic_error("Dictionary: remove(): key \""+k+"\" does not exist");
	}
	if (N->left == nil){
		transplant(N, N->right);
		num_pairs--;
	}else if (N->right == nil){
		transplant(N, N->left);
		num_pairs--;
	}else{
		Node* y = findMin(N->right);
		if (y->parent != N){
			transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y; 
		}//else?
		transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		
		num_pairs--;

	}
	if (current == N){
		current = nil;
	}
}

// // begin()
// // If non-empty, places current iterator at the first (key, value) pair
// // (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	current = findMin(root);
}

// // end()
// // If non-empty, places current iterator at the last (key, value) pair
// // (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	current = findMax(root);
}

// // next()
// // If the current iterator is not at the last pair, advances current 
// // to the next pair (as defined by the order operator < on keys). If 
// // the current iterator is at the last pair, makes current undefined.
// // Pre: hasCurrent()
void Dictionary::next(){
	if (this->hasCurrent() == false){
		throw std::logic_error("Dictionary: next(): current not defined");
	}
	current = findNext(current);
}

// // prev()
// // If the current iterator is not at the first pair, moves current to  
// // the previous pair (as defined by the order operator < on keys). If 
// // the current iterator is at the first pair, makes current undefined.
// // Pre: hasCurrent()
void Dictionary::prev(){
	if (this->hasCurrent() == false){
		throw std::logic_error("Dictionary: next(): current not defined");
	}
	current = findPrev(current);
}


// // Other Functions ---------------------------------------------------------

// // to_string()
// // Returns a string representation of this Dictionary. Consecutive (key, value)
// // pairs are separated by a newline "\n" character, and the items key and value 
// // are separated by the sequence space-colon-space " : ". The pairs are arranged 
// // in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	std::string s = "";
	inOrderString(s, this->root);
	return s;

}

// // pre_string()
// // Returns a string consisting of all keys in this Dictionary. Consecutive
// // keys are separated by newline "\n" characters. The key order is given
// // by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	std::string s = "";
	preOrderString(s, this->root);
	return s;
}

// // equals()
// // Returns true if and only if this Dictionary contains the same (key, value)
// // pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	return (this->num_pairs == D.num_pairs && this->to_string() == D.to_string());
}


// // Overloaded Operators ----------------------------------------------------

// // operator<<()
// // Inserts string representation of Dictionary D into stream, as defined by
// // member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// // operator==()
// // Returns true if and only if Dictionary A equals Dictionary B, as defined
// // by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return (A.equals(B));
}

// // operator=()
// // Overwrites the state of this Dictionary with state of D, and returns a
// // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if (this != &D){
		Dictionary temp = D;
		std::swap(root, temp.root);
   		std::swap(nil, temp.nil);
   		std::swap(current, temp.current);
   		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}
