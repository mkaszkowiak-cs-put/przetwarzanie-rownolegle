#!/bin/bash

g++ -o 2_sito.o -O3 -static-libstdc++ 2_sito_v2.cpp
chmod +x 2_sito.o
./2_sito.o
