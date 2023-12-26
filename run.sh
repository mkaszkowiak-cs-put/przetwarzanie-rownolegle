#!/bin/bash

python3 -m pip install pandas

mkdir -p wyniki

cd funkcyjne 
./run.sh 

cd ../domenowe
./run.sh

cd ../koncepcyjne
./run.sh

cd ..

echo "wariant,watki,min,max,uruchomienia,avgczas,maxczas,minczas,dodania,dzielenia,liczbapierwszych,przyspieszenie,avgpredkosc,efektywnosc" > wyniki.csv
cat wyniki/* >> wyniki.csv

python3 process-results.py

echo "done - check wyniki.csv"