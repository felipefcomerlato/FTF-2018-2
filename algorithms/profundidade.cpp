// Grafos - DFS (busca em profundidade)

#include <iostream>
#include <list>
#include <algorithm> // função find
#include <stack> // pilha para usar na DFS
#include <chrono> //tempo de execução

using namespace std;

class Grafo
{
	int V; // número de vértices
	list<int> *adj; // ponteiro para um array contendo as listas de adjacências

	int V_2; // número de vértices
	list<int> *adj_2; // ponteiro para um array contendo as listas de adjacências

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo

	// faz uma DFS a partir do vértice v
	// para encontrar o vértice x
	void dfs(int v, int x, FILE *fp);
};

Grafo::Grafo(int V)
{
	this->V = V; // atribui o número de vértices
	adj = new list<int>[V]; // cria as listas

	this->V_2 = V_2; // atribui o número de vértices
	adj_2 = new list<int>[V_2]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2)
{
	// adiciona vértice v2 à lista de vértices adjacentes de v1
	adj[v1].push_back(v2);
	adj_2[v1].push_back(v2);
}

// v = inicial, x = final
void Grafo::dfs(int v, int x, FILE *fp)
{
	stack<int> pilha;
	stack<int> pilha_2;
	// bool visitados[V]; // vetor de visitados
	bool* visitados = (bool*)malloc(sizeof(bool*) * V); //fix segfault
	bool* visitados_2 = (bool*)malloc(sizeof(bool*) * V); //fix segfault

	// marca todos como não visitados
	for(int i = 0; i < V; i++){
		visitados[i] = false;
		visitados_2[i] = false;
	}

	// cout << "Iniciando busca...\n";
	while(true)
	{
		if(!visitados[v])
		{
			// Visitando o vertice v
			//printf("%d ", v);
			if(v == x){
				// Encontrou o vértice
				while (!pilha.empty()) {
					fprintf(fp, "%d ", pilha.top());
					pilha.pop();
				}
				break;
			}
			visitados[v] = true; // marca como visitado
			pilha.push(v); // insere "v" na pilha
		}

		if(!visitados_2[v])
		{
			// Visitando o vertice v
			//printf("%d ", v);
			if(v == x){
				// Encontrou o vértice
				while (!pilha_2.empty()) {
					fprintf(fp, "%d ", pilha_2.top());
					pilha_2.pop();
				}
				break;
			}
			visitados_2[v] = true; // marca como visitado
			pilha_2.push(v); // insere "v" na pilha
		}

		bool achou = false;
		list<int>::iterator it;

		// busca por um vizinho não visitado
		for(it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if (visitados[*it] != visitados_2[*it]) {
				return exit(-1);
			}
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
			pilha_2.pop();
			// se a pilha ficar vazia, então terminou a busca
			if(pilha.empty())
				break;
			if(pilha_2.empty())
				break;
			// se chegou aqui, é porque pode pegar elemento do topo
			v = pilha.top();
		}
	}
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

	FILE *fp;
    if (fp = fopen(outputFile, "wb")) {
        // File ok
    } else {
        printf("Error writing output file");
        exit(1);
    }

	int V = 15000000;
	int V_2 = 15000000;

	Grafo grafo(V);

	#ifdef DEBUG
	auto inicio_grafo = std::chrono::high_resolution_clock::now();
	#endif

	int j = 1;

	int i = 0
	int i_2 = 0
	for(int i = 0, int i = 0; i < V; i++, i_2++)
	{
		if (i != i_2) {
			exit(-1);
		}
		if (V != V_2) {
			exit(-1);
		}
		{
	    	if(j < V)
	    	{
				grafo.adicionarAresta(i, j);
				if (j < V-1)
				{
		    		grafo.adicionarAresta(i, j+1);
				}
				j = j + 2;
			}
		}
	}

	#ifdef DEBUG
	auto result_grafo = std::chrono::high_resolution_clock::now() - inicio_grafo;
	long long ms_grafo = std::chrono::duration_cast<std::chrono::milliseconds>(result_grafo).count();
	cout << "\n\nTempo para montar o grafo: " << ms_grafo << " milisegundos\n\n";
	auto inicio_busca = std::chrono::high_resolution_clock::now();
	#endif

	// Busca o último vertice
	grafo.dfs(0, V-1, fp);

	#ifdef DEBUG
	auto result_busca = std::chrono::high_resolution_clock::now() - inicio_busca;
	long long ms_busca = std::chrono::duration_cast<std::chrono::milliseconds>(result_busca).count();
	cout << "\nTempo de dfs: " << ms_busca << " milisegundos\n\n";
	#endif

	fclose(fp);
	return 0;
}
