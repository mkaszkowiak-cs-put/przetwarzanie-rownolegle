#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <omp.h>
#include "../measure_time.cpp"
#include "../print_primes.cpp"

std::vector<int> findPrimes(int lower, int upper)
{
    std::vector<int> primes;
    std::vector<bool> prime(upper + 1, true);
    prime[0] = false;
    prime[1] = false;

// Tworzymy sekcję parallel
#pragma omp parallel
    {
        // Tworzymy lokalna kopie tablicy wątkow
        std::vector<bool> threadPrime = prime;

// Wątek nie czeka na inne wątki az skonczą wykonywać pętle
// Schedule jest w domyślnym trybie static
#pragma omp for nowait
        for (int p = 2; p <= upper; p++)
        {
            if (threadPrime[p])
            {
                for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
                    threadPrime[i] = false;
            }
        }

// Tablica prime jest aktualizowana przez jeden wątek jednocześnie
#pragma omp critical
        for (int p = 2; p <= upper; p++)
        {
            if (!threadPrime[p])
            {
                prime[p] = false;
            }
        }
    }

    return primes;
}

int main(int argc, char *argv[])
{
    int start = 2;
    int end = 20000000;

    if (argc == 3)
    {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    }

    measureTime("Sito:", findPrimes, start, end);
    return 0;
}
