#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../measure_time.cpp"

std::vector<int> findPrimes(int lower, int upper, long long *additions, long long *divisions)
{
    std::vector<int> primes;
    std::vector<bool> prime(upper + 1, true);
    prime[0] = false;
    prime[1] = false;

    int max = std::sqrt(upper);

    for (int p = 2; p <= max; p++)
    {
        (*additions) += 1; // pętla

        if (prime[p])
        {
            // początkowe warunki pętli
            (*divisions) += 1;
            (*additions) += 1;

            for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
            {
                (*additions) += 1; // pętla
                prime[i] = false;
            }
        }
    }

    for (int p = lower; p <= upper; p++)
    {
        (*additions) += 1; // pętla

        if (prime[p])
            primes.push_back(p);
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

    benchmark(findPrimes, "KONC-SITO-2");
    return 0;
}
