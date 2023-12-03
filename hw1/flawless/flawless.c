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

unsigned long long breakdown(unsigned long long number,unsigned long long other_number,int divisor,unsigned long long original) {
    if (number <= 0) {
        return 1;
    }
    unsigned long long mod;
    mod = number % divisor;
    number /=  divisor;
    unsigned long long sum = number + mod + other_number;
    if (sum * sum == original){
        return sum;
    }
    return breakdown(number,other_number,divisor,original);
}

unsigned long long recursiveNumberSplitting(unsigned long long testNumber) {
    unsigned long long sum1 = 0;
    unsigned long long sum2 = 0;
    int digits = floor(log10(testNumber)) + 1;
    for (unsigned long long j = 1; j <= digits; j++) { 
        unsigned long long divisor = pow(10, j);
        unsigned long long b = calculateB(testNumber, divisor);
        unsigned long long a = calculateA(testNumber, divisor);
        int digits_a = floor(log10(a)) + 1;
        unsigned long long division = 1;
        unsigned long long mod;

        sum1 = a + b;
        if (sum1 * sum1 == testNumber) {
            return sum1;
        }
        for (int i = 1; i <= digits_a; i++) {
            division *= 10;
            sum1 = breakdown(a,b,division,testNumber);
            if (sum1 != 1) {
                return sum1;
            }
        }
        unsigned long long temp2 = b;
        int digits_b = floor(log10(b)) + 1;
        unsigned long long division2 = 1;
        unsigned long long mod2;
        for (int i = 1; i <= digits_b; i++) {
            division *= 10;
            sum2 = breakdown(b,a,division,testNumber);
            if (sum2 * sum2 == testNumber) {
                return sum2;
            }
        }
    }
}



int check(unsigned long long n, unsigned long long i) {
    unsigned long long sum = recursiveNumberSplitting(n);
    if (sum == i) {
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
            printf("%lld\n",sqr);
            sum += sqr;
        }
    }
    
    return 0;
}
