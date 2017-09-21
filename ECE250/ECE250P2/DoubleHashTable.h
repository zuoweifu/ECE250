#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  z32fu
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
    int count;
    int power;
    int array_size;
    T *array;
    state *array_state;
    
    int h1( T const & ) const; // first hash function
    int h2( T const & ) const; // second hash function
    
public:
    DoubleHashTable( int = 5 );
    ~DoubleHashTable();
    int size() const;
    int capacity() const;
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;
    void print() const;
    void insert( T const & );
    bool remove( T const & );
    void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
    
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete []array;
    delete []array_state; //delete memory
}

template<typename T >
int DoubleHashTable<T >::size() const {
        return count; // return the size of hash table
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
        return array_size;  //return the capacity of hashtable
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    if(count <= 0){
        return true; //if size of hashtable is no bigger than 0, return true
    }else{
        return false; // otehrwise return false
    }
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int probe = (int)obj % array_size;
    if(probe<0){
        probe = probe + array_size; //if probe is smaller than 0, add array_size to probe.
    }
        return probe;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    int offset = ((int)obj / array_size) % array_size;
    if(offset < 0){
        offset = offset + array_size;   //if offset is smaller than 0, add array_size to offset.
    }
    
    if( offset % 2 == 0){
        offset = offset + 1;    //if offset is even, add 1 to make offset odd.
    }
    
    return offset;
}


template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    int loopcount = 0;  //loopcount of the while loop
    int probe = h1(obj);    //call h1 to get probe
    int offset = h2(obj);   //call h2 to get offset
    if (array[probe] != obj) {  //check if probe is already the index
        //while the element is deleted, continue the loop
        //while the element is occupied but not the object, continue the loop
        //cotinue the loop until we reached the capacity of the hashtable
  while ((array_state[probe] == DELETED) || (array_state[probe] == OCCUPIED && array[probe] != obj) || (loopcount <= array_size)) {
        probe = (probe + offset) % array_size; //double hashing
        loopcount = loopcount +1;
    }
    }
    int index = probe;
        if(array_state[index] == OCCUPIED && array[index] == obj ){ //if the index of that object is occupied and the object is the element, when the object is member of the hashtable
            return true;
        }
        else{
            return false; //otherwise not.
        }

}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    if(n < 0)
    {
    throw overflow();   //throw overflow exception
    }
    return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    if (count == array_size) {
        throw overflow();   //throw overflow exception when the hashtable is full
    }
    int probe = h1(obj);
    int offset = h2(obj);
    while ( array_state[probe] == OCCUPIED ) {
        probe = (probe + offset) % array_size;  //continue hasing until we find the index
    }

    int index = probe;
    array[index] = obj;
    count = count + 1;
    array_state[index] = OCCUPIED;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {

        if(member(obj)){
            int loopcount = 0;
            int probe = h1(obj);
            int offset = h2(obj);
            if (array[probe] != obj) {
                while ((array_state[probe] == DELETED) || (array_state[probe] == OCCUPIED && array[probe] != obj) || (loopcount <= array_size)) {
                    probe = (probe + offset) % array_size;
                    loopcount = loopcount +1;
                }
            }
            int index = probe;
            array[index] = -1;
            array_state[index] = DELETED;   //change state
            count = count - 1;  //substract the size by 1
            return true;
            
        }else{
            return false;
        }
    
}

template<typename T >
void DoubleHashTable<T >::clear() {
    count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
    // enter your implemetation here 	
    return;
}

#endif