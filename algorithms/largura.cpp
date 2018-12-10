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
	int V_2;

	// ponteiro para um array contendo as listas de adjac�ncias
	list<int> *adj;
	list<int> *adj_2;

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2); // adiciona uma aresta no grafo

	// faz uma BFS a partir de um v�rtice
	void bfs(int v, FILE *fp);
};

Grafo::Grafo(int V)
{
	// atribui o n�mero de v�rtices
	this->V = V;
	this->V_2 = V;

	// cria as listas
	adj = new list<int>[V];
	adj_2 = new list<int>[V_2];
}

void Grafo::adicionarAresta(int v1, int v2)
{
	// adiciona v�rtice v2 � lista de v�rtices adjacentes de v1
	adj[v1].push_back(v2);
	adj_2[v1].push_back(v2);
}

void Grafo::bfs(int v, FILE *fp)
{
	queue<int> fila;
	queue<int> fila_2;

	bool* visitados = (bool*)malloc(sizeof(bool*) * V); //fix segfault
	bool* visitados_2 = (bool*)malloc(sizeof(bool*) * V); //fix segfault


	for(int i = 0; i < V; i++) {
		visitados[i] = false;
		visitados_2[i] = false;
	}
	
	// marca como visitado
	visitados[v] = true;
	visitados_2[v] = true;

	while(true)
	{
		for(auto it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if (visitados[*it] != visitados_2[*it]) {
				return exit(-1);
			}
			if(!visitados[*it])
			{
				// Visitando vertice *it
				fprintf(fp, "%d ", *it);

				// marca como visitado
				visitados[*it] = true;
				visitados_2[*it] = true;

				// insere na fila
				fila.push(*it);
				fila_2.push(*it);
			}
		}

		// verifica se a fila N�O est� vazia
		if(!fila.empty() && !fila_2.empty())
		{
			// obt�m o primeiro elemento
			v = fila.front(); 
			int v2 = fila_2.front();
			if (v != v2) {
				exit(-1);
			}

			// remove da fila
			fila.pop();
			fila_2.pop();

		}
		else
			break;
	}
}

#pragma GCC push_options
#pragma GCC optimize ("O0")

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

	int V = 150000;
	int V_2 =150000;

	if (V != V_2) {
		exit(-1);
	}

	Grafo grafo(V);

	#ifdef DEBUG
	auto inicio_grafo = std::chrono::high_resolution_clock::now();
    #endif
	
	int j = 1;
	int j_2 = 1;

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
		if (j != j_2) {
			exit(-1);
		}

        if(j < V)
        {
            grafo.adicionarAresta(i, j);
            if (j < V-1)
			{
                grafo.adicionarAresta(i, j+1);
            }
            j = j + 2;
			j_2 = j_2 + 2;
        }
    }

	#ifdef DEBUG
	auto result_grafo = std::chrono::high_resolution_clock::now() - inicio_grafo;
	long long ms_grafo = std::chrono::duration_cast<std::chrono::milliseconds>(result_grafo).count();
	cout << "\n\nTempo para montar o grafo: " << ms_grafo << " milisegundos\n\n";
	auto inicio_busca = std::chrono::high_resolution_clock::now();
	#endif

	grafo.bfs(0, fp);

	#ifdef DEBUG
	auto result_busca = std::chrono::high_resolution_clock::now() - inicio_busca;
	long long ms_busca = std::chrono::duration_cast<std::chrono::milliseconds>(result_busca).count();
	cout << "\nTempo de bfs: " << ms_busca << " milisegundos\n\n";
	#endif

	fclose(fp);
	return 0;
}

#pragma GCC pop_options
