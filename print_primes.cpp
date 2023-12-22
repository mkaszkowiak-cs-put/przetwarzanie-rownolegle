#include <iostream>
#include <vector>

void printPrimes(const std::vector<bool>& isPrime, int lower, int upper) {
    int count = 0, lineCount = 0;
    for (int i = lower; i <= upper; ++i) {
        if (isPrime[i]) {
            std::cout << i << " ";
            if (++lineCount % 10 == 0) std::cout << std::endl;
            ++count;
        }
    }
    std::cout << "\nZnaleziono " << count << " liczb pierwszych w zakresie od " << lower << " do " << upper << "." << std::endl;
}

void printPrimes(const std::vector<int>& primes) {
    for (size_t i = 0; i < primes.size(); ++i) {
        if (i > 0 && i % 10 == 0) {
            std::cout << std::endl;
        }
        std::cout << primes[i] << " ";
    }
    std::cout << "\nZnaleziono " << primes.size() << " liczb pierwszych." << std::endl;
}