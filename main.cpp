#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph tweet;
    tweet.insert("/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_users.csv",
                 "/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_connections.csv");
    auto k = tweet.topInfluencer(5);

    for (auto i : k){
        cout << i.first << " ---- " << i.second << endl;
    }
    return 0;
}
