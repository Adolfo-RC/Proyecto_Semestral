#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph tweet;
    tweet.insert("/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_users.csv",
                 "/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_connections.csv");

    auto k = tweet.topInfluenced(10);
    for (int i = 0; i < k.size(); ++i) {
        cout << i + 1 <<": " << k[i].id <<" - " <<k[i].following<< endl;
    }
    //tweet.print();

    return 0;
}
