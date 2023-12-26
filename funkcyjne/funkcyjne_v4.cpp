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

    std::vector<int> primesToSqrt;
    int sqrtUpper = sqrt(upper);

    for (int p = 2; p <= sqrtUpper; p++)
    {
        (*additions) += 1;
        if (prime[p])
        {
            primesToSqrt.push_back(p);
            for (int i = p * p; i <= sqrtUpper; i += p)
            {
                (*additions) += 1;
                prime[i] = false;
            }
        }
    }

    int primesToSqrtSize = primesToSqrt.size();

    long long _additions, _divisions = 0;

#pragma omp parallel reduction(+ : _additions, _divisions)
    {
        std::vector<bool> threadPrime = prime;

#pragma omp for nowait
        for (int i = 0; i < primesToSqrtSize; ++i)
        {
            _additions += 1;
            int p = primesToSqrt[i];
            for (int multiple = p * p; multiple <= upper; multiple += p)
            {
                _additions += 1;
                threadPrime[multiple] = false;
            }
        }

#pragma omp critical
        for (int i = lower; i <= upper; ++i)
        {
            _additions += 1;
            if (!threadPrime[i])
            {
                prime[i] = false;
            }
        }
    }

    for (int p = lower; p <= upper; p++)
    {
        (*additions) += 1;
        if (prime[p])
            primes.push_back(p);
    }

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

    benchmark(findPrimes, "FUNKC-4");
    return 0;
}
