#ifndef PROYECTO_FINAL_GRAPH_H
#define PROYECTO_FINAL_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <set>
#include <stack>

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
    double polPow;
    deque<Node *> followers;
    vector<double> politicalTendency; // vector of political tendency with 4 components (1 for each tendency)

};


class Graph {
private:
    umap ref; // hash table to associate the ID field with the position in the list
    //unordered_map<int, str> inverse_ref; // From position to ID
    vector<Node> graph; //adjacency list
    void politicalTendencyCalc(str Magazine);

    void DFSUtil (int n, bool visited []);

    void fillOrder(int n, bool visited [], stack<Node> &s);

    Graph transpose();

    void insert(Node, Node);

public:
    Graph(); // Class constructor
    void insert(str vertex, str junctions); // insert in graph
    void insert(str node);



    void print(); // print graph
    vector<Node> topInfluencer(int n); // returns a ranking with the most followed users

    vector<Node> topInfluenced(int n); // returns a ranking with the most followers users

    vector<Node> influenceColorMap(); // returns an array with % of political influence for every user

    int Kosaraju(); // Kosaraju's SCC detection algorithm. Returns count

    void exportGraph(str path); // Export graph as a txt

    void exportTendencies(str path); // Export tendencies as txt

    void computeStats(); // compute the political dispersion in Chile

    int size(); // returns the number of vertex in graph

    Node returnNode(int n); // returns a partiular node
    Node returnNode(str id); // returns a particular node str overloaded

    void getGraphSize(); // Computes the graph size in MB

    int findIsland();


    ~Graph(); // class destructor

};


#endif //PROYECTO_FINAL_GRAPH_H
