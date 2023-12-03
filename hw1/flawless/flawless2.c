#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize ("O3")
#define MAX_NUMBER 1000000000000
#define MIN_NUMBER 1

unsigned long long calculateA(unsigned long long testNumber, unsigned long long divisor) {
    return floor((float)testNumber / divisor);
}

unsigned long long calculateB(unsigned long long testNumber, unsigned long long divisor) {
    return testNumber % divisor;
}

unsigned long long recursiveNumberSplitting(unsigned long long testNumber) {
    unsigned long long sum1 = 0;
    unsigned long long sum2 = 0;
    int digits = floor(log10(testNumber)) + 1;
    
    for (unsigned long long j = 1; j <= digits; j++) { 
        unsigned long long divisor = pow(10, j);
        unsigned long long b = calculateB(testNumber, divisor);
        unsigned long long a = calculateA(testNumber, divisor);
        printf("Iteration %llu: a=%llu, b=%llu\n", j, a, b);
        int digits_a = floor(log10(a)) + 1;
        unsigned long long division = 1;
        unsigned long long mod;
        for (int i = 1; i <= digits_a; i++) {
            division *= 10;
            unsigned long long temp1 = a;
            while (temp1 > 0) {
                mod = temp1 % division;
                temp1 /= division;
                sum1 = temp1 + mod + b;
                if (sum1 * sum1 == testNumber) {
                    return sum1;
                }
            }
        }
        unsigned long long temp2 = b;
        int digits_b = floor(log10(b)) + 1;
        unsigned long long division2 = 1;
        unsigned long long mod2;
        for (int i = 1; i <= digits_b; i++) {
            division2 *= 10;
            unsigned long long temp2 = b;
            while (temp2 > 0) {
                mod2 = temp2 % division2;
                temp2 /= division2;// Default return if no matching conditions are met
                sum2 = temp2 + mod2 + a;
                if (sum2 * sum2 == testNumber) {
                    return sum2;
                }
            }
        } 
    }
    return 0; 
}



int check(unsigned long long n, unsigned long long i) {
    unsigned long long sum = recursiveNumberSplitting(n);
    if (sum == i) {
        printf("%lld\n",i);
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
    
    for (unsigned long long i = begin; i * i <= high; i ++) {
        register unsigned long long sqr = i * i;
        if (check(sqr,i)) {
            sum += sqr;
        }
    }
    
    printf("%lld\n",sum);
    return 0;
}
