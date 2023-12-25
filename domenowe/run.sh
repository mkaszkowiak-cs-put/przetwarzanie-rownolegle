#!/bin/bash

g++ -o domenowe_v4.o -O3 -static-libstdc++ domenowe_v3.cpp
chmod +x domenowe_v4.o
./domenowe_v4.o
