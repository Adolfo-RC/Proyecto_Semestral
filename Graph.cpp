//
// Created by eric on 6/29/21.
//

#include "Graph.h"
#include <stdlib.h>

Graph::Graph() {

}

bool Graph::insert(str vertex, str junctions) {
    ifstream f;
    str read;
    f.open(vertex);

    int i = 0;
    int k, j;

    while (getline(f, read)) {
        if (i == 0){
            i ++;
            continue;
        }
        k = read.find(";");
        j = read.find(";", read.find(";") + 1);
        str result(read.begin() + k + 1, read.begin() + j);
        this->ref.insert(pair<str, int>(result, i));
        i++;

    }
    f.close();
    graph.resize(ref.size());
    f.open(junctions);
    i = 0;
    while (getline(f, read)){
        if (i == 0){
            i++;
            continue;
        }
        k = read.find(";");
        str followee(read.begin(), read.begin() + k);
        str follower(read.begin() + k + 1, read.end());
        umap::iterator it = ref.find(followee);
        //cout << it->second << endl;
        Node n {follower};

        graph[it->second].push_back(n);
        i ++;


    }
    f.close();
}

void Graph::print() {
    for (int i = 0; i < graph.size(); ++i) {
        cout << i << "--> ";
        for (int j = 0; j < graph[i].size(); j++){
            cout << graph[i][j].id << "--> ";
        }
        cout << endl;
    }
}

Graph::~Graph() {

}