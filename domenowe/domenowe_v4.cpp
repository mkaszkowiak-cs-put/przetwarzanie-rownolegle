#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <omp.h>
#include "../measure_time.cpp"
#include "../print_primes.cpp"

// Zadaniem realizowanym równolegle w jednym trybie podziału pracy
// może być wykreślenie wszystkich wymaganych wielokrotności
// podzbioru liczb pierwszych.

// To jest raczej niepoprawne, bo nie równoleglimy wykreślania a wrzucanie do tablicy primes
// Ale chociaż jest szybsze xD

std::vector<int> findPrimes(int lower, int upper)
{
    std::vector<int> primes;
    std::vector<bool> prime(upper + 1, true);
    prime[0] = false;
    prime[1] = false;

    // Procesy otrzymują całą tablice wykreśleń
    for (int p = 2; p <= sqrt(upper); ++p)
    {
        if (prime[p])
        {
            for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
            {
                prime[i] = false;
            }
        }
    }

// Dynamiczne rozdzielanie iteracji pomiędzy wątki
#pragma omp parallel
    {
        // Tworzymy lokalna kopie tablicy wątkow
        std::vector<int> threadPrimes = primes;

// Wątek nie czeka na inne wątki az skonczą wykonywać pętle
#pragma omp for nowait
        for (int p = 2; p <= upper; p++)
        {
            if (prime[p])
            {
                threadPrimes.push_back(p);
            }
        }

// Każdy wątek tylko raz wykonuje operacje zapisania do tablicy primes
#pragma omp critical
        primes.insert(primes.end(), threadPrimes.begin(), threadPrimes.end());
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
