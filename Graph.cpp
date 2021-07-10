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
        if (i == 0) { // Skip the first read (cv header)
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
    while (getline(f, read)) {  // reading the lines
        if (i == 0) {
            i++;
            continue;
        }
        k = read.find(";"); // find the comma separator
        str followee(read.begin(), read.begin() + k); // extracting followee
        str follower(read.begin() + k + 1, read.end()); // extracting follower
        umap::iterator it = ref.find(followee); // find the table position by  the id
        umap::iterator it2 = ref.find(follower);
        graph[it->second].followers.push_front(&graph[it2->second]); // insert into the graph O(1) amortized time;
        i++;


    }
    f.close();
}


vector<Node> Graph::topInfluencer(int cant) { // Compute the n most influencer users. (The users with more followers)
    vector<Node> result = graph; // Result vector
    auto comp = [](Node a, Node b) -> bool { // lambda comparator func
        return a.followers.size() > b.followers.size(); // if number of followers is bigger
    };
    sort(result.begin(), result.end(), comp); // sort graph by followers
    return vector<Node>(result.begin(), result.begin() + cant); // return sorted vector

}


vector<Node> Graph::topInfluenced(int n) { // Compute the n most influneced users (Useres following more people)

    for (Node i : graph) {
        for (auto j: i.followers) {
            j->following++; // If user appears in other user list of followers
        }
    }
    vector<Node> result = graph; // result vector
    sort(result.begin(), result.end(),
         [](Node a, Node b) -> bool { return a.following > b.following; }); // sorted by following field
    return vector<Node>(result.begin(), result.begin() + n); // return sorted vector
}

void Graph::politicalTendencyCalc(str Magazine) { // Computes the political tendency for all user. BFS run
    int node = ref.find(Magazine)->second; // Find node pos by id

    queue<Node> Q; // BFS queue
    set<str> visited; // visited set
    Node u = graph[node]; // Start node
    u.polPow = 200.0; // Initial polPow
    Q.push(u); // Insert u into queue
    visited.insert(graph[node].id); // mark u as visited

    // Coloring the graph
    while (!Q.empty()) { // While elements in queue
        u = Q.front(); // u = first inserted element

        Q.pop(); // extarct from queue
        for (auto i : u.followers) { // for all the children
            if (visited.find(i->id) == visited.end()) { // if the instance has not been visited yet
                i->politicalTendency[node] = u.polPow /
                                             2; // Assign half of the political power of his parent to the current political tendency
                i->polPow = u.polPow / 2; // And to his own political power
                Q.push(*i); // inert i to queue
                visited.insert(i->id); // mark i as visitied

            }

        }


    }


}

// A dummy sum func
double sum(vector<double> a) {
    double res = 0;
    for (double j : a) {
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
    for (Node i : graph) { // for every node in graph
        s = sum(i.politicalTendency); // sum his influences
        cout << " Political tendency " << i.id << ": ";
        for (double j : i.politicalTendency) { // for every component in his political tendency
            j = (j / s) * 100; // % of influence
            cout << j << "% ";
        }
        cout << endl;
    }
    return graph; // return the graph modified.

}

void Graph::DFSUtil(int pos, bool *visited) {
    visited[pos] = true;
    Node n = graph[pos];
    //cout << n.id << " --->";
    for (int i = 0; i < n.followers.size(); ++i) {
        if (!visited[n.followers[i]->pos]) {
            DFSUtil(n.followers[i]->pos, visited);
        }
    }
}

void Graph::fillOrder(int pos, bool *visited, stack<Node> &s) {
    visited[pos] = true;
    Node n = graph[pos];
    for (int i = 0; i < n.followers.size(); ++i) {
        if (!visited[n.followers[i]->pos]) {
            fillOrder(n.followers[i]->pos, visited, s);
        }
    }
    s.push(n);
}

int Graph::Kosaraju() { // Kosaraju
    stack<Node> s; // stack needed
    bool *visited = new bool[graph.size()];
    for (int i = 0; i < graph.size(); ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < graph.size(); ++i) {
        if (visited[i] == false)
            fillOrder(graph[i].pos, visited, s);
    }

    Graph T = this->transpose();

    for (int i = 0; i < graph.size(); ++i) {
        visited[i] = false;
    }
    int k = 0;
    while (!s.empty()) {
        Node v = s.top();

        s.pop();
        if (visited[v.pos] == false) {
            cout << v.id << " " << v.followers.size();
            T.DFSUtil(v.pos, visited);
            cout << endl;
            k++;
        }
    }
    return k;

}


Graph Graph::transpose() { // Compute the inverse graph
    Graph T;
    for (int i = 0; i < graph.size(); ++i) {
        T.graph.push_back(graph[i]);
        T.graph[i].following = 0;
        T.graph[i].followers.clear();
    }


    for (Node i : graph) {
        for (Node *j : i.followers) {
            T.graph[j->pos].followers.push_front(&T.graph[i.pos]);
        }
    }


    return T; //  return graph

}

void Graph::print() { // print graph


    for (auto i : graph) {
        cout << i.id << " --> ";
        for (auto j : i.followers) {
            cout << j->id << " --> ";

        }
    }

}

int Graph::size() { return graph.size(); }

void Graph::exportGraph(str path) {
    ofstream f(path + "/Origins.txt");
    for (auto i : graph) {
        for (auto j : i.followers) {
            f << i.pos;
            f << "\n";
        }
    }
    f.close();
    f.open(path + "/Destiny.txt");
    f << "\n";
    for (auto i : graph) {
        for (auto j : i.followers) {
            f << j->pos;
            f << "\n";
        }
    }
    f.close();
}

void Graph::computeStats() {
    int mixt = 0;
    bool *vis = new bool[graph.size()];

    for (int i = 0; i < graph.size(); ++i) {
        vis[i] = false;
    }
    int left = count_if(graph.begin(), graph.end(), [&mixt](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());
        if (max == a.politicalTendency[1] and max == a.politicalTendency[0]) {

            return true;
        }
        return max == a.politicalTendency[0] and max != a.politicalTendency[1] and max != a.politicalTendency[2]
               and max != a.politicalTendency[3];

    });
    int libert = count_if(graph.begin(), graph.end(), [&mixt](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());

        return max == a.politicalTendency[1] and max != a.politicalTendency[0] and max != a.politicalTendency[2]
               and max != a.politicalTendency[3];
    });
    int right = count_if(graph.begin(), graph.end(), [&mixt](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());
        if (max == a.politicalTendency[3] and max == a.politicalTendency[4]) {
            return true;
        }
        return max == a.politicalTendency[2] and max != a.politicalTendency[1] and max != a.politicalTendency[0]
               and max != a.politicalTendency[3];
    });
    int center = count_if(graph.begin(), graph.end(), [&mixt](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());

        return max == a.politicalTendency[3] and max != a.politicalTendency[1] and max != a.politicalTendency[2]
               and max != a.politicalTendency[0];
    });
    cout << "left: " << (double(left) / double(graph.size())) * 100 << "%." << endl;
    cout << "libertarian: " << (double(libert) / double(this->size())) * 100 << "%." << endl;
    cout << "right: " << (double(right) / double(this->size())) * 100 << "%." << endl;
    cout << "center: " << (double(center) / double(this->size())) * 100 << "%." << endl;
    mixt = this->size() - (left + right + libert + center);
    cout << "mixt: " << (double(mixt) / double(this->size()) * 100) << "%\n";

}

void Graph::exportTendencies(str path) {
    ofstream f(path + "/Tendencies.txt");
    for (auto i : graph) {
        f << i.politicalTendency[0];
        f << " ";
        f << i.politicalTendency[1];
        f << " ";
        f << i.politicalTendency[2];
        f << " ";
        f << i.politicalTendency[3];
        f << " ";
        f << "\n";
    }
}

void Graph::getGraphSize() {
    int content = sizeof(Graph);
    int graphS = sizeof(Node) * graph.size();
    int insider = 0;
    for (int i = 0; i < graph.size(); ++i) {
        insider += sizeof(Node *) * graph[i].followers.size();
    }

    cout << "Struct size: " <<  float (content + graphS + insider) / 1000000 << " MBs.\n";
}

Graph::~Graph() {

}