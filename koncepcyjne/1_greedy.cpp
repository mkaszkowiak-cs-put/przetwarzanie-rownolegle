#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../measure_time.cpp"

bool isPrimeNumber(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;

    // Optymalizacje - odrzucamy na wejściu parzyste liczby
    if (n % 2 == 0)
        return false;

    // Musimy sprawdzić tylko do kwadratu N
    int max = std::sqrt(n);

    // Nie sprawdzamy parzystych dzielników
    for (int i = 3; i <= max; i += 2)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

std::vector<int> greedyFindPrimes(int start, int end)
{
    std::vector<int> primes;

    for (int i = start; i <= end; i++)
    {
        if (isPrimeNumber(i))
        {
            primes.push_back(i);
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

    measureTime("Greedy:", greedyFindPrimes, start, end);
    return 0;
}
