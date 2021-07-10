#include <iostream>
#include "Graph.h"
#include <filesystem>



using namespace std;



int main() {
    Graph tweet;
    tweet.insert("/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_users.csv",
                 "/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_connections.csv");

    ifstream f;

    if (!f.is_open()) cout<<"LLLLL";

    //vector<Node> k = tweet.influenceColorMap();
    //auto z = tweet.topInfluenced(tweet.size());
    //tweet.exportGraph();
    //int x = tweet.Kosaraju();
    //cout << endl << endl << x << endl;
    //tweet.print();

    return 0;
}
