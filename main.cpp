#include <iostream>
#include "Graph.h"
#include <stdio.h>
#include <filesystem>

#ifdef WINDOWS // Idea taked from stackOverflow to get currentpath
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd

#endif




using namespace std;



int main() {

    char currentPath [FILENAME_MAX];
    GetCurrentDir(currentPath, sizeof (currentPath));
    str strCurrentPath = currentPath;


    Graph tweet;
    tweet.insert(strCurrentPath + "/twitter_users.csv",
                 strCurrentPath + "/twitter_connections.csv");



    //vector<Node> k = tweet.influenceColorMap();
    //auto z = tweet.topInfluenced(tweet.size());
    //tweet.exportGraph();
    //int x = tweet.Kosaraju();
    //cout << endl << endl << x << endl;
    //tweet.print();

    tweet.getGraphSize();


    return 0;
}
