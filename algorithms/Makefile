# C++ compiler
CC = g++ -g -std=c++11

destDir = /tmp/quicksort

all: djikstra largura profundidade

djikstra: djikstra.cpp
	$(CC) djikstra.cpp -o djikstra

largura: largura.cpp
	$(CC) largura.cpp -o largura

profundidade: profundidade.cpp
	$(CC) profundidade.cpp -o profundidade

clean:
	rm -rf djikstra largura profundidade
