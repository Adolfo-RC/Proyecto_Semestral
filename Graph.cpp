//
// Created by eric on 6/29/21.
//

#include "Graph.h"
#include <queue>

Graph::Graph() { // Empty constructor

}

void Graph::insert(str vertex, str junctions) { // insert function takes as parameter absolute path to csv files
    ifstream f; // file buffer
    str read; // str for reading
    f.open(vertex);

    int i = 0;
    int k, j;

    while (getline(f, read)) { // read line from file. O(V) with V number of vertexes
        if (i == 0){ // Skip the first read (cv header)
            i++;
            continue;
        }
        k = read.find(";"); // find usr name (ID field) begin
        j = read.find(";", read.find(";") + 1); // find usr name end
        str result(read.begin() + k + 1, read.begin() + j); // extract the usr name
        this->ref.insert(pair<str, int>(result, i - 1)); // insert into the hash table
        this->inverse_ref.insert(pair<int, str>(i - 1, result));
        i++;

    }
    f.close();
    graph.resize(ref.size()); // resizing to the number of vertexes
    f.open(junctions); // reading the connections
    i = 0;
    while (getline(f, read)){  // reading the lines
        if (i == 0){
            i++;
            continue;
        }
        k = read.find(";"); // find the comma separator
        str followee(read.begin(), read.begin() + k); // extracting followee
        str follower(read.begin() + k + 1, read.end()); // extracting follower
        umap::iterator it = ref.find(followee); // find the table position by  the id
        //cout << it->second << endl;
        Node n (follower); // create a new node

        graph[it->second].push_back(n); // insert into the graph O(1) amortized time;
        i ++;


    }
    f.close();
}

vector<pair<str, int>> Graph::topInfluencer (int cant){

    auto comp = [](pair<int, vector<Node>> a, pair<int, vector<Node>> b) ->bool {
        return a.second.size() < b.second.size();
    };
    priority_queue<pair <int, vector<Node>>, vector<pair <int, vector<Node>>>, decltype(comp)> top(comp);
    for (int i = 0; i < graph.size(); ++i) {
        top.push(pair<int, vector<Node>>(i, graph[i]));
    }

    vector<pair<str, int>> topN (cant);
    int i = 0;
    int k;
    unordered_map<int, str>::iterator it;
    ranking:
    k = top.top().first;
    it = inverse_ref.find(k);
    topN[i] =pair<str, int> (it->second, top.top().second.size());
    top.pop();
    cant --;
    i ++;
    if (cant != 0) goto ranking;

    return topN;
}

void Graph::print() { // print graph
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