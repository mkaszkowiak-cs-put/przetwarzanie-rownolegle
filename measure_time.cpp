#include <iostream>
#include <time.h>

template <typename Func, typename... Args>
void measureTime(std::string message, Func func, Args... args)
{
    const int numRuns = 30;
    double totalTime = 0.0;

    for (int i = 0; i < numRuns; ++i)
    {
        clock_t spstart, spstop;
        spstart = clock();
        func(args...);
        spstop = clock();
        double time = static_cast<double>(spstop - spstart) / CLOCKS_PER_SEC;
        std::cout << message << " Run " << (i + 1) << ": " << time << " seconds" << std::endl;
        totalTime += time;
    }

    double averageTime = totalTime / numRuns;
    std::cout << message << " Average: " << averageTime << " seconds" << std::endl;
}