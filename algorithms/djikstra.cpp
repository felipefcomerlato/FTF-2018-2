// Grafos - DFS (busca em profundidade)

#include <iostream>
#include <list>
#include <algorithm> // fun��o find
#include <stack> // pilha para usar na DFS
#include <chrono> //tempo de execu��o
#include <queue>

#define INFINITO 10000000

using namespace std;

class Grafo
{
	int V; // n�mero de v�rtices

	list<pair<int, int> > * adj;

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2, int custo); // adiciona uma aresta no grafo

	// aplica dijkstra a partir do v�rtice v
	// para encontrar o v�rtice x
	void dijkstra(int v, int x);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o n�mero de v�rtices
	adj = new list<pair<int, int> >[V]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2, int custo)
{
	// adiciona v�rtice v2 � lista de v�rtices adjacentes de v1
	adj[v1].push_back(make_pair(v2, custo));
}

void Grafo::dijkstra(int orig, int dest)
{
	// vetor de dist�ncias
	int dist[V];

	/*
		vetor de visitados serve para caso o v�rtice j� tenha sido
		expandido (visitado), n�o expandir mais
	*/
	int visitados[V];

	// fila de prioridades de pair (distancia, v�rtice)
	priority_queue <pair<int, int>,
					vector<pair<int, int> >, greater<pair<int, int> > > pq;

	// inicia o vetor de dist�ncias e visitados
	for(int i = 0; i < V; i++)
	{
		dist[i] = INFINITO;
		visitados[i] = false;
	}

	// a dist�ncia de orig para orig � 0
	dist[orig] = 0;

	// insere na fila
	pq.push(make_pair(dist[orig], orig));

	// loop do algoritmo
	while(!pq.empty())
	{
		pair<int, int> p = pq.top(); // extrai o pair do topo
		int u = p.second; // obt�m o v�rtice do pair
		pq.pop(); // remove da fila

		// verifica se o v�rtice n�o foi expandido
		if(visitados[u] == false)
		{
			// marca como visitado
			visitados[u] = true;


			list<pair<int, int> >::iterator it;

			// percorre os v�rtices "v" adjacentes de "u"
			for(it = adj[u].begin(); it != adj[u].end(); it++)
			{
				// obt�m o v�rtice adjacente e o custo da aresta
				int v = it->first;
				int custo_aresta = it->second;

				// relaxamento (u, v)
				if(dist[v] > (dist[u] + custo_aresta))
				{
					// atualiza a dist�ncia de "v" e insere na fila
					//printf("%d ", v);
					dist[v] = dist[u] + custo_aresta;
					pq.push(make_pair(dist[v], v));
				}
			}
		}
	}
	// Retorna a distância mínima até o destino
	printf("%d", dist[dest]);
}

int main()
{
	int V = 150000;

	Grafo grafo(V);

	auto inicio_grafo = chrono::high_resolution_clock::now();
	int j = 1;
	for(int i = 0; i < V; i++)
	{
    	if(j < V)
    	{
			grafo.adicionarAresta(i, j, 1);
			if (j < V-1)
			{
	    		grafo.adicionarAresta(i, j+1, 1);
			}
    		j = j + 2;
    	}
	}

	#ifdef DEBUG
	auto result_grafo = chrono::high_resolution_clock::now() - inicio_grafo;
	long long ms_grafo = chrono::duration_cast<chrono::milliseconds>(result_grafo).count();
	cout << "\n\nTempo para montar o grafo: " << ms_grafo << " milisegundos\n\n";
	auto inicio_busca = chrono::high_resolution_clock::now();
	#endif
	
	// Busca o último vertice
	grafo.dijkstra(0, V-1); 

	#ifdef DEBUG
	auto result_busca = chrono::high_resolution_clock::now() - inicio_busca;
	long long ms_busca = chrono::duration_cast<chrono::milliseconds>(result_busca).count();
	cout << "\nTempo de dijkstra: " << ms_busca << " milisegundos\n\n";
	#endif

	return 0;
}
