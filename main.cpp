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
    // Se calcula la influencia de los noticieros en los usuarios.
    t0 = clock();
    vector<Node> k = tweet.influenceColorMap();
    tf = clock();
    cout << "\n\nTime to calculate influence: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;
    // Tiempo transcurrido.

    cout << "Top 10 Influenced\n";
    // Se calculan los 10 usuarios más influenciados.
    t0 = clock();
    auto z = tweet.topInfluenced(10);
    tf = clock();
    cout << "\n\nTime to calculate influenceds: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;
    // Tiempo transcurrido.

    for (auto i : z){
    // Se imprime los nombres y la cantidad de gente que siguen.
        cout << i.id << " " << i.following << endl;
    }

    cout << "Top 10 Influencers\n";
    // Se calculan los 10 usuarios más influyentes.
    t0 = clock();
    auto y = tweet.topInfluencer(10);
    tf = clock();
    cout << "\n\nTime to calculate influencers: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;
    // Tiempo transcurrido.

    for (auto i : y){
    // Se imprimen los nombres y la cantidad de gente que los siguen.
        cout << i.id << " " << i.followers.size() << endl;
    }

    cout << "SCC Detection\n";
    // Se calculan los conjuntos fuertemente conexos mediante Kosaraju.
    t0 = clock();
    int x = tweet.Kosaraju();
    tf = clock();
    cout << "\n\nTime to calculate influence: " << (tf - t0) / CLOCKS_PER_SEC << endl << endl;
    // Tiempo transcurrido.

    cout << endl << endl << " Number of SCCs"<< x << endl;
    // Cantidad de componentes fuertemente conexas incluyendo singularidades.

    cout << "Stats\n";
    // Porcentajes totales de la influencia de los usuarios.
    tweet.computeStats();

    cout << "Graph size\n";
    // Tamaño total del grafo.
    tweet.getGraphSize();
    
    return 0; // Fin.
}
