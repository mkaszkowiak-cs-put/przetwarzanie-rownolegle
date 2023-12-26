#!/bin/bash

echo "KONC-GREEDY-1"
g++ -o koncepcyjne.o -O3 -fopenmp -static-libstdc++  1_greedy.cpp
chmod +x koncepcyjne.o
./koncepcyjne.o > ../wyniki/KONC-GREEDY-1

echo "KONC-SITO-1"
g++ -o koncepcyjne.o -O3 -fopenmp -static-libstdc++  2_sito_v1.cpp
chmod +x koncepcyjne.o
./koncepcyjne.o > ../wyniki/KONC-SITO-1

echo "KONC-SITO-2"
g++ -o koncepcyjne.o -O3 -fopenmp -static-libstdc++  2_sito_v2.cpp
chmod +x koncepcyjne.o
./koncepcyjne.o > ../wyniki/KONC-SITO-2

