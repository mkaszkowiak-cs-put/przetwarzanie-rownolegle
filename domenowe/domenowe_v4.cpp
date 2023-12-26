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
std::vector<int> findPrimes(int lower, int upper, long long *additions, long long *divisions)
{
    std::vector<int> primes;
    (*additions) += 1;
    std::vector<bool> prime(upper + 1, true);
    prime[0] = false;
    prime[1] = false;

    // Procesy otrzymują całą tablice wykreśleń
    for (int p = 2; p <= sqrt(upper); ++p)
    {
        (*additions) += 1;

        if (prime[p])
        {
            (*additions) += 1;
            (*divisions) += 1;
            for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
            {
                (*additions) += 1;
                prime[i] = false;
            }
        }
    }

    long long _additions, _divisions = 0;

// Dynamiczne rozdzielanie iteracji pomiędzy wątki
#pragma omp parallel reduction(+ : _additions, _divisions)
    {
        // Tworzymy lokalna kopie tablicy wątkow
        std::vector<int> threadPrimes = primes;

// Wątek nie czeka na inne wątki az skonczą wykonywać pętle
#pragma omp for nowait
        for (int p = 2; p <= upper; p++)
        {
            _additions += 1;
            if (prime[p])
            {
                threadPrimes.push_back(p);
            }
        }

// Każdy wątek tylko raz wykonuje operacje zapisania do tablicy primes
#pragma omp critical
        primes.insert(primes.end(), threadPrimes.begin(), threadPrimes.end());
    }

    (*additions) += _additions;
    (*divisions) += _divisions;

    return primes;
}

int main(int argc, char *argv[])
{
    int start = 2;
    int end = 200000000;

    if (argc == 3)
    {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    }

    benchmark(findPrimes, "DOMEN-4");
    return 0;
}
