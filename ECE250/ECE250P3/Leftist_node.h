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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
private:
    Type element;
    Leftist_node *left_tree;
    Leftist_node *right_tree;
    int heap_null_path_length;
    
public:
    Leftist_node( Type const & );
    
    Type retrieve() const;
    bool empty() const;
    Leftist_node *left() const;
    Leftist_node *right() const;
    int count( Type const & ) const;
    int null_path_length() const;
    
    void push( Leftist_node *, Leftist_node *& );
    void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
    // does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
    return ( this == nullptr );
}

template<typename Type>
Type Leftist_node<Type>::retrieve() const {
    if(empty()){
        throw underflow();
    }
    else{
        return element;
    }
}

template<typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
    return left_tree;
}

template<typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
    return right_tree;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    if(empty()){
        return -1;
    }else{
        if(left()->null_path_length() < right()->null_path_length()){
            return left()->null_path_length()+1;
        }
        else{
            return right()->null_path_length()+1;
        }
    }
}

template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const {
    int counter = 0;
    
    if ( !empty() ) {
        if ( retrieve() == obj ) {
            counter = 1 + left()->count(obj) + right()->count(obj);
        } else if ( retrieve() < obj ) {
            counter = left()->count(obj) + right()->count(obj);
        } else {
            counter = 0;
        }
    }
    
    return counter;
    
}
template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ) {
    if(new_heap->empty()){
        return;
    }else{
        if(this == nullptr){
             ptr_to_this = new_heap;
            return;
        }if(retrieve() <= new_heap->retrieve()){
            right_tree->push(new_heap,right_tree);
            if(left()->null_path_length() < right()->null_path_length()){
                heap_null_path_length = 1 + right()->null_path_length();
                std::swap( left_tree, right_tree );
            }
        }
        else{
            ptr_to_this = new_heap;
            ptr_to_this->push( this, right_tree );
        }
    }
}

template <typename Type>
void Leftist_node<Type>::clear() {
    if(empty()){
        return;
    }else{
        left_tree->clear();
        right_tree->clear();
        delete this;
    }
    
}

// You must implement everything

#endif