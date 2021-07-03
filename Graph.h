//
//Graph class header
//

#ifndef PROYECTO_FINAL_GRAPH_H
#define PROYECTO_FINAL_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <string>
#include <fstream>

using namespace std;
//namesppcese to bue used for typename simplification
using uint = unsigned int;
using str = string;
using umap = unordered_map<str, int>;

// Cointainer node struct
struct Node {
    str id; // ID field
    int pos;
    int following;
    deque<Node *> followers;
    vector<double> politicalTendency; // vector of political tendency with 4 components (1 for each tendency)

};


class Graph {
private:
    umap ref; // hash table to associate the ID field with the position in the list
    //unordered_map<int, str> inverse_ref; // From position to ID
    vector<Node> graph; //adjacency list
    void politicalTendenceCalc(str);

public:
    Graph(); // Class constructor
    void insert(str vertex, str junctions); // insert in graph
    void print(); // print graph
    vector<Node> topInfluencer(int n);

    vector<Node> topInfluenced(int n);

    vector<Node> influenceColorMap ();
    ~Graph(); // class destructor

};


#endif //PROYECTO_FINAL_GRAPH_H
