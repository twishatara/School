//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 8
// Dictionary.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include "Dictionary.h"

#define RED -98765
#define BLACK -12345

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED; // this may have to be changed to red?
}

// Creates new Dictionary in the empty state.·
Dictionary::Dictionary() {
    nil = new Node("llkjhgfdsa", -999);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("llkjhgfdsa", -999);
    nil->color = BLACK;
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
        setValue(R->key, R->val);
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
    if (N == findMax(root)) {
        return nil;
    }
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
    if (N == findMin(root)) {
        return nil;
    }
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

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    Node *y = N->right;
    N->right = y->left;
    if (y->left != nil) {     // not necessary if using sentinal nil node
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
void Dictionary::RightRotate(Node* N) {
    Node *y = N->left;
    N->left = y->right;
    if (y->right != nil) {  // not necessary if using sentinal nil node
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
void Dictionary::RB_InsertFixUp(Node* N) {
    Node *y;
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            y = N->parent->parent->right;
            if (y->color == RED) {
                N->parent->color = BLACK;               // case 1
                y->color = BLACK;                       // case 1
                N->parent->parent->color = RED;         // case 1
                N = N->parent->parent;                  // case 1
            }
            else {
                if (N == N->parent->right) {
                    N = N->parent;                      // case 2
                    LeftRotate(N);                      // case 2
                }
                N->parent->color = BLACK;               // case 3
                N->parent->parent->color = RED;         // case 3
                RightRotate(N->parent->parent);         // case 3
            }
        }
        else {
            y = N->parent->parent->left;
            if (y->color == RED) {
                N->parent->color = BLACK;               // case 4
                y->color = BLACK;                       // case 4
                N->parent->parent->color = RED;         // case 4
                N = N->parent->parent;                  // case 4
            }
            // COULD BE BREAKING HERE?? CHECK
            else {
                if (N == N->parent->left) {
                    N = N->parent;                      // case 5
                    RightRotate(N);                     // case 5
                }
                N->parent->color = BLACK;               // case 6
                N->parent->parent->color = RED;         // case 6
                LeftRotate(N->parent->parent);          // case 6
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_Delete()
void Dictionary::RB_Delete(Node *z) {
    Node *y = z;
    Node *x;
    int y_original_color = y->color;
    if (z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    }
    else if (z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    }
    else {
        y = findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK) {
        RB_DeleteFixUp(x);
    }
    if (z == current) {
        current = nil;
    }
    delete(z);
    num_pairs --;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    Node *w;
    while (N != root && N->color == BLACK) {
        if (N == N->parent->left) {
            w = N->parent->right;
            if (w->color == RED) {
                w->color = BLACK;                                               // case 1
                N->parent->color = RED;                                         // case 1
                LeftRotate(N->parent);                                          // case 1
                w = N->parent->right;                                           // case 1
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                                                 // case 2
                N = N->parent;                                                  // case 2
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;                                     // case 3
                    w->color = RED;                                             // case 3
                    RightRotate(w);                                             // case 3
                    w = N->parent->right;                                       // case 3
                }
                w->color = N->parent->color;                                    // case 4
                N->parent->color = BLACK;                                       // case 4
                w->right->color = BLACK;                                        // case 4
                LeftRotate(N->parent);                                          // case 4
                N = root;                                                       // case 4
            }
        }
        else {
            w = N->parent->left;
            if (w->color == RED) {
                w->color = BLACK;                                               // case 5
                N->parent->color = RED;                                         // case 5
                RightRotate(N->parent);                                         // case 5
                //here?? Check rotate next fs
                w = N->parent->left;                                            // case 5
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;                                                 // case 6
                N = N->parent;                                                  // case 6
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;                                    // case 7
                    w->color = RED;                                             // case 7
                    LeftRotate(w);                                              // case 7
                    w = N->parent->left;                                        // case 7
                }
                w->color = N->parent->color;                                    // case 8
                N->parent->color = BLACK;                                       // case 8
                w->left->color = BLACK;                                         // case 8
                RightRotate(N->parent);                                         // case 8
                N = root;                                                       // case 8
            }
        }
    }
    N->color = BLACK;
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
    root = nil;
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
    Node *n = new Node(k, v);
    n->parent = y;
    if (y == nil) {
        root = n;
    }
    else if (n->key < y->key) {
        y->left = n;
    }
    else {
        y->right = n;
    }
    n->right = nil;
    n->left = nil;
    num_pairs ++;
    n->color = RED;
    RB_InsertFixUp(n);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist in dictionary");
    }
    RB_Delete(search(root, k));
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
    A.begin();
    if (A.num_pairs != B.num_pairs) {
        return false;
    }
    while (A.current != A.nil) {
        f = B.search(B.root, A.current->key);
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

