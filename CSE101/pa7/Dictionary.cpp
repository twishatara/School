//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 7
// Dictionary.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include "Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Creates new Dictionary in the empty state.·
Dictionary::Dictionary() {
    nil = new Node("llkjhgfdsa", -999);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("llkjhgfdsa", -999);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    num_pairs = 0;
    delete nil;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}


// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        num_pairs --;
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if ((R == nil) || (k == R->key)) {
        return R;
    }
    else if (k < R->key) {
        return search(R->left, k);
    }
    else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    Node* l = R;
    while (l->left != nil) {
        l = l->left;
    }
    return l;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    Node *r = R;
    while (r->right != nil) {
        r = r->right;
    }
    return r;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {                 // case 1
        return findMin(N->right);
    }
    Node* y = N->parent;                      // case 2
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {                 // case 1
        return findMax(N->left);
    }
    Node* y = N->parent;                      // case 2
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if (search(root, k) != nil) {
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node *f = search(root, k);
    if (contains(f->key) == false) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist in dictionary");
    }
    return f->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current == nil) {
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: currentKey(): current key does not exist");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: currentVal(): current key does not exist");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    num_pairs = 0;
    current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    Node* y = nil;
    Node* x = root;
    while (x != nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            return;
        }
        else if (k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    Node* n = new Node(k, v);
    n->parent = y;
    n->left = nil;
    n->right = nil;
    if (y == nil) {
        root = n;
    }
    else if (k < y->key) {
        y->left = n;
    }
    else {
        y->right = n;
    }
    num_pairs += 1;
}

// transplant()
//
// Pre:
void Dictionary::transplant(Node* N, Node* R) {
    if (N->parent == nil) {
        root = R;
    }
    else if (N == N->parent->left) {
        N->parent->left = R;
    }
    else {
        N->parent->right = R;
    }
    if (R != nil) {
        R->parent = N->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist in dictionary");
    }
    Node *f = search(root, k);
    Node *y;
    if (f->left == nil) {              // case 1  or case 2.1 (right only)
        transplant(f, f->right);
    }
    else if (f->right == nil) {         // case 2.2 (left only)
        transplant(f, f->left);
    }
    else {                           // case 3
        y = findMin(f->right);
        if (y->parent != f) {
            transplant(y, y->right);
            y->right = f->right;
            y->right->parent = y;
        }
        transplant(f, y);
        y->left = f->left;
        y->left->parent = y;
    }
    if (current == f) {
        current = nil;
    }
    num_pairs --;
    delete f;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (num_pairs <= 0) {
        return;
    }
    current = root;
    while (current->left != nil) {
        current = current->left;
    }
    return;
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (num_pairs <= 0) {
        return;
    }
    current = root;
    while (current->right != nil) {
        current = current->right;
    }
    return;
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: next(): current key does not exist");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: prev(): current key does not exist");
    }
    current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    Node *f;
    Dictionary A = *this;
    Dictionary B = D;
    //std::cout << "HEYY A " << A << std::endl;
    A.begin();
    if (A.num_pairs != B.num_pairs) {
        return false;
    }
    //std::cout << A.current->key << std::endl;
    while (A.current != A.nil) {
        f = B.search(B.root, A.current->key);
        //std::cout << "a key val " << A.current->key << " " << A.current->val << std::endl;
        //std::cout << "f key val " << f->key << " " << f->val << std::endl;
        if (f->key != A.current->key) {
            return false;
        }
        if (f->val != A.current->val) {
            return false;
        }
        A.next();
    }
    return true;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(nil, temp.nil);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}


