#include "estructura.h"

using namespace std;

Grafo::Grafo(char ini,char fini,vector<char> nombreVerts,vector<int> valueVerts,vector<char>vertice1,vector<char>vertice2,vector<int> valueArist){
    inicio = ini;
    fin = fini;
    nombreVertices = nombreVerts;
    valueVertices = valueVerts;
    for (int i = 0; i < vertice1.size(); i++) {
        arista arista;
        arista.start = vertice1[i];
        arista.end = vertice2[i];
        arista.cost = valueArist[i];
        aristas.push_back(arista);
    }
}
Grafo::~Grafo(){
}
char Grafo::getInicio() {
    return inicio;
}
char Grafo::getFin() {
    return fin;
}
int Grafo::heuristic(char actual, char objetivo) {
    return 0;
}
vector<char> Grafo::getNombreVertices() {
    return nombreVertices;
}
vector<int> Grafo::getValueVertices() {
    return valueVertices;
}
vector<arista> Grafo::getAristas() {
    return aristas;
}
void Grafo::printGrafo(Grafo grafo){
    vector<char> vertices = grafo.getNombreVertices();
    vector<int> valores = grafo.getValueVertices();
    cout << "Vertices: ";
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i] << " (" << valores[i] << ")";
        if (i != vertices.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    // Imprimir aristas y pesos
    vector<arista> aristas = grafo.getAristas();
    cout << "Aristas" << endl;
    for (int i = 0; i < aristas.size(); i++) {
        cout << aristas[i].start << " -> " << aristas[i].end << " (" << aristas[i].cost << ")" << endl;
    }
}
void Grafo::printRuta(vector<char> &ruta,unordered_map<char,int> &expanciones) {
    int totalCost = 0;

    cout << "Output:" << endl;
    for (size_t i = 0; i < ruta.size(); i++) {
        cout << ruta[i];
        if (i < ruta.size() - 1) {
            cout << " → ";
        }

        if (i > 0) {
            for (arista arista : aristas) {
                if (arista.start == ruta[i - 1] && arista.end == ruta[i]) {
                    totalCost += arista.cost;
                    break;
                }
            }
        }
    }

    cout << endl << "Costo: " << totalCost << endl;

    for (const auto &item : expanciones) {
        cout<<"expanciones de: " << item.first << ": " << item.second  << endl;
    }
}
void Grafo::dfs() {
    srand(time(0)); // Inicializa la semilla para la generación de números aleatorios
    stack<char> pila; //para guardar los nodos no explorados
    vector<char> visitados; //almacena los nodos ya visitados
    vector<char> ruta; //para guardar la ruta encontrada
    vector<char> sucesores; //para ir guardando los sucesores correspondientes.
    unordered_map<char, int> expanciones; //para guardar la cantidad de veces que se expandio un nodo.
    pila.push(inicio);
    while (!pila.empty()) {
        char actual = pila.top();
        pila.pop();
        if (find(visitados.begin(), visitados.end(), actual) == visitados.end()) { //verifica si actual NO fue visitado.
            visitados.push_back(actual);
            ruta.push_back(actual); 
            //si NO fue visitado se visita y se agrega a la ruta.
            if (actual == fin) { //condicion de salida.
                break;
            }
            expanciones[actual] = 0; //inicializa el contador del nodo visitado en 0
            for (size_t i = 0; i < aristas.size(); ++i) { //Se recorren las aristas y si comienza con el nodo actual y el nodo objetivo
                arista arista = aristas[i];                //no ha sido visitado se agrega a la lista de sucesores.
                if (arista.start == actual && find(visitados.begin(), visitados.end(), arista.end) == visitados.end()) {
                    sucesores.push_back(arista.end);
                }
            }
            shuffle(sucesores.begin(), sucesores.end(), default_random_engine(rand())); //se desordenan los sucesores para que sea aleatorio
            for (size_t i = 0; i < sucesores.size(); ++i) { //se recorren los sucesores del nodo actual.
                char sucesor = sucesores[i];
                pila.push(sucesor); //se agregan los sucesores a la pila 
                expanciones[actual]++; //se aumenta el contador de expancion del nodo actual.
            }
        }
        sucesores.clear();
    }
    cout<<"Resultado DFS"<<endl;
    printRuta(ruta, expanciones);
}
void Grafo::costoUniforme(){
    unordered_map<char, char> nodoAnterior; // para almacenar el nodo anterior en la ruta optima de cada nodo en el grafo
    unordered_map<char, int> costeAcumulado; //para almacenar el coste minimo acumulado para llegar desde el nodo inicial a cada modo en el grafo
    unordered_map<char, int> expanciones;  //para guardar la cantidad de veces que se expandio un nodo.
    vector<char> ruta; //para guardar la ruta encontrada
    auto compare = [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second > b.second;
    };// Funcion local que permite ordenar elementos en una cola de prioridad
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(compare)> frontera(compare); //se inicializa la cola de prioridad
    //Se define una cola de prioridad llamada frontera 
    //lo que almacena pair<char, int>
    //lo guarda en un vector<pair<char, int>>
    //decltype(compare) indica que esta cola de prioridad usara la funcion local compare para ordenarse
    frontera.push(make_pair(inicio, 0)); //nodo inicial agregado a la frontera
    nodoAnterior[inicio] = inicio; //nodo anterior pero como es el inicio queda el mismo.
    costeAcumulado[inicio] = 0; //0 ya que no se ha acumulado aun
    while (!frontera.empty()) {
        char actual = frontera.top().first; // se toma el nodo con menor valor.
        frontera.pop(); // se borra el nodo
        if (actual == fin) { //condicion de salida
            break;
        }
        expanciones[actual] = 0; //inicializar contador de expanciones
        for (arista arista : aristas) { //recorre las aristas del grafo
            if (arista.start == actual) { //si corresponde al nodo actual
                int costeNuevo = costeAcumulado[actual] + arista.cost; //se actualiza el coste
                if (costeAcumulado.find(arista.end) == costeAcumulado.end() || costeNuevo < costeAcumulado[arista.end]) {
                // si el nodo objetivo no se ha visitado o el nuevo coste es menor que el actual acumulado   
                    costeAcumulado[arista.end] = costeNuevo; //actualiza coste
                    frontera.push(make_pair(arista.end, costeNuevo)); //agrega el nodo final a la frontera con el coste asociado.
                    nodoAnterior[arista.end] = actual; //define el nodo anterior del nuevo nodo como el que ya se revisaba.
                    expanciones[actual]++;
                }
            }
        }
    }
    //contruccion ruta e imprimir resultado.
    char actual = fin;
    while (actual != inicio) {
        ruta.push_back(actual);
        actual = nodoAnterior[actual];
    }
    ruta.push_back(inicio);
    reverse(ruta.begin(), ruta.end());
    cout<<"Resultado Coste Uniforme"<<endl;
    printRuta(ruta, expanciones);
}
void Grafo::greedy(){
    unordered_map<char, char> nodoAnterior;
    unordered_map<char, int> costeAcumulado;
    unordered_map<char, int> expanciones;
    vector<char> ruta;
    //mismas estructuras que costeUniforme
    auto compare = [this](const pair<char, int>& a, const pair<char, int>& b) {
        return heuristic(a.first, fin) > heuristic(b.first, fin);
    };
    //solo se considera la mejor heuristica 
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(compare)> frontera(compare);
    frontera.push(make_pair(inicio, 0));
    nodoAnterior[inicio] = inicio;
    costeAcumulado[inicio] = 0;
    while (!frontera.empty()) {
        char actual = frontera.top().first;
        frontera.pop();
        if (actual == fin) {
            break;
        }
        expanciones[actual] = 0;
        for (arista arista : aristas) {
            if (arista.start == actual) {
                int costeNuevo = costeAcumulado[actual] + arista.cost;
                if (costeAcumulado.find(arista.end) == costeAcumulado.end() || costeNuevo < costeAcumulado[arista.end]) {
                    costeAcumulado[arista.end] = costeNuevo;
                    frontera.push(make_pair(arista.end, heuristic(arista.end, fin)));
                    nodoAnterior[arista.end] = actual;
                    expanciones[actual]++;
                }
            }
        }
    }
    char actual = fin;
    while (actual != inicio) {
        ruta.push_back(actual);
        actual = nodoAnterior[actual];
    }
    ruta.push_back(inicio);
    reverse(ruta.begin(), ruta.end());
     cout<<"Resultado greedy"<<endl;
    printRuta(ruta, expanciones);
}
void Grafo::estrella(){
    unordered_map<char, char> nodoAnterior;
    unordered_map<char, int> costeAcumulado;
    unordered_map<char, int> expanciones;
    vector<char> ruta;
    //mismas estructuras que costeUniforme
    auto compare = [this](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second + heuristic(a.first, fin) > b.second + heuristic(b.first, fin);
    };
    //ahora la funcion local considera la suma del coste acumulado y la heuristica
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(compare)> frontera(compare);
    frontera.push(make_pair(inicio, 0));
    nodoAnterior[inicio] = inicio;
    costeAcumulado[inicio] = 0;
    while (!frontera.empty()) {
        char actual = frontera.top().first;
        frontera.pop();
        if (actual == fin) {
            break;
        }
        expanciones[actual] = 0;
        for (arista arista : aristas) {
            if (arista.start == actual) {
                int costeNuevo = costeAcumulado[actual] + arista.cost;
                if (costeAcumulado.find(arista.end) == costeAcumulado.end() || costeNuevo < costeAcumulado[arista.end]) {
                    costeAcumulado[arista.end] = costeNuevo;
                    frontera.push(make_pair(arista.end, costeNuevo));
                    nodoAnterior[arista.end] = actual;
                    expanciones[actual]++;
                }
            }
        }
    }
    char actual = fin;
    while (actual != inicio) {
        ruta.push_back(actual);
        actual = nodoAnterior[actual];
    }
    ruta.push_back(inicio);
    reverse(ruta.begin(), ruta.end());
    cout<<"Resultado A*"<<endl;
    printRuta(ruta, expanciones);
}
