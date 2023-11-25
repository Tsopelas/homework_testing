#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize ("O3")
#define MAX_NUMBER 1000000000000000
#define MIN_NUMBER 1

int is_prime(unsigned long long n) {
    if (n < 2) {
        return 0;
    }
    if (n < 4){
        return 1;
    }
    if (n % 2 == 0 || n % 3 == 0){
        return 0;
    }
    for (unsigned long long i = 5; i * i <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0){
            return 0;
        }
    }
    return 1;
}

unsigned long long mirror(unsigned long long n){
    unsigned long long original = n;
    unsigned long long mirrored = 0;

    while (original != 0) {
        mirrored = mirrored * 10 + original % 10;
        original /= 10;
    }
    return mirrored;
  
}


int check(unsigned long long n, unsigned long long i) {
    unsigned long long reversed = mirror(n);
    
    // Check if n and reversed are both primes
    if (reversed != n) {
        // Check if n is not equal to its reversed form
        if (is_prime(i) == 1) {
            unsigned long long rev_root = i * i;
            if (rev_root == reversed * reversed) {
                if(is_prime(rev_root)) {
                    return 1;
                }
            }
        }
    }
    
    return 0;  // Not a palindromic prime square
}



int main(int argc, char **argv) {
    if (argc != 3) {
        printf("ERROR: MORE/LESS THAN 2 INPUTS\n");
        return 1;
    }
    unsigned long long low = atoll(argv[1]);
    unsigned long long high = atoll(argv[2]);
    if (low > high || low < MIN_NUMBER || high > MAX_NUMBER) {
        printf("INPUTS NEED TO MATCH THE LIMITS\n");
        return 1;
    }
    unsigned long long begin = sqrt(low);
    if (begin * begin < low) {
        ++begin;
    }
    unsigned long long sum = 0;
    for (unsigned long long i = begin; i * i <= high; i += 2) {
        unsigned long long sqr = i * i;
        printf("Checking square: %llu\n", sqr);
        if (check(sqr,i) == 1) {
            sum += sqr;
        }
    }
    printf("%lld\n",sum);
    return 0;
}
