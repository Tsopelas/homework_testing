#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize ("O3")
#define MAX_NUMBER 1000000000000
#define MIN_NUMBER 1

unsigned long long digit_separation(unsigned long long n){
    int count = 0;
    long long digit_sum = 0;
    do {
        n /= 10;
        ++count;
    } while (n != 0);
    if (count % 2 == 0) {
        while(n > 0) {
            long long mod = n % count*10 / 2; 
            digit_sum += mod;
            n = n / count*10 /2;    
        }
        if (digit_sum ^ 2 == n) {
            return 1;
        }
        
    }
}

int check(unsigned long long n) {
    if (digit_separation(n)^2 == n) {
        return 1;
    }
    return 0;
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
    long long sum = 0;
    for (unsigned long long i = begin; i * i <= high; i += 2) {
        register unsigned long long sqr = i * i;
        if (check(sqr)) {
            sum += sqr;
        }
    }
    printf("%lld\n",sum);
    return 0;
}
