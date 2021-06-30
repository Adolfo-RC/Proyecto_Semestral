//
//Graph ---- class
//

#ifndef PROYECTO_FINAL_GRAPH_H
#define PROYECTO_FINAL_GRAPH_H
#include <iostream>
#include <unordered_map>
#include <vector>

#include <string>
#include <fstream>

using namespace std;
using  uint = unsigned int;
using  str =  string;
using  umap = unordered_map<str, int>;

struct Node{
    str id;
    vector<int> politicalTendence;
    Node( str id){
        this->id = id;
        politicalTendence.resize(4);
        politicalTendence = {0, 0, 0, 0};
    }
};


class Graph {
private:
    umap ref;
    vector<vector<Node>> graph;

public:
    Graph();
    bool insert (str vertex, str junctions);
    void print();
    ~Graph();

};


#endif //PROYECTO_FINAL_GRAPH_H
