/*****************************************
 * UW User ID:  z32fu
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "ece250.h"

// include whatever classes you want

class Weighted_graph {
private:

    static const double INF;
    double **graph_matrix;
    int size;
    int edge;
    bool visited;
    bool *visitedA;
    double *distanceA;
    
public:
    Weighted_graph( int = 50 );
    ~Weighted_graph();
    
    int degree( int ) const;
    int edge_count() const;
    double adjacent( int, int ) const;
    double distance( int, int ) const;
    
    void insert( int, int, double );
    
    // Friends
    
    friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};


const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

Weighted_graph::Weighted_graph( int n ):
graph_matrix( new double*[n] ) {
    
    if(n<=0){
        n=1;
    }
    edge=0;
    size=n;
    visited = false;
    visitedA = new bool[n];
    distanceA = new double[n];
    for (int i = 0; i < n; i++)
    {
        graph_matrix[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                graph_matrix[i][j] = 0.0;
            }
            else
            {
                graph_matrix[i][j] = INF;
            }
        }
        visitedA[i] = false;
        distanceA[i] = INF;
    }
}


Weighted_graph::~Weighted_graph(){
    for(int i=0;i<size;i++){
        delete[] graph_matrix[i];
    }
    delete[] graph_matrix;
    delete[] visitedA;
    delete[] distanceA;
}

int Weighted_graph::degree(int n) const {
    int degree = 0;
    for(int i = 0; i<size;i++){
        if(graph_matrix[n][i] == INF || graph_matrix[n][i] ==0){
            
        }
        else{
            degree++;
        }
    }
    return degree;
}
int Weighted_graph::edge_count() const {
    return edge;
}

double Weighted_graph::adjacent(int m, int n) const {
    if(m<0 || m>= size || n<0 || n>=size){
        throw illegal_argument();
    }
    return graph_matrix[m][n];
    
}

void Weighted_graph::insert(int m, int n, double w)
{
    if(n<0 || n>= size || m<0 || m>=size || m==n || w<=0)
    {
        throw illegal_argument();
    }
    if(w<=0){
        throw illegal_argument();
    }
    if(adjacent(m,n) == INF)
    {
        edge++;
    }
    graph_matrix[m][n] = w;
    graph_matrix[n][m] = w;
    visited = false;
}

double Weighted_graph::distance(int m, int n) const
{
    
    int current = m;
    int next = 0;
    double shortestPath = INF;
    if (visited)
    {
        return distanceA[n];
    }
    else
    {
        if (m < 0 || m >= size || n < 0 || n >= size )
        {
            throw illegal_argument();
        }
        if (m == n)
        {
            return 0.0;
        }
        for (int i = 0; i < size; i++)
        {
            visitedA[i] = false;
            distanceA[i] = INF;
        }
        visitedA[m] = true;
        distanceA[m] = 0.0;
        for (int i = 0; i < size; i++)
        {
            visitedA[current] = true;
            shortestPath = INF;
            for (int j = 0; j < size; j++)
            {
                if (graph_matrix[current][j] != INF && graph_matrix[current][j] != 0.0)
                {
                    if ((graph_matrix[j][current] + distanceA[current]) < distanceA[j])
                    {
                        distanceA[j] = graph_matrix[j][current] + distanceA[current];
                    }
                    if (visitedA[j] == false)
                    {
                        if (distanceA[j] < shortestPath || distanceA[j] == 0)
                        {
                            shortestPath = distanceA[j];
                            next = j;
                        }
                    }
                }
            }
            current = next;
            next = 0;
        }
        
        Weighted_graph visited = true;
        return distanceA[n];
    }
    
}


// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif