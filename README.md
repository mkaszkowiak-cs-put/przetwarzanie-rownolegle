# przetwarzanie-rownolegle
Projekt OMP do Walkusia

## Uruchomienie kodu:

```code
cd koncepcyjne
```

```code
g++ .\1_greedy.cpp -static-libstdc++ -o 1_greedy.exe
```

```code
.\1_greedy.exe <start> <end>
```

## Uruchomienie kodu wielowątkowego:

```code
cd domenowe
```

```code
g++ .\domenowe_v1.cpp -static-libstdc++ -fopenmp -o domenowe_v1.exe
```

```code
.\domenowe_v1.exe <start> <end>
```