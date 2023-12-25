#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../measure_time.cpp"

std::vector<int> findPrimes(int lower, int upper)
{
    std::vector<int> primes;
    std::vector<bool> prime(upper + 1, true);
    prime[0] = false;
    prime[1] = false;

    int max = std::sqrt(upper);

    for (int p = 2; p <= max; p++)
    {
        if (prime[p])
        {
            for (int i = std::max(p * p, (lower + p - 1) / p * p); i <= upper; i += p)
                prime[i] = false;
        }
    }

    for (int p = lower; p <= upper; p++)
    {
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

    measureTime("Sito:", findPrimes, start, end);
    return 0;
}
