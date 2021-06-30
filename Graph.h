//
//Graph class header
//

#ifndef PROYECTO_FINAL_GRAPH_H
#define PROYECTO_FINAL_GRAPH_H
#include <iostream>
#include <unordered_map>
#include <vector>

#include <string>
#include <fstream>

using namespace std;
//namesppcese to bue used for typename simplification
using  uint = unsigned int;
using  str =  string;
using  umap = unordered_map<str, int>;

// Cointainer node struct
struct Node{
    str id; // ID field
    vector<int> politicalTendency; // vector of political tendency with 4 components (1 for each tendency)
    Node( str id){ // Node class constructor
        this->id = id;
        politicalTendency.resize(4); // Array dimension
        politicalTendency = {0, 0, 0, 0}; // initial percentage
    }
};


class Graph {
private:
    umap ref; // hash table to associate the ID field with the position in the list
    unordered_map<int, str> inverse_ref; // From position to ID
    vector<vector<Node>> graph; // list od adjacency

public:
    Graph(); // Class constructor
    void insert (str vertex, str junctions); // insert in graph
    void print(); // print graph
    vector<pair<str, int>> topInfluencer (int n);
    ~Graph(); // class destructor

};


#endif //PROYECTO_FINAL_GRAPH_H
