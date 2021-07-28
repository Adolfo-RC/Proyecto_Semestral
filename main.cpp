// Programa principal encargado del experimento del proyecto.
// Eric Primelles & Claudio Rioseco 2021-1.

#include <iostream>
#include "Graph.h"
#include <stdio.h>
#include <ctime>

// Idea extraía de StackOverflow para leer archivos desde directorio.
#ifdef _WIN32 // Si el sistema operativo es Windows:
    #include <direct.h> // Incluye esta libreria.
    #define GetCurrentDir _getcwd
#else // Si el sistema operativo es basado en Linux/Unix:
    #include <unistd.h> // Incluye esta libreria
    #define GetCurrentDir getcwd

#endif

using namespace std; // Utilizando el espacio estandar.

int main() {

    char currentPath [FILENAME_MAX]; // Variable almacenadora del directorio actual.
    GetCurrentDir(currentPath, sizeof (currentPath)); // Se obtiene el directorio.
    str strCurrentPath = currentPath; // Se crea un string con el directorio actual.

    // Se da inicio a la estructura grafo para almacenar los usuarios.
    Graph tweet; 
    double t0, tf; // Se crean relojes para medir el tiempo transcurrido entre método.
    t0 = clock(); // Inicia el contador.

    tweet.insert(strCurrentPath + "/twitter_users.csv",
                 strCurrentPath + "/twitter_connections.csv");
    // Se ingresan al método de inserción ambos juegos de datos.

    tf = clock(); // Finaliza el contador.
    cout << "Time to insert: " << (tf - t0)/ CLOCKS_PER_SEC << endl << endl;
    // Se calcula la diferencia sobre segundos para obtener el tiempo transcurrido.
    
    cout << "Influence by components\n";
    t0 = clock();
    vector<Node> k = tweet.influenceColorMap();
    tf = clock();
    cout << "\n\nTime to calculate influence: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;

    cout << "Top 10 Influenced\n";
    t0 = clock();
    auto z = tweet.topInfluenced(10);
    tf = clock();
    cout << "\n\nTime to calculate influenceds: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;

    for (auto i : z){
        cout << i.id << " " << i.following << endl;
    }
    cout << "Top 10 Influenced\n";
    t0 = clock();
    auto y = tweet.topInfluencer(10);
    tf = clock();
    cout << "\n\nTime to calculate influencers: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;

    for (auto i : y){
        cout << i.id << " " << i.followers.size() << endl;
    }
    cout << "SCC Detection\n";
    t0 = clock();
    int x = tweet.Kosaraju();
    tf = clock();
    cout << "\n\nTime to calculate influence: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;

    cout << endl << endl << " Number of SCCs"<< x << endl;
    cout << "Stats\n";
    tweet.computeStats();

    cout << "Graph size\n";
    tweet.getGraphSize();


    return 0;
}
