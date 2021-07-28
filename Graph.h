// Cabecera de la estructura nodal y la clase grafo.

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

using uint = unsigned int; 
using str = string;
using umap = unordered_map<str, int>;

// Estructura Nodo.
struct Node {
    str id; // Nombre de usuario.
    int pos; // Posición en el dataset.
    int following; // Cantidad de personas que sigue el usuario.
    double polPow; // Tendencia política valor numérico.
    deque<Node *> followers; // Lista de seguidores como nodos.
    vector<double> politicalTendency; 
    // Vector que mantiene las 4 posturas políticas con sus propios valores.
};

// Clase Grafo.
class Graph {
private:
    umap ref; // Tabla hash que asocia nombre de usuario con posición.
    vector<Node> graph; // Vector de adyacencia entre nodos.

    void politicalTendencyCalc(str Magazine); 
    // Función que añade el valor de la tendencia política respectiva al noticiero y a 
    // la posicion del seguidor en el grafo.

    void DFSUtil (int n, bool visited []);
    // Función que realiza la busqueda por profundidad necesaria para Kosaraju.

    void fillOrder(int n, bool visited [], stack<Node> &s);
    // Función que rellena la lista de nodos para Kosaraju.

    Graph transpose(); // Invierte los nodos del grafo.

    void insert(Node, Node); // Inserta los nodos a otros nodos.

public:
    Graph(); // Constructor.
    ~Graph(); // Destructor.

    void insert(str vertex, str junctions); // Inserta al grafo nodos y arcos.
    void insert(str node); // Inserta al grafo nodos.

    void print(); // Imprime el grafo.
    
    vector<Node> topInfluencer(int n); // Entrega los "n" usuarios con más seguidores.

    vector<Node> topInfluenced(int n); // Entrega los "n" usuarios que siguen a más cuentas.

    vector<Node> influenceColorMap(); // Entrega un arreglo porcentual de la influencia 
                                      // política de cada usuario.

    int Kosaraju(); // Algoritmo de Kosaraju que entrega las componentes fuertemente conexas.

    void exportGraph(str path); // Exporta el grafo como archivo de texto.

    void exportTendencies(str path); // Exporta las tendencias políticas como archivo de texto.

    void computeStats(); // Calcula la totalidad de la influencia política entre los usuarios.

    int size(); // Entrega la cantidad de nodos.

    Node returnNode(int n); // Entrega un nodo según su posición.
    Node returnNode(str id); // Entrega un nodo según su nombre de usuario.

    void getGraphSize(); // Calcula el tamaño total del grafo.

    int findIsland(); // Identifica nodos que no tengan arcos.
};

#endif //PROYECTO_FINAL_GRAPH_H
