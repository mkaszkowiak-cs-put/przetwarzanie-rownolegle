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

// Dynamiczne rozdzielanie iteracji pomiędzy wątki
#pragma omp parallel for schedule(dynamic)
    for (int p = 2; p <= upper; p++)
    {
        if (prime[p])
        {
            for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
                // Ryzyko wyscigu - edytujemy zasób współdzielony
                prime[i] = false;
        }
    }

    // printPrimes(prime, lower, upper);

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
