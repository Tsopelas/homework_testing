#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculateA(int testNumber, int divisor) {
    return floor((float)testNumber / divisor);
}

int calculateB(int testNumber, int divisor) {
    return testNumber % divisor;
}

unsigned long long breakdown(unsigned long long number,unsigned long long other_number,int divisor,unsigned long long original,unsigned long long temp) {
    if (number <= 0) {
        return 1;
    }
    unsigned long long mod = number % divisor;
    number /=  divisor;
    unsigned long long sum = number + mod + other_number;
    printf("%lld %lld %lld\n", number,mod,other_number);
    if (sum * sum == original && mod != 0){
        return sum;
    }
    int mod_digits = floor(log10(mod)) + 1;
    unsigned long long mod2;
    if (mod_digits > 1) {
        temp = mod;
        int divisor2 = 10;
        while (temp > 0) {
            mod2 = mod % divisor2;
            temp /= divisor2;
            sum = number + other_number + mod2 + temp;
            if (sum * sum == original && mod != 0){
                return sum;
            }
        }
    }
    return breakdown(number,other_number,divisor,original,temp);
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
        sum1 = a + b;
        if (sum1 * sum1 == testNumber) {
            printf("yes sum = %lld\n",sum1);
            break;
        }
        for (int i = 1; i <= digits_a; i++) {
            division *= 10;
            sum1 = breakdown(a,b,division,testNumber,a);
            if (sum1 != 1) {
                printf("yes sum = %lld\n",sum1);
                break;
            }
        }
        unsigned long long temp2 = b;
        int digits_b = floor(log10(b)) + 1;
        unsigned long long division2 = 1;
        unsigned long long mod2;
        for (int i = 1; i <= digits_b; i++) {
            division *= 10;
            sum2 = breakdown(b,a,division,testNumber,b);
            if (sum2 * sum2 == testNumber) {
                printf("yes sum = %lld\n",sum2);
                break;
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
