// Grafos - DFS (busca em profundidade)

#include <iostream>
#include <list>
#include <algorithm> // fun��o find
#include <stack> // pilha para usar na DFS
#include <chrono> //tempo de execu��o
#include <queue>
#include <cstdio>

#define INFINITO 10000000

using namespace std;

class Grafo
{
	int V; // n�mero de v�rtices
	int V_2;

	list<pair<int, int> > * adj;
	list<pair<int, int> > * adj_2;

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2, int custo); // adiciona uma aresta no grafo

	// aplica dijkstra a partir do v�rtice v
	// para encontrar o v�rtice x
	int dijkstra(int v, int x);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o n�mero de v�rtices
	this->V_2 = V;
	adj = new list<pair<int, int> >[V]; // cria as listas
	adj_2 = new list<pair<int, int> >[V_2]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2, int custo)
{
	// adiciona v�rtice v2 � lista de v�rtices adjacentes de v1
	adj[v1].push_back(make_pair(v2, custo));
	adj_2[v1].push_back(make_pair(v2, custo));
}

int Grafo::dijkstra(int orig, int dest)
{
	// vetor de dist�ncias
	int dist[V];
	int dist_2[V];

	/*
		vetor de visitados serve para caso o v�rtice j� tenha sido
		expandido (visitado), n�o expandir mais
	*/
	int visitados[V];
	int visitados_2[V];

	// fila de prioridades de pair (distancia, v�rtice)
	priority_queue <pair<int, int>,
					vector<pair<int, int> >, greater<pair<int, int> > > pq;
	priority_queue <pair<int, int>,
					vector<pair<int, int> >, greater<pair<int, int> > > pq_2;

	// inicia o vetor de dist�ncias e visitados
	for(int i = 0; i < V; i++)
	{
		dist[i] = INFINITO;
		dist_2[i] = INFINITO;
		visitados[i] = false;
		visitados_2[i] = false;
	}

	// a dist�ncia de orig para orig � 0
	dist[orig] = 0;
	dist_2[orig] = 0;

	// insere na fila
	pq.push(make_pair(dist[orig], orig));
	pq_2.push(make_pair(dist_2[orig], orig));

	// loop do algoritmo
	while(!pq.empty())
	{
		pair<int, int> p = pq.top(); // extrai o pair do topo
		pair<int, int> p_2 = pq_2.top(); // extrai o pair do topo
		int u = p.second; // obt�m o v�rtice do pair
		int u_2 = p_2.second; // obt�m o v�rtice do pair
		pq.pop(); // remove da fila
		pq_2.pop(); // remove da fila

		// verifica se o v�rtice n�o foi expandido
		if(visitados[u] == false && visitados_2[u_2])
		{
			// marca como visitado
			visitados[u] = true;
			visitados_2[u] = true;

			list<pair<int, int> >::iterator it;
			list<pair<int, int> >::iterator it_2;

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

			// percorre os v�rtices "v" adjacentes de "u" no segundo grafo
			for(it_2 = adj_2[u_2].begin(); it_2 != adj_2[u_2].end(); it_2++)
			{
				// obt�m o v�rtice adjacente e o custo da aresta
				int v_2 = it_2->first;
				int custo_aresta_2 = it_2->second;

				// relaxamento (u, v)
				if(dist_2[v_2] > (dist_2[u_2] + custo_aresta_2))
				{
					// atualiza a dist�ncia de "v" e insere na fila
					//printf("%d ", v);
					dist_2[v_2] = dist_2[u_2] + custo_aresta_2;
					pq_2.push(make_pair(dist_2[v_2], v_2));
				}
			}
		} else {
			exit(-1);
		}
	}
	// Retorna a distância mínima até o destino ou erro caso distancias sejam diferentes
	if(dist[dest] != dist_2[dest])
		exit(-1);
	else
		return dist[dest];
}

int main(int argc, char** argv)
{
	char *outputFile;
	if (argc == 2) {
        outputFile = argv[1];
    } else {
        fprintf(stderr, "Usage: %s <output file>\n", argv[0]);
        exit(1);
    }



	int V = 150000;
	int V_2 =150000;

	Grafo grafo(V);

	#ifdef DEBUG
	auto inicio_grafo = std::chrono::high_resolution_clock::now();
    #endif

	int j = 1;

	int i = 0;
	int i_2 = 0;

    for(i = 0, i_2 = 0; i < V; i++, i_2++)
    {
		if (i != i_2) {
			exit(-1);
		}
		if (V != V_2) {
			exit(-1);
		}
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
	int distancia = grafo.dijkstra(0, V-1);
	FILE *fp;
    if (fp = fopen(outputFile, "wb")) {
        fprintf(fp, "%d", distancia);
    } else {
        printf("Error writing output file");
        exit(1);
    }

	#ifdef DEBUG
	auto result_busca = chrono::high_resolution_clock::now() - inicio_busca;
	long long ms_busca = chrono::duration_cast<chrono::milliseconds>(result_busca).count();
	cout << "\nTempo de dijkstra: " << ms_busca << " milisegundos\n\n";
	#endif

	fclose(fp);
	return 0;
}
