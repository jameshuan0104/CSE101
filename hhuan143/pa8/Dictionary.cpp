/*
*James Huang, hhuan143
*2023 spring CSE101 PA#8
*Dictionary.cpp
*cpp for ADT
*/

#include<string>
#include<iostream>
#include<stdexcept>
#include<stdlib.h>
#include"Dictionary.h"

using namespace std;

#define red 0 
#define black 1 

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
	//set key to k, val to v, left & right & parent nodes to null pointers
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = black; // ?
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
		if (R->color == red){
			s += R->key + " (RED)\n";
		}else{
			s += R->key + "\n";
		}
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
/*void Dictionary::BST_insert(Node* M){
	Node* tempR = root;
	Node* tempP = nil;
	while (tempR != nil){
		tempP = tempR;
		if (M->key < tempR->key){
			tempR = tempR->left;
		}else if (M->key > tempR->key){
			tempR = tempR->right;
		}else{
			//setValue(tempR->key, tempR->val);
			tempR->val = M->val;
			return;
		}
	}
	Node* tempN = M;
	if (tempP == nil){
		tempN->left = nil;
		tempN->right = nil;
		tempN->parent = nil;
		root = tempN;
	}else if (M->key < tempP->key){
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
}*/

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if (R != N){
		setValue(R->key, R->val);
		//BST_insert(R);
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
		delete R;
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

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
	Node* y = N->right;
	N->right = y->left;
	if (y->left != nil) {
	  y->left->parent = N;
	}
	y->parent = N->parent;
	if (N->parent == nil) {
	  root = y;
	}
	else if (N == N->parent->left) {
	  N->parent->left = y;
	}
	else {
	  N->parent->right = y;
	}
	y->left = N;
	N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
	Node* y = N->left;
	N->left = y->right;
	if (y->right != nil) {
	  y->right->parent = N;
	}
	y->parent = N->parent;
	if (N->parent == nil) {
	  root = y;
	}
	else if (N == N->parent->right) {
	  N->parent->right = y;
	}
	else {
	  N->parent->left = y;
	}

	y->right = N;
	N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
	Node* y = nullptr;
    while (N->parent->color == red) {
        if (N->parent == N->parent->parent->left) {
         	y = N->parent->parent->right;
         	if (y->color == red) {
            	N->parent->color = black;
            	y->color = black;
            	N->parent->parent->color = red;
            	N = N->parent->parent;
        }
        else {
            if (N == N->parent->right) {
               N = N->parent;
               LeftRotate(N);
            }
            N->parent->color = black;
            N->parent->parent->color = red;
            RightRotate(N->parent->parent);
        }
    }
    else {
        y = N->parent->parent->left;
        if (y->color == red) {
            N->parent->color = black;
            y->color = black;
            N->parent->parent->color = red;
            N = N->parent->parent;
        }
        else {
            if (N == N->parent->left) {
               N = N->parent;
               RightRotate(N);
            }
            N->parent->color = black;
            N->parent->parent->color = red;
            LeftRotate(N->parent->parent);
         }
      }
   }
   root->color = black;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
	if (u->parent == nil){
		root = v;
	}else if (u == u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
	Node* w = nullptr;
	while (N != root && N->color == black){
		if (N == N->parent->left){
			w = N->parent->right;
			if (w->color == red){
				w->color = black;
				N->parent->color = red;
				LeftRotate(N->parent);
				w = N->parent->right;
			}
			if ((w->left->color == black) && (w->right->color == black)){
				w->color = red;
				N = N->parent;
			}else{
				if (w->right->color == black){
					w->left->color = black;
					w->color = red;
					RightRotate(w);
					w = N->parent->right;
				}
				w->color = N->parent->color;
				N->parent->color = black;
				w->right->color = black;
				LeftRotate(N->parent);
				N = root;
			}
		}else{
			w = N->parent->left;
			if (w->color == red){
				w->color = black;
				N->parent->color = red;
				RightRotate(N->parent);
				w = N->parent->left;
			}
			if ((w->right->color == black) && (w->left->color == black)){
				w->color = red;
				N = N->parent;
			}else{
				if (w->left->color == black){
					w->right->color = black;
					w->color = red;
					LeftRotate(w);
					w = N->parent->left;
				}
				w->color = N->parent->color;
				N->parent->color = black;
				w->left->color = black;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = black;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
	Node* y = N;
	Node* x = nullptr;
	int ogcolor = y->color; //y_original_color = y.color
	if (N->left == nil){
		x = N->right;
		RB_Transplant(N, N->right);
	}else if (N->right == nil){
		x = N->left;
		RB_Transplant(N, N->left);
	}else{
		y = findMin(N->right);
		ogcolor = y->color; //y_original_color = y.color
		x = y->right;
		if (y->parent == N){
			x->parent = y;
		}else{
			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
	}

	//y_original_color == BLACK
	if (ogcolor == black){
		RB_DeleteFixUp(x);
	}
}

// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	nil = new Node("abcdefghijkl", 999);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("abcdefghijkl", 999);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	root = nil;
	current = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
	clear();
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
	   Node* y = nil;
   Node* x = root;
   Node* z = new Node(k, v); // probably valgrind issue here
   int c;
   // cout << "hello" << endl;
   while (x != nil) {
      y = x;
      c = (z->key).compare(x->key);
      if (c == 0) { 
         x->val = z->val;
         delete z;
         return;
      }
      else if (c < 0) {
         x = x->left;
      }
      else {
         x = x->right;
      }
      // cout << "hello" << endl;
   }
   z->parent = y;
   c = (z->key).compare(y->key);
   if (y == nil) {
      root = z;
   }
   else if (c < 0) {
      y->left = z;
   }
   else {
      y->right = z;
   }
   z->left = nil;
   z->right = nil;
   z->color = red;
   num_pairs++;
   RB_InsertFixUp(z);
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
	Node* y = search(root, k);
	if (current == y){
		current = nil;
	}
	RB_Delete(y);
	num_pairs--;
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
	inOrderString(s, root);
	return s;

}

// // pre_string()
// // Returns a string consisting of all keys in this Dictionary. Consecutive
// // keys are separated by newline "\n" characters. The key order is given
// // by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	std::string s = "";
	preOrderString(s, root);
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
