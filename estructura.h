#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <ctime>
#include <cstdlib>
#include <random>
#include <queue>
#include <functional>
#include <unordered_map>
#include <climits>

using namespace std;

struct arista {
    char start;
    char end;
    int cost;
};

class Grafo{
	private:
		char inicio;
		char fin;
		char getInicio();
    	char getFin();
    	vector<char> nombreVertices;
    	vector<char> getNombreVertices();
    	vector<int> valueVertices;
    	vector<int> getValueVertices();
    	vector<arista> aristas;
    	vector<arista> getAristas();
    	int heuristic(char current, char goal);
	public:
		Grafo(char ini,char fini,vector<char> nombreVerts,vector<int> valueVerts,vector<char>vertice1,vector<char>vertice2,vector<int> valueArist);
		~Grafo();
		void printGrafo(Grafo grafo);
		void printRuta(vector<char>& path,unordered_map<char, int>& expanded);
		void dfs();
		void costoUniforme();
		void greedy();
		void estrella();
};