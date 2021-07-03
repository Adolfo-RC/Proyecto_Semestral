#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph tweet;
    tweet.insert("/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_users.csv",
                 "/home/eric/Maestria/I Semestre/FED&A/Tareas/Tarea 3/Proyecto final/twitter_connections.csv");

    return 0;
}
