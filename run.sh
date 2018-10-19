printf "Building\n"
make clean -C ./algorithms/
make -C ./algorithms/

printf "Copying executables to tmp\n"
mkdir -p /tmp/ftf
cp ./algorithms/djikstra     /tmp/ftf/djikstra
cp ./algorithms/largura      /tmp/ftf/largura
cp ./algorithms/profundidade /tmp/ftf/profundidade

printf "Generating gold files..\n"
mkdir -p /tmp/ftf/gold
/tmp/ftf/djikstra     /tmp/ftf/gold/djikstra
/tmp/ftf/largura      /tmp/ftf/gold/largura
/tmp/ftf/profundidade /tmp/ftf/gold/profundidade

printf "Gold files done, injecting faults\n"
# One terminal per executable
gnome-terminal -e "./fault_injector.py -c ./algorithms/djikstra.conf     -i 10"
gnome-terminal -e "./fault_injector.py -c ./algorithms/largura.conf      -i 10"
gnome-terminal -e "./fault_injector.py -c ./algorithms/profundidade.conf -i 10"

