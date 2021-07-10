#include <iostream>
#include "Graph.h"
#include <stdio.h>
#include <filesystem>

// Idea taked from stackOverflow to get current path. Based on compiler's headers
#ifdef WINDOWS  // If Windows OS is detected
    #include <direct.h> // Include this
    #define GetCurrentDir _getcwd
#else // Else (a Unix vbased SO)
    #include <unistd.h> // Include the equivalent
    #define GetCurrentDir getcwd

#endif




using namespace std;



int main() {

    char currentPath [FILENAME_MAX]; // char buffer to save current path
    GetCurrentDir(currentPath, sizeof (currentPath)); // getcwd
    str strCurrentPath = currentPath; // make a string


    Graph tweet;
    tweet.insert(strCurrentPath + "/twitter_users.csv",
                 strCurrentPath + "/twitter_connections.csv");


    cout << "Influence by components\n";
    vector<Node> k = tweet.influenceColorMap();
    cout << "Top 10 Influenced\n";
    auto z = tweet.topInfluenced(10);
    for (auto i : z){
        cout << i.id << " " << i.following << endl;
    }
    cout << "Top 10 Influenced\n";
    auto y = tweet.topInfluencer(10);
    for (auto i : y){
        cout << i.id << " " << i.followers.size() << endl;
    }
    cout << "SCC Detection\n";
    int x = tweet.Kosaraju();

    cout << endl << endl << " Number of SCCs"<< x << endl;
    cout << "Stats\n";
    tweet.computeStats();

    cout << "Graph size\n";
    tweet.getGraphSize();


    return 0;
}
