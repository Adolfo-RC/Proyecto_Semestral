/*
 * Claudio, este es el proyecto. Aqui te acoto las ideas fdtles.
 *  Creacion del grafo:
 *      El grafo sigue la siguiente estructura, es un vector de nodos, cada nodo es una estructura con la siguiente forma:
 *          str id: Usr name
 *          int pos: posicion dentro del grafo
 *          following: numero usuarios seguidos por el nodo. se computa con los influenciados
 *          followers: double ended list de punteros a nodos, de esta forma cada seguidor apunta directamente al nodo que representa
 *          polPow : poder politico de cada nodo. Te lo explico mas adelante.
 *          tendencias: un vector con las componentes de tendencias politicas
 *
 *      la clase grafo ademas contiene una tabla hash ref que sirve para buscar la posicion dentro del grfo a partir del id de usuario.
 *
 *   Tendencia politica:
 *      Habiamos hablado de un kruskal pero eso implica un grafo ponderado que no es el caso. Algoritmicamente lo enfoque como un problema de coloreo. Un recorrido BFS de esta forma:
 *
 *          Se le asigna a cada revista un poder politico de 200
 *          se realiza el bfs donde cada hijo toma, para la corriente politica defindida por la revista, la mitad del poder de su padre.
 *          De esta manera la influencia es una funcion de la cercania del nodo a la revista en el arbol de cobertura generado por el BFS
 *          Finalmente se realiza el recorrido para cada revista
 *          Y se halla el porciento de cada componente con respecto al total de cada nodo.
 *
 *    Componentes conexas OJO:
 *      Implemente un Kosaraju corriente, de alguna manera encuentra un grafo conexo completamente (una sola componente)
 *      Creo que ser'ia bueno aplicar la tecnica del pato de goma aqui, revisa bien la implementacion y, si tienes contacto con algunos de nuestros compa;eros alla, preguntales
 *      no se si Martita o Carlos nos puedan ayudar. Ese resultado no me convence :(
 *
 *    Ya, lo otro es bastante intuitivo.
 *
 *    De mas esta decirte que cambies todo lo que quieras y que cualquier duda me esribas.
 *
 */

#ifndef PROYECTO_FINAL_GRAPH_H
#define PROYECTO_FINAL_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <set>
#include <stack>

using namespace std;
//namesppcese to bue used for typename simplification
using uint = unsigned int;
using str = string;
using umap = unordered_map<str, int>;

// Cointainer node struct
struct Node {
    str id; // ID field
    int pos;
    int following;
    double polPow;
    deque<Node *> followers;
    vector<double> politicalTendency; // vector of political tendency with 4 components (1 for each tendency)

};


class Graph {
private:
    umap ref; // hash table to associate the ID field with the position in the list
    //unordered_map<int, str> inverse_ref; // From position to ID
    vector<Node> graph; //adjacency list
    void politicalTendencyCalc(str Magazine);

    void recursiveDFS(Node n, set<str> *vis, stack<Node> *s);

    Graph transpose();

    void insert(Node, Node);

public:
    Graph(); // Class constructor
    void insert(str vertex, str junctions); // insert in graph
    void insert(str node);

    void insertP(str source, str dest);

    void print(); // print graph
    vector<Node> topInfluencer(int n);

    vector<Node> topInfluenced(int n);

    vector<Node> influenceColorMap();

    void recursiveDFS(Node, set<str> *);

    void Kosaraju();

    void exportGraph();

    void exportTendencies();

    void computeStats();

    int size();

    Node returnNode(int n);

    ~Graph(); // class destructor

};


#endif //PROYECTO_FINAL_GRAPH_H
