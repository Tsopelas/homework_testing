#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculateA(int testNumber, int divisor) {
    return floor((float)testNumber / divisor);
}

int calculateB(int testNumber, int divisor) {
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
        int digits_a = floor(log10(a)) + 1;
        unsigned long long division = 1;
        unsigned long long mod;
        printf("Iteration %llu: a=%llu, b=%llu\n", j, a, b);
        for (int i = 1; i <= digits_a; i++) {
            division *= 10;
            unsigned long long temp1 = a;
            while (temp1 > 0) {
                mod = temp1 % division;
                temp1 /= division;
                sum1 = temp1 + mod + b;
                if (sum1 * sum1 == testNumber) {
                    printf("yes sum = %lld\n",sum1);
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
                    printf("yes sum = %lld\n",sum2);
                    break;
                }
                else {
                    unsigned long long temp3 = temp2;
                    while (temp3 > 0) {
                        mod2 = temp3 % division2;
                        temp3 /= division2;
                        temp3 = temp2;
                        sum2 = temp3 + temp2 + mod2 + a;
                        if (sum2 * sum2 == testNumber) {
                        printf("yes sum = %lld\n",sum2);
                        break;
                        }
                    }
                }
            }
        } 
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    int testNumber = atoll(argv[1]);
    recursiveNumberSplitting(testNumber);
    return 0;
}
