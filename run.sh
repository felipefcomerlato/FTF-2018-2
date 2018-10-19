printf 'building...'
make clean -C ./algorithms/
make -C ./algorithms/

printf 'build done, generating gold files..'
mkdir -p algorithms/gold
./algorithms/djikstra > ./algorithms/gold/djikstra
./algorithms/largura > ./algorithms/gold/largura
./algorithms/profundidade > ./algorithms/gold/profundidade

printf 'gold files done, injecting faults'
./fault_injector.py -c ./algorithms/djikstra.conf     -i 10
./fault_injector.py -c ./algorithms/largura.conf      -i 10
./fault_injector.py -c ./algorithms/profundidade.conf -i 10

printf 'all done'
