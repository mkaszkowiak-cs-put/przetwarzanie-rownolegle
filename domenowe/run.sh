#!/bin/bash

echo "DOMEN-1"
g++ -o ./domenowe.o -O3 -fopenmp -static-libstdc++ ./domenowe_v1.cpp
chmod +x ./domenowe.o
./domenowe.o > ../wyniki/DOMEN-1

echo "DOMEN-2"
g++ -o ./domenowe.o -O3 -fopenmp -static-libstdc++ ./domenowe_v2.cpp
chmod +x ./domenowe.o
./domenowe.o > ../wyniki/DOMEN-2

echo "DOMEN-3"
g++ -o ./domenowe.o -O3 -fopenmp -static-libstdc++ ./domenowe_v3.cpp
chmod +x ./domenowe.o
./domenowe.o > ../wyniki/DOMEN-3

echo "DOMEN-4"
g++ -o ./domenowe.o -O3 -fopenmp -static-libstdc++ ./domenowe_v4.cpp
chmod +x ./domenowe.o
./domenowe.o > ../wyniki/DOMEN-4
