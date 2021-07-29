// Métodos del grafo

#include "Graph.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

Graph::Graph() {} // Constructor.

void Graph::insert(str vertex, str junctions) {
// Inserta los datos de los datasets entregados en los nodos correspondientes y en el grafo.

    ifstream f; // Variable encargada del archivo.
    str read; // Variable de lectura en el archivo.
    f.open(vertex); // Lee el dataset de nombres.
    int i = 0; // Contador.
    int k, j; // Separadores.

    while (getline(f, read)) { 
    // Mientras el archivo siga teniendo lineas con texto.
        if (i == 0) { 
        // Se salta la primera linea, puesto que es la cabecera.
            i++;
            continue;
        }
        k = read.find(";"); // Encuentra el primer ";".
        j = read.find(";", read.find(";") + 1); // Busca el siguiente ";".
        str result(read.begin() + k + 1, read.begin() + j); // Se extrae el nombre de 
                                                            // usuario entre ambos ";".
        this->ref.insert(pair<str, int>(result, i - 1)); // Inserta el nombre y posición
                                                         // en tabla hash.
        this->graph.push_back({result, i - 1, 0, 0});   // Inserta el nodo en el grafo.
        graph[i - 1].politicalTendency.resize(4);    // En el nodo agranda el vector de 
                                                    // tendencia para las 4 posturas.
        graph[i - 1].politicalTendency = {0, 0, 0, 0}; // Se inician vacias.
        i++; // Pasa al siguiente usuario.
    }

    f.close(); // Cierra el documento.
    f.open(junctions); // Lee el dataset de conexiones.
    i = 0; // Reinicia el contador.

    while (getline(f, read)) { 
    // Mientras el archivo tenga lineas con texto.
        if (i == 0) {
        // Se omite el encabezado del dataset.
            i++;
            continue;
        }
        k = read.find(";"); // Busca el primer separador ";".
        str followee(read.begin(), read.begin() + k); // Primer dato es considerado seguido.
        str follower(read.begin() + k + 1, read.end()); // Segundo dato es considerado seguidor.
        umap::iterator it = ref.find(followee); // Busca en la tabla la posición del seguido.
        umap::iterator it2 = ref.find(follower); // Busca también la posición del seguidor
        graph[it->second].followers.push_front(&graph[it2->second]); 
        // Inserta este en la lista de seguidores del nodo correspondiente.
        i++; // Avanza a la siguiente linea.
    }

    f.close(); // Cierra el documento.
}

vector<Node> Graph::topInfluencer(int cant) { 
// Entrega los n usuarios con más seguidores (Influenciadores).

    vector<Node> result = graph; // Se trabaja con el grafo completo
    auto comp = [](Node a, Node b) -> bool { // Se crea una función comparadora.
        return a.followers.size() > b.followers.size();}; // Si un nodo tiene más seguidores que 
                                                          // el otro retorna verdadero.
    sort(result.begin(), result.end(), comp); // Se ordena utilizando la función comparadora.
    return vector<Node>(result.begin(), result.begin() + cant); // Retorna el grafo ordenado
}

vector<Node> Graph::topInfluenced(int n) { 
// Entrega los n usuarios con más personas seguidas (Influyentes).

    for (Node i : graph) {
    // Para cada nodo dentro del grafo.
        for (auto j: i.followers) {
            j->following++; // Si el usuario aparece en otras listas se suma en su variable
                            // following para llevar un conteo.
        }
    }
    vector<Node> result = graph; // Luego, con el grafo completo.
    sort(result.begin(), result.end(), // Se ordena según la cantidad de cuentas que el usuario siga.
         [](Node a, Node b) -> bool { return a.following > b.following; }); // De mayor a menor.
    return vector<Node>(result.begin(), result.begin() + n); // Retorna el grafo ordenado.
}

void Graph::politicalTendencyCalc(str Magazine) { 
// Calcula la tendencia politica según el noticiero que se ingrese mediante BFS.

    int node = ref.find(Magazine)->second; // Se busca la posición en la tabla.
    queue<Node> Q; // Cola de orden.
    set<str> visited; // Set con usuarios visitados.
    Node u = graph[node]; // Se toma la posición como nodo inicial.
    u.polPow = 200.0; // Se entrega un valor igual a 200.
    graph[node].politicalTendency[node] = 200.0; // Se inserta este valor en el nodo.
    Q.push(u); // Se inserta el nodo en la lista de orden.
    visited.insert(graph[0].id); 
    visited.insert(graph[1].id);
    visited.insert(graph[2].id);
    visited.insert(graph[3].id);
    // Se marcan los 4 noticieros como visitados incialmente.

    // Utilizando BFS para recorrer el grafo.
    while (!Q.empty()) { // Mientras existan elementos en la lista.
        u = Q.front(); // Toma al primer elemento.
        Q.pop(); // Lo saca de la lista.
        for (auto i : u.followers) { // Considera los seguidores de la cuenta
            if (visited.find(i->id) == visited.end()) { 
                // Si el nodo no ha sido visitado previamente.
                i->politicalTendency[node] = u.polPow / 2; 
                // Se le asigna la mitad del valor a sus seguidores.
                i->polPow = u.polPow / 2; // Y la mitad del valor original a el mismo.
                Q.push(*i); // Se insertan los seguidores a la lista de orden.
                visited.insert(i->id); // Se marca este como visitado.
            }
        }
    }
}

double sum(vector<double> a) {
// Función de suma por iterador.
    double res = 0;
    for (double j : a) {
        res += j;
    }
    return res;
}

vector<Node> Graph::influenceColorMap() { 
// Función encargada de colorear el grafo según la tendencia política.
    politicalTendencyCalc("Cooperativa"); // Izquierda
    politicalTendencyCalc("soyvaldiviacl"); // Derecha
    politicalTendencyCalc("latercera"); // Centro
    politicalTendencyCalc("elmostrador"); // Libertario

    double s = 0; // Variable encargada de la suma.
    for (Node i : graph) {
    // Para cada nodo del grafo.
        s = sum(i.politicalTendency); // Se suman sus influencias.
        cout << " Political tendency " << i.id << ": ";
        // Se imprime los porcentajes del nombre del usuario.
        for (double j : i.politicalTendency) { 
            // Para cada componente en su vector de tendencia política.
            j = (j / s) * 100; // Se calcula el porcentaje.
            cout << j << "% "; // Se imprime junto al nombre.
        }
        cout << endl;
    }
    return graph; // Retorna el grafo modificado.
}

void Graph::DFSUtil(int pos, bool *visited) { 
// DFS para recorrer los arcos entre los nodos.
    visited[pos] = true; // Se indica el primer nodo como visitado.
    Node n = graph[pos];// Se crea un nuevo nodo donde se guarda el grafo.
    cout << n.id << " --->"; // Se imprime el usuario.
    for (int i = 0; i < n.followers.size(); ++i) { 
        // Todos los nodos adyacentes a este.
        if (!visited[n.followers[i]->pos]) { // Si no ha sido visitado.
            DFSUtil(n.followers[i]->pos, visited);
            // Se llama recursivamente con este nuevo nodo.
        }
    }
}

void Graph::fillOrder(int pos, bool *visited, stack<Node> &s) {
// Rellenado de un stack con Kosaraju.
    visited[pos] = true; // Se indica el usuario de esta posición como visitado.                                          
    Node n = graph[pos]; // Se crea un nuevo nodo.
    for (int i = 0; i < n.followers.size(); ++i) {           
    // Con la totalidad de seguidores. 
        if (!visited[n.followers[i]->pos]) {      
        // Si no han sido visitados.          
            fillOrder(n.followers[i]->pos, visited, s);  
            // Se asigna el nuevo nodo como la posición.
        }
    }
    s.push(n); // Cuando acaba el DFS, se ingresa todo el nuevo nodo al stack.
}

int Graph::Kosaraju() { 
// Detección de conjuntos fuertemente conexos utilizando Kosaraju.

    stack<Node> s; // Se necesita de un stack.
    bool *visited = new bool[graph.size()]; // Se crea un arreglo donde se
                                            // indican los nodos visitados.
    for (int i = 0; i < graph.size(); ++i) {
    // Para la totalidad de los nodos.
        visited[i] = false; // Se indica que no se han visitado.
    }

    for (int i = 0; i < graph.size(); ++i) {
    // Para la totalidad de los nodos.
        if (visited[i] == false) {
            fillOrder(graph[i].pos, visited, s); // Llena el stack con los
                                                // nodos no visitados.
        }
    }

    Graph T = this->transpose(); // Se aplica inversión al grafo.

    for (int i = 0; i < graph.size(); ++i) {
    // Para la totalidad de los nodos.
        visited[i] = false; // Se vuelve al estado original.
    }
    int k = 0; // Se crea un contador.
    while (!s.empty()) { 
    // Mientras existan elementos en el stack.
        Node v = s.top(); // Se obtiene el elemento superior del stack.
        s.pop(); // Se libera.
        if (visited[v.pos] == false) {
        // Si este nodo no fue visitado.
            cout << "SCC: ";
            T.DFSUtil(v.pos, visited); 
            // Se aplica la búsqueda con el nodo inverso.
            cout << endl;
            k++;
        }
    }
    return k;
    // Regresa la cantidad de conjuntos fuertemente conexos.
}

Graph Graph::transpose() { 
// Invierte el grafo para uso en Kosaraju.
    Graph T; // Se crea un nuevo grafo.
    for (int i = 0; i < graph.size(); ++i) {
        T.graph.push_back(graph[i]); // Se copia el grafo
        T.graph[i].following = 0; // Sin seguidores
        T.graph[i].followers.clear(); // Sin usuarios seguidos.
    }

    for (Node i : graph) {
        for (Node *j : i.followers) {
            T.graph[j->pos].followers.push_front(&T.graph[i.pos]);
            // Ingresamos los previos seguidores como seguidos.
        }
    }

    return T; // Retornamos el nuevo grafo.
}

void Graph::print() { 
// Se encarga de mostrar las conexiones del grafo.
    for (auto i : graph) {
        cout << i.id << " --> ";
        for (auto j : i.followers) {
            cout << j->id << " --> ";

        }
    }

}

int Graph::size() { return graph.size(); } // Retorna la cantidad de nodos.

void Graph::exportGraph(str path) { // Exporta el grafo a un archivo de texto
    ofstream f(path + "/Origins.txt");
    for (auto i : graph) {
        for (auto j : i.followers) {
            f << i.pos;
            f << "\n";
        }
    }
    f.close();
    f.open(path + "/Destiny.txt");
    f << "\n";
    for (auto i : graph) {
        for (auto j : i.followers) {
            f << j->pos;
            f << "\n";
        }
    }
    f.close();
}

void Graph::computeStats() {
// Cálculo de la totalidad de la influencia política.
    int mix = 0; // Variable donde se almacenarán aquellos usuarios con igual cantidad de influencia máxima.
    int left = count_if(graph.begin(), graph.end(), [](Node a) -> bool { 
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end()); 
        // Se extrae la tendencia política más grande entre el vector.
        return max == a.politicalTendency[0] && max != a.politicalTendency[1] && max != a.politicalTendency[2]
             && max != a.politicalTendency[3]; // Regresa verdadero si domina la postura izquierda.
    });

    int libert = count_if(graph.begin(), graph.end(), [](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());
        return max == a.politicalTendency[3] && max != a.politicalTendency[0] && max != a.politicalTendency[2]
                && max != a.politicalTendency[1]; // Del mismo modo, regresa verdadero si domina la postura liberal.
    });

    int right = count_if(graph.begin(), graph.end(), [](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());
        return max == a.politicalTendency[1] && max != a.politicalTendency[2] && max != a.politicalTendency[0]
               && max != a.politicalTendency[3]; // Del mismo modo, regresa verdadero si domina la postura derechista.
    });

    int center = count_if(graph.begin(), graph.end(), [](Node a) -> bool {
        double max = *max_element(a.politicalTendency.begin(), a.politicalTendency.end());
        return max == a.politicalTendency[2] && max != a.politicalTendency[1] && max != a.politicalTendency[3]
               && max != a.politicalTendency[0]; // Del mismo modo, regresa verdadero si domina la postura central.
    });
    
    cout << "left: " << (double(left) / double(graph.size())) * 100 << "%." << endl;
    cout << "libertarian: " << (double(libert) / double(this->size())) * 100 << "%." << endl;
    cout << "right: " << (double(right) / double(this->size())) * 100 << "%." << endl;
    cout << "center: " << (double(center) / double(this->size())) * 100 << "%." << endl;
    mix = this->size() - (left + right + libert + center);
    cout << "mix: " << (double(mix) / double(this->size()) * 100) << "%\n";
    // Muestra los porcentajes de las tendencias en porcentaje sobre el total de usuarios.
}

void Graph::exportTendencies(str path) {
// Exporta las tendencias de los nodos a un archivo de texto.
    ofstream f(path + "/Tendencies.txt");
    for (auto i : graph) {
        f << i.politicalTendency[0];
        f << " ";
        f << i.politicalTendency[1];
        f << " ";
        f << i.politicalTendency[2];
        f << " ";
        f << i.politicalTendency[3];
        f << " ";
        f << "\n";
    }
}

void Graph::getGraphSize() { 
// Calcula el tamaño del grafo total en MBs
    int content = sizeof(Graph); // Incluye todo el contenido del grafo
    int graphS = sizeof(Node) * graph.size(); // Esoacio utilizado por nodos
    int insider = 0; // Espacio consumido por los arcos entre nodos
    for (int i = 0; i < graph.size(); ++i) {
        insider += sizeof(Node *) * graph[i].followers.size(); 
        // Esto se logra contando la cantidad de seguidores.
    }

    cout << "Struct size: " <<  float (content + graphS + insider) / 1000000 << " MBs.\n"; 
    // Retorna la suma total en MBs
}

Node Graph::returnNode(int n) {
// Regresa el nodo del grafo por posición
    return graph[n];
}

Node Graph::returnNode(str id) {
// Regresa el nodo del grafo por nombre de usuario.
    return graph[ref.find(id)->second];
}

int Graph::findIsland() {
// Busca si existe algun nodo que no siga a nadie.
    this->topInfluenced(0);
    uint k;
    for (Node i : this->graph){
        if (i.following == 0){
            k++;
        }
    }
    return k; // Retorna cantidad.
}

Graph::~Graph() {}; // Destructor.