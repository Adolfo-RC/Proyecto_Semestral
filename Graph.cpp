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
        this->graph.push_back({result, i - 1, 0, 0});
        graph[i - 1].politicalTendency.resize(4);
        graph[i - 1].politicalTendency = {0, 0, 0, 0};
        i++;

    }
    f.close();
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
        umap::iterator it2 = ref.find(follower);
        graph[it->second].followers.push_front(&graph[it2->second]); // insert into the graph O(1) amortized time;
        i ++;


    }
    f.close();
}

vector<Node> Graph::topInfluencer (int cant){ // Compute the n most influencer user. (The user with more followers)
    vector<Node> result = graph;
    auto comp = [] (Node a, Node b)->bool {
        return a.followers.size() > b.followers.size();
    };
    sort(result.begin(), result.end(), comp);
    return vector<Node>(result.begin(), result.begin() + cant );

}

vector<Node> Graph::topInfluenced(int n) {
    cout << "Holis\n";
    for (Node i : graph){
        for (auto j: i.followers){
            j->following ++;
        }
    }
    cout << "Bye :(\n";
    vector<Node> result = graph;
    sort(result.begin(), result.end(), [](Node a, Node b)->bool {return a.following > b.following;});
    cout << ":P\n";
    return vector<Node>(result.begin(), result.begin() + n);
}

void Graph::politicalTendenceCalc( str Magazine) {
    int node = ref.find(Magazine)->second;

    queue<Node> Q;
    set <str> visited;
    Node u = graph[node];
    u.polPow = 200.0;
    Q.push(u);
    visited.insert(graph[node].id);

    int h = 0;
    while (!Q.empty()){
        u = Q.front();

        Q.pop();
        for (auto i : u.followers){
            if (visited.find(i->id) == visited.end()){
                i->politicalTendency[node] = u.polPow/2;
                i->polPow = u.polPow / 2;
                Q.push(*i);
                visited.insert(i->id);

                //cout << i->polPow << endl;
            }

        }

        h++;
    }



}
double sum (vector<double> a){
    double res = 0;
    for (double j : a){
        res += j;
    }
    return res;
}
vector<Node> Graph::influenceColorMap() {
    politicalTendenceCalc("Cooperativa");
    politicalTendenceCalc("soyvaldiviacl");
    politicalTendenceCalc("latercera");
    politicalTendenceCalc("elmostrador");

    double s = 0;
    for (Node i : graph){
        s = sum(i.politicalTendency);
        cout << " Political tendency " << i.id << ": ";
        for (double j : i.politicalTendency){
            j = (j / s) * 100;
            cout << j << "% ";
        }
        cout <<endl;
    }
    return graph;

}

void Graph::print() { // print graph
    int k = 0;
    for (auto i : graph) {
        cout << i.id << " --> ";
        for (auto j : i.followers){
            cout << j->id << " --> ";
            k ++;
        }
        cout << "NULL." << endl;
    }

}

Graph::~Graph() {

}