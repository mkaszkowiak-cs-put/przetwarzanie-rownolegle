#include <iostream>
#include <time.h>
#include <vector>
#include <omp.h>

#ifndef MAX_BENCHMARK
#define MAX_BENCHMARK 200000000
#endif

template <typename T>
void measureTime(
    T func,
    std::string message,
    int threads,
    int lower,
    int upper)
{

    // Wymuszamy wykorzystanie dokładnie podanej liczby wątków
    omp_set_dynamic(0);
    omp_set_num_threads(threads);

    const int numRuns = 2;
    double totalTime = 0.0;

    double maxTime = 0;
    double minTime = 10000000000;
    long long additions = 0;
    long long divisions = 0;

    std::vector<int> primes;
    for (int i = 0; i < numRuns; ++i)
    {
        additions = 0;
        divisions = 0;
        clock_t spstart, spstop;
        spstart = clock();
        primes = func(lower, upper, &additions, &divisions);
        spstop = clock();
        double time = static_cast<double>(spstop - spstart) / CLOCKS_PER_SEC;
        maxTime = std::max(maxTime, time);
        minTime = std::min(minTime, time);
        totalTime += time;
    }

    double averageTime = totalTime / numRuns;
    double averageSpeed = (upper - lower) / averageTime;

    int primesCount = primes.size();
    std::cout
        << message << ","
        << threads << ","
        << lower << ","
        << upper << ","
        << numRuns << ","
        << averageTime << ","
        << maxTime << ","
        << minTime << ","
        << additions << ","
        << divisions << ","
        << primesCount << ","
        << "speedup," // needs to be postprocessed due to being relative to fastest run time
        << averageSpeed << ","
        << "effective" // needs to be postprocessed due to being relative to fastest run time
        << std::endl;
}

template <typename T>
void benchmark(
    T func,
    std::string message)
{
    int MIN = 2;
    int MAX = MAX_BENCHMARK;

    std::vector<int> threads{1, 3, 6};
    std::vector<int> lower{MIN, MIN, MAX / 2};
    std::vector<int> upper{MAX, MAX / 2, MAX};

    for (auto &threadNum : threads)
    {
        for (int i = 0; i < 3; i++)
        {
            int lowerBound = lower[i];
            int upperBound = upper[i];

            measureTime(func, message, threadNum, lowerBound, upperBound);
        }
    }
}
