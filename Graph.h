//
// Created by eric on 6/29/21.
//

#ifndef PROYECTO_FINAL_GRAPH_H
#define PROYECTO_FINAL_GRAPH_H
#include <unordered_map>
#include <vector>
#include <deque>
#include <string>

using namespace std;
using  uint = unsigned int;
using  umap = unordered_map<pair<int, int>, int>;
using  str =  string;
struct Node{
    uint id;
    vector<int> politicalTendence;
    Node(){
        politicalTendence.resize(4);
    }
};

class Graph {
private:
    umap ref;
    vector<deque<Node>> graph;

public:
    Graph();
    bool insert (str vertex, str junctions);

};


#endif //PROYECTO_FINAL_GRAPH_H
