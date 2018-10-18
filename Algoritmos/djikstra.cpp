// Grafos - DFS (busca em profundidade)

#include <iostream>
#include <list>
#include <algorithm> // função find
#include <stack> // pilha para usar na DFS
#include <chrono> //tempo de execução
#include <queue>

#define INFINITO 10000000

using namespace std;

class Grafo
{
	int V; // número de vértices

	list<pair<int, int> > * adj;

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2, int custo); // adiciona uma aresta no grafo

	// aplica dijkstra a partir do vértice v
	// para encontrar o vértice x
	void dijkstra(int v, int x);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o número de vértices
	adj = new list<pair<int, int> >[V]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2, int custo)
{
	// adiciona vértice v2 à lista de vértices adjacentes de v1
	adj[v1].push_back(make_pair(v2, custo));
}

void Grafo::dijkstra(int orig, int dest)
	{
		// vetor de distâncias
		int dist[V];

		/*
		   vetor de visitados serve para caso o vértice já tenha sido
		   expandido (visitado), não expandir mais
		*/
		int visitados[V];

		// fila de prioridades de pair (distancia, vértice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// inicia o vetor de distâncias e visitados
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// a distância de orig para orig é 0
		dist[orig] = 0;

		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			pq.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(visitados[u] == false)
			{
				// marca como visitado
				visitados[u] = true;


				list<pair<int, int> >::iterator it;

				// percorre os vértices "v" adjacentes de "u"
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// relaxamento (u, v)
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
// retorna a distância mínima até o destino
		//cout << dist[dest] << endl;
	}



int main()
{
	int V = 150000;

	Grafo grafo(V);

	auto inicio_grafo = std::chrono::high_resolution_clock::now();
  int j = 1;
  for(int i = 0; i < V; i++)
  {
    if(j < V)
    {
			grafo.adicionarAresta(i, j, 1);
			if (j < V-1){
	    	grafo.adicionarAresta(i, j+1, 1);
			}
      j = j + 2;
    }
  }
	auto result_grafo = std::chrono::high_resolution_clock::now() - inicio_grafo;
	long long ms_grafo = std::chrono::duration_cast<std::chrono::milliseconds>(result_grafo).count();
	cout << "\n\nTempo para montar o grafo: " << ms_grafo << " milisegundos\n\n";

	auto inicio_busca = std::chrono::high_resolution_clock::now();
	grafo.dijkstra(0,V-1); //busca o último vertice
	auto result_busca = std::chrono::high_resolution_clock::now() - inicio_busca;
	long long ms_busca = std::chrono::duration_cast<std::chrono::milliseconds>(result_busca).count();
	cout << "\nTempo de dijkstra: " << ms_busca << " milisegundos\n\n";

	return 0;
}
