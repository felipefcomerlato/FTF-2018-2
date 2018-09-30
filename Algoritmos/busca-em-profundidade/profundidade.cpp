// Grafos - DFS (busca em profundidade)

#include <iostream>
#include <list>
#include <algorithm> // função find
#include <stack> // pilha para usar na DFS

using namespace std;

class Grafo
{
	int V; // número de vértices
	list<int> *adj; // ponteiro para um array contendo as listas de adjacências

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo

	// faz uma DFS a partir de um vértice
	void dfs(int v);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o número de vértices
	adj = new list<int>[V]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2)
{
	// adiciona vértice v2 à lista de vértices adjacentes de v1
	adj[v1].push_back(v2);
}

void Grafo::dfs(int v)
{
	stack<int> pilha;
	// bool visitados[V]; // vetor de visitados
	bool* visitados = (bool*)malloc(sizeof(bool*) * V); //segfault corrigido

	// marca todos como não visitados
	for(int i = 0; i < V; i++){
		visitados[i] = false;
	}
	// cout << "Iniciando busca...\n";
	while(true)
	{
		if(!visitados[v])
		{
			// cout << "Visitando vertice " << v << " ...\n";
			visitados[v] = true; // marca como visitado
			pilha.push(v); // insere "v" na pilha
		}

		bool achou = false;
		list<int>::iterator it;

		// busca por um vizinho não visitado
		for(it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if(!visitados[*it])
			{
				achou = true;
				break;
			}
		}

		if(achou)
			v = *it; // atualiza o "v"
		else
		{
			// se todos os vizinhos estão visitados ou não existem vizinhos
			// remove da pilha
			pilha.pop();
			// se a pilha ficar vazia, então terminou a busca
			if(pilha.empty())
				break;
			// se chegou aqui, é porque pode pegar elemento do topo
			v = pilha.top();
		}
	}
}

int main()
{
	int V = 8500000;

	Grafo grafo(V);

  int j = 1;
  for(int i = 0; i < V; i++)
  {
    if(j < V-1)
    {
      grafo.adicionarAresta(i, j);
      grafo.adicionarAresta(i, j+1);
      j = j + 2;
    }
  }

	grafo.dfs(0);
	// cout << "Terminou a busca\n";

	return 0;
}
