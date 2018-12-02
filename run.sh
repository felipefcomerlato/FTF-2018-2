#!/bin/bash
echo "Building"
make clean -C ./algorithms/
make -C ./algorithms/

echo "Clearing logs"
rm -rf ./logs
rm -f ./summary-carolfi.log

echo "Copying executables to tmp"
mkdir -p /tmp/ftf
# cp ./algorithms/djikstra     /tmp/ftf/djikstra
cp ./algorithms/largura      /tmp/ftf/largura
cp ./algorithms/profundidade /tmp/ftf/profundidade

echo "Generating gold files"
mkdir -p /tmp/ftf/gold
# /tmp/ftf/djikstra     /tmp/ftf/gold/djikstra
/tmp/ftf/largura      /tmp/ftf/gold/largura
/tmp/ftf/profundidade /tmp/ftf/gold/profundidade

echo "Injecting faults"
# One terminal per executable
# gnome-terminal -e "./fault_injector.py -c ./algorithms/djikstra.conf     -i 1000"
gnome-terminal -e "./fault_injector.py -c ./algorithms/largura.conf      -i 1000"
gnome-terminal -e "./fault_injector.py -c ./algorithms/profundidade.conf -i 1000"

echo "Run ./sh stats.sh when done to get an overview of corruptions (SDCs), Hangs, Crashes, and masked faults."



