#include "estructura.h"
#include <iostream>
#include <fstream>

using namespace std;
//guarda las primeras dos lineas en dos char
//de la tercera a la decima por cada linea guarda la primera letra encontrada en un vector<char> y el primer numero encontrado en un vector<int>, 
//luego las lineas restantes guarda por cada linea la primera letra encontrada en un vector<char>, la segunda letra encontrada en otro vector<char> 
//y luego el primer numero encontrado en un vector<int>
int main() {
    ifstream file("entrada.txt");  // Abrir archivo de texto
    char inicio;
    char fin;
    file >> inicio >> fin;  // Leer primera y segunda linea
    vector<char> vertices;
    vector<int> heuristicas;
    for (int i = 0; i < 8; i++) {  // Leer tercera a décima línea
        char key;
        int value;
        file >> key >> value;
        vertices.push_back(key);
        heuristicas.push_back(value);
    }
    vector<arista> aristas;
    vector<char> vertice1;
    vector<char> vertice2;
    vector<int> valueArista;
    char start;
    char end;
    int cost;
    while (file >> start >> end >> cost) { // Leer líneas restantes
        arista arista;
        arista.start = start;
        arista.end = end;
        arista.cost = cost;
        vertice1.push_back(start);
        vertice2.push_back(end);
        valueArista.push_back(cost);
        aristas.push_back(arista);
    }
    file.close();  // Cerrar archivo de texto
    Grafo grafo (inicio, fin, vertices, heuristicas, vertice1, vertice2, valueArista);
    grafo.printGrafo(grafo);
    grafo.dfs();
    grafo.estrella();
    grafo.costoUniforme();
    grafo.greedy();
    return 0;
}