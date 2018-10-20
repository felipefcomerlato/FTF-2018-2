#!/bin/bash
printf "djikstra-random:\n"
printf "SDCs: "
grep -r -i "djikstra-random - SDC" summary-carolfi.log |wc -l
printf "Crashes: "
grep -r -i "djikstra-random - CRASH" summary-carolfi.log |wc -l
printf "Hangs: "
grep -r -i "djikstra-random - HANG" summary-carolfi.log |wc -l
printf "Masked: "
grep -r -i "djikstra-random - Masked" summary-carolfi.log |wc -l
printf "Failed: "
grep -r -i "djikstra-random - Fault Injection Failed" summary-carolfi.log |wc -l

printf "\nprofundidade-random:\n"
printf "SDCs: "
grep -r -i "profundidade-random - SDC" summary-carolfi.log |wc -l
printf "Crashes: "
grep -r -i "profundidade-random - CRASH" summary-carolfi.log |wc -l
printf "Hangs: "
grep -r -i "profundidade-random - HANG" summary-carolfi.log |wc -l
printf "Masked: "
grep -r -i "profundidade-random - Masked" summary-carolfi.log |wc -l
printf "Failed: "
grep -r -i "profundidade-random - Fault Injection Failed" summary-carolfi.log |wc -l

printf "\nlargura-random:\n"
printf "SDCs: "
grep -r -i "largura-random - SDC" summary-carolfi.log |wc -l
printf "Crashes: "
grep -r -i "largura-random - CRASH" summary-carolfi.log |wc -l
printf "Hangs: "
grep -r -i "largura-random - HANG" summary-carolfi.log |wc -l
printf "Masked: "
grep -r -i "largura-random - Masked" summary-carolfi.log |wc -l
printf "Failed: "
grep -r -i "largura-random - Fault Injection Failed" summary-carolfi.log |wc -l



