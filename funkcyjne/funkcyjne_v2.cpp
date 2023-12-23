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

    std::vector<int> primesToSqrt;
    int sqrtUpper = sqrt(upper);

    for (int p = 2; p <= sqrtUpper; p++) {
        if (prime[p]) {
            primesToSqrt.push_back(p);
            for (int i = p * p; i <= sqrtUpper; i += p) {
                prime[i] = false;
            }
        }
    }

    int primesToSqrtSize = primesToSqrt.size();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < primesToSqrtSize; ++i) {
        int p = primesToSqrt[i];
        for (int multiple = p * p; multiple <= upper; multiple += p) {
            // Brak ryzyka wyścigu
            #pragma omp critical
            prime[multiple] = false;
        }
    }

    for (int p = lower; p <= upper; p++) {
        if (prime[p])
            primes.push_back(p);
    }

    // printPrimes(primes, lower, upper);

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
