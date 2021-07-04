//
// Created by eric on 6/29/21.
//

#include "Graph.h"
#include <queue>
#include <stack>
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

vector<Node> Graph::topInfluencer (int cant){ // Compute the n most influencer users. (The users with more followers)
    vector<Node> result = graph; // Result vector
    auto comp = [] (Node a, Node b)->bool { // lambda comparator func
        return a.followers.size() > b.followers.size(); // if number of followers is bigger
    };
    sort(result.begin(), result.end(), comp); // sort graph by followers
    return vector<Node>(result.begin(), result.begin() + cant ); // return sorted vector

}


vector<Node> Graph::topInfluenced(int n) { // Compute the n most influneced users (Useres following more people)

    for (Node i : graph){
        for (auto j: i.followers){
            j->following ++; // If user appears in other user list of followers
        }
    }
    vector<Node> result = graph; // result vector
    sort(result.begin(), result.end(), [](Node a, Node b)->bool {return a.following > b.following;}); // sorted by following field
    return vector<Node>(result.begin(), result.begin() + n); // return sorted vector
}

void Graph::politicalTendencyCalc(str Magazine) { // Computes the political tendency for all user. BFS run
    int node = ref.find(Magazine)->second; // Find node pos by id

    queue<Node> Q; // BFS queue
    set <str> visited; // visited set
    Node u = graph[node]; // Start node
    u.polPow = 200.0; // Initial polPow
    Q.push(u); // Insert u into queue
    visited.insert(graph[node].id); // mark u as visited

    // Coloring the graph
    while (!Q.empty()){ // While elements in queue
        u = Q.front(); // u = first inserted element

        Q.pop(); // extarct from queue
        for (auto i : u.followers){ // for all the children
            if (visited.find(i->id) == visited.end()){ // if the instance has not been visited yet
                i->politicalTendency[node] = u.polPow/2; // Assign half of the political power of his parent to the current political tendency
                i->polPow = u.polPow / 2; // And to his own political power
                Q.push(*i); // inert i to queue
                visited.insert(i->id); // mark i as visitied

            }

        }


    }



}

// A dummy sum func
double sum (vector<double> a){
    double res = 0;
    for (double j : a){
        res += j;
    }
    return res;
}
vector<Node> Graph::influenceColorMap() { // Color all the graph by his political influence
    politicalTendencyCalc("Cooperativa"); // right
    politicalTendencyCalc("soyvaldiviacl"); // libertarian
    politicalTendencyCalc("latercera"); // right
    politicalTendencyCalc("elmostrador"); // center

    double s = 0; // sum
    for (Node i : graph){ // for every node in graph
        s = sum(i.politicalTendency); // sum his influences
        cout << " Political tendency " << i.id << ": ";
        for (double j : i.politicalTendency){ // for every component in his political tendency
            j = (j / s) * 100; // % of influence
            cout << j << "% ";
        }
        cout <<endl;
    }
    return graph; // return the graph modified.

}

void Graph::recursiveDFS(Node n, set<str>* vis) { // DFS without stack implementation
    //cout << n.id << " --> ";

    vis->insert(n.id); // set node as visited
    for (auto i : n.followers){ // for every children
        if (vis->find(i->id) == vis->end()){
            recursiveDFS(*i, vis); // recursive call
        }
    }
}



void Graph::recursiveDFS(Node n, set<str> *vis, stack<Node> *s) { // DFS with stack for Kosaraju
    vis->insert(n.id);
    for (auto i : n.followers){
        if (vis->find(i->id) == vis->end()){
            recursiveDFS(*i, vis, s); // same of recursiveDEFS
        }
    }
    s->push(n); // When node is done insert node to stack

}

void Graph::Kosaraju() { // Kosaraju
    stack<Node> s; // stack needed
    set<str> vis; // set for direct DFS
    recursiveDFS(graph[0], &vis, &s ); // direct recursive call

    for (Node i : graph){ // For every node
        if (vis.find(i.id) == vis.end()){ // that has not been visited
            recursiveDFS(i, &vis, &s); // run dfs from that node
        }
        if (graph.size() == vis.size()) break; // if all node has been visited -> end;
    }
    Graph T = this->transpose(); // Inverse graph
    vis.clear(); // clear set for inverse run
    int k = 0; // SCC counter
    while (!s.empty()){ // While elements in stack
        Node top = s.top(); // first node in stack
        s.pop(); // un - pile node
        if (vis.find(top.id) == vis.end()){ // if has benn not visited
            T.recursiveDFS(top, &vis); // DFS from node

            k++; // increase SCC counter
        }

    }
    cout << vis.size() << " " << graph.size() << endl;
    cout << k << " SCCs."<< endl;
}



Graph Graph::transpose() { // Compute the inverse graph
    Graph T = *this; //New graph = current graph
    for (auto i : T.graph){ //for every node in new graph
        i.followers.clear(); // clear hsi followers. A 0 node in list status is implicit.
    }
    for (auto i : graph){ // for every node in graph
        for (auto j : i.followers){ // for every follower of current node
            T.graph[j->pos].followers.push_front(&i); // Change follower for followee
        }
    }
    return T; //  return graph

}

void Graph::print() { // print graph

    for (auto i : graph) {
        cout << i.id << " --> ";
        for (auto j : i.followers){
            cout << j->id << " --> ";

        }
    }

}
int Graph ::size() { return graph.size();}

Graph::~Graph() {

}