/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  z32fu@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
private:
    Leftist_node<Type> *root_node;
    int heap_size;
    
public:
    Leftist_heap();
    ~Leftist_heap();
    
    void swap( Leftist_heap &heap );
    
    
    bool empty() const;
    int size() const;
    int null_path_length() const;
    Type top() const;
    int count( Type const & ) const;
    
    void push( Type const & );
    Type pop();
    void clear();
    
    // Friends
    
    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
    // does nothing
}



template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
    clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
    std::swap( root_node, heap.root_node );
    std::swap( heap_size, heap.heap_size );
}

template <typename Type>
bool Leftist_heap<Type>::empty() const {
    return (root_node == nullptr);
}

template <typename Type>
int Leftist_heap<Type>::size() const {
    return heap_size;
}

template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
    return root_node->null_path_length();
}

template <typename Type>
int Leftist_heap<Type>::count( const Type &obj ) const {
    return root_node->count(obj);
}

template<typename Type>
Type Leftist_heap<Type>::top() const {
    if(empty()){
        throw underflow();
    }
    else{
        return root_node->retrieve();
    }
}

template <typename Type>
void Leftist_heap<Type>::push( Type const &obj ) {
    Leftist_node<Type> * tmp = new Leftist_node<Type>( obj );
    root_node->push( tmp, root_node );
    ++heap_size;
}

template <typename Type>
Type Leftist_heap<Type>::pop() {
    if (empty()) {
        throw underflow();
    }
    else {
        Leftist_node<Type> *tmp = root_node;
        Type popped_element = root_node->retrieve();
        root_node = root_node->left();
        root_node->push(tmp->right(),root_node);
        --heap_size;
        delete tmp;
        return popped_element;
    }
    
}

template <typename Type>
void Leftist_heap<Type>::clear() {
    root_node ->clear();
    root_node = nullptr;
    heap_size = 0;
    
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif