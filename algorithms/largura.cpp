// Grafos - BFS (busca em largura)

#include <iostream>
#include <list>
#include <algorithm> // fun��o find
#include <chrono> //tempo de execu��o
#include <queue> // fila para usar na BFS

using namespace std;

class Grafo
{
	int V; // n�mero de v�rtices
	list<int> *adj; // ponteiro para um array contendo as listas de adjac�ncias

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo

	// faz uma BFS a partir de um v�rtice
	void bfs(int v);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o n�mero de v�rtices
	adj = new list<int>[V]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2)
{
	// adiciona v�rtice v2 � lista de v�rtices adjacentes de v1
	adj[v1].push_back(v2);
}

void Grafo::bfs(int v)
{
	queue<int> fila;

	bool* visitados = (bool*)malloc(sizeof(bool*) * V); //fix segfault

	//bool visitados[V]; // vetor de visitados

	for(int i = 0; i < V; i++)
		visitados[i] = false;

	//cout << "Visitando vertice " << v << " ...\n";
	visitados[v] = true; // marca como visitado

	while(true)
	{
		list<int>::iterator it;
		for(it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if(!visitados[*it])
			{
				//cout << "Visitando vertice " << *it << " ...\n";
				visitados[*it] = true; // marca como visitado
				fila.push(*it); // insere na fila
			}
		}

		// verifica se a fila N�O est� vazia
		if(!fila.empty())
		{
			v = fila.front(); // obt�m o primeiro elemento
			fila.pop(); // remove da fila
		}
		else
			break;
	}
}

int main()
{
	int V = 15000000;

	Grafo grafo(V);

	auto inicio_grafo = std::chrono::high_resolution_clock::now();
    int j = 1;
    for(int i = 0; i < V; i++)
    {
        if(j < V)
        {
            grafo.adicionarAresta(i, j);
            if (j < V-1){
                grafo.adicionarAresta(i, j+1);
            }
            j = j + 2;
        }
    }
	auto result_grafo = std::chrono::high_resolution_clock::now() - inicio_grafo;
	long long ms_grafo = std::chrono::duration_cast<std::chrono::milliseconds>(result_grafo).count();
	cout << "\n\nTempo para montar o grafo: " << ms_grafo << " milisegundos\n\n";

	auto inicio_busca = std::chrono::high_resolution_clock::now();
	grafo.bfs(0);
	auto result_busca = std::chrono::high_resolution_clock::now() - inicio_busca;
	long long ms_busca = std::chrono::duration_cast<std::chrono::milliseconds>(result_busca).count();
	cout << "\nTempo de bfs: " << ms_busca << " milisegundos\n\n";

	return 0;
}
