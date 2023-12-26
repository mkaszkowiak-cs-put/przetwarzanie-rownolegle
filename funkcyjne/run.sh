#!/bin/bash

echo "FUNKC-1"
g++ -o ./funkcyjne.o -O3 -fopenmp -static-libstdc++ ./funkcyjne_v1.cpp
chmod +x ./funkcyjne.o
./funkcyjne.o > ../wyniki/FUNKC-1

echo "FUNKC-2"
g++ -o ./funkcyjne.o -O3 -fopenmp -static-libstdc++ ./funkcyjne_v2.cpp
chmod +x ./funkcyjne.o
./funkcyjne.o > ../wyniki/FUNKC-2

echo "FUNKC-3"
g++ -o ./funkcyjne.o -O3 -fopenmp -static-libstdc++ ./funkcyjne_v3.cpp
chmod +x ./funkcyjne.o
./funkcyjne.o > ../wyniki/FUNKC-3

echo "FUNKC-4"
g++ -o ./funkcyjne.o -O3 -fopenmp -static-libstdc++ ./funkcyjne_v4.cpp
chmod +x ./funkcyjne.o
./funkcyjne.o > ../wyniki/FUNKC-4