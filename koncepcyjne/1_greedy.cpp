#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../measure_time.cpp"

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }

    return true;
}

std::vector<int> greedy(int start, int end) {
    std::vector<int> primes;

    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main(int argc, char *argv[]) {
    int start = 2;
    int end = 20000000;

    if(argc == 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    }

    measureTime("Greedy:", greedy, start, end);
    return 0;
}
