//
// Created by eric on 6/29/21.
//

#include "Graph.h"
#include <queue>
#include <algorithm>
#include <set>

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

vector<pair<str, int>> Graph::topInfluencer (int cant){ // Compute the n most influencer user. (The user with more followers)

    auto comp = [](pair<int, vector<Node>> a, pair<int, vector<Node>> b) ->bool { // Lambda func for priority queue comparator
        return a.second.size() < b.second.size(); // ordered by vector sizes (number of followers)
    };
    priority_queue<pair <int, vector<Node>>, vector<pair <int, vector<Node>>>, decltype(comp)> top(comp); // priority queue for order
    for (int i = 0; i < graph.size(); ++i) { // Through all the vertexes O(V)
        top.push(pair<int, vector<Node>>(i, graph[i]));// O(log(V))

        // O(Vlog(V)
    }

    vector<pair<str, int>> topN (cant); // output vector
    int i = 0; // counter
    int k; // inverse key container
    unordered_map<int, str>::iterator it; // unordered map iterator to dereference

    ranking: // ranking loop
    k = top.top().first; // extract the influencest
    it = inverse_ref.find(k); // dereference from secondary key
    topN[i] =pair<str, int> (it->second, top.top().second.size()); // insert in output vector
    top.pop(); // extract from queue
    cant --; // decrees loop counter
    i ++; // increase the allocation counter
    if (cant != 0 and !top.empty()) goto ranking; // if ranking isn't complete and queue is no empty -> repeat ranking loop

    return topN;
}

vector<pair<str, int>> Graph::topInfluenced(int n) {
    vector<pair<str, int>> result (graph.size());
    for (int i = 0; i < result.size(); ++i) {
        result[i].first = inverse_ref.find(i)->second;
        result[i].second = 0;
    }
    int k;
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            k = ref.find(graph[i][j].id)->second;
            result[k].second++;
        }
    }

    auto sort = [](pair<str, int> a, pair<str, int> b)->bool {
        return a.second > b.second;
    };

    std::sort(result.begin(), result.end(), sort);

    return std::vector<pair<str, int>>(result.begin(), result.begin() + n);

}

void Graph::politicalTendenceCalc(int node) {
    queue<int> Q;
    set<int> visited;
    double politicalRank = 100;
    int u, k;
    Q.push(node);
    visited.insert(node);
    while (!Q.empty()){
        u = Q.front();
        Q.pop();
        for (Node i : graph[u]) {
            k = ref.find(i.id)->second;
            if (visited.find(k) == visited.end()){
                visited.insert(ref.find(i.id)->second);
                Q.push(ref.find(i.id)->second);
            }
            i.politicalTendency[node] += politicalRank;
        }
        politicalRank = politicalRank/2;
    }
}

vector<Node> Graph::influenceColorMap() {

}

void Graph::print( int n) { // print graph
    for (int i = 0; i < n; ++i) {
        cout << inverse_ref.find(i)->second << "--> ";
        for (int j = 0; j < graph[i].size(); j++){
            cout << graph[i][j].id << "--> ";
        }
        cout << endl;
    }
}

Graph::~Graph() {

}