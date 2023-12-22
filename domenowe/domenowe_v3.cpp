#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <omp.h>
#include "../measure_time.cpp"
#include "../print_primes.cpp"

std::vector<int> sieveOfEratosthenes(int lower, int upper) {
    std::vector<int> primes;
    std::vector<bool> prime(upper + 1, true);
    prime[0] = prime[1] = false;

    // Dynamiczne rozdzielanie iteracji pomiędzy wątki
    #pragma omp parallel
    {
        // Tworzymy lokalna kopie tablicy wątkow
        std::vector<bool> threadPrime = prime;

        // Wątek nie czeka na inne wątki az skonczą wykonywać pętle
        #pragma omp for nowait
        for (int p = 2; p <= upper; p++) {
            if (threadPrime[p]) {
                for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
                    threadPrime[i] = false;
            }
        }

        // Tablica prime jest aktualizowana przez jeden wątek jednocześnie
        #pragma omp critical
        for (int p = 2; p <= upper; p++) {
            if (!threadPrime[p]) {
                prime[p] = false;
            }
        }
    }

    // printPrimes(prime, lower, upper);

    return primes;
}

int main(int argc, char *argv[]) {
    int start = 2;
    int end = 20000000;

    if(argc == 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    }

    measureTime("Sito:", sieveOfEratosthenes, start, end);
    return 0;
}
