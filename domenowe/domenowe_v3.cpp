#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <omp.h>
#include "../measure_time.cpp"
#include "../print_primes.cpp"

std::vector<int> findPrimes(int lower, int upper, long long *additions, long long *divisions)
{
    std::vector<int> primes;
    std::vector<bool> prime(upper + 1, true);
    (*additions) += 1;
    prime[0] = false;
    prime[1] = false;

    long long _additions, _divisions = 0;

// Tworzymy sekcję parallel
#pragma omp parallel reduction(+ : _additions, _divisions)
    {
        // Tworzymy lokalna kopie tablicy wątkow
        std::vector<bool> threadPrime = prime;

// Wątek nie czeka na inne wątki az skonczą wykonywać pętle
// Schedule jest w domyślnym trybie static
#pragma omp for nowait
        for (int p = 2; p <= upper; p++)
        {
            _additions += 1;
            if (threadPrime[p])
            {
                _additions += 1;
                _divisions += 1;

                for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
                {
                    _additions += 1;
                    threadPrime[i] = false;
                }
            }
        }

// Tablica prime jest aktualizowana przez jeden wątek jednocześnie
#pragma omp critical
        for (int p = 2; p <= upper; p++)
        {
            _additions += 1;
            if (!threadPrime[p])
            {
                prime[p] = false;
            }
        }
    }

    // TODO: NIE RUSZAMY WEKTORA PRIMES, A MUSIMY!!!
    // NIE ZWRACAJA SIE LICZBY PIERWSZE!!!

    (*additions) += _additions;
    (*divisions) += _divisions;

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

    benchmark(findPrimes, "DOMEN-3");
    return 0;
}
