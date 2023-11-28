#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize ("O3")
#define MAX_NUMBER 1000000000000
#define MIN_NUMBER 1

int count(unsigned long long n) {
    int count = 0;
    long long mod;
    while (n > 0) {
        mod = n % 10;
        count++;
        n /= 10;
    }
    return count;
}

unsigned long long digit_sum(unsigned long long n){
    long long digit_sum = 0;
    long long mod;
    long long num = n;
    int digit_count = count(n);
    // CASE 0
    while (num > 0) {
        mod = num % 10;
        digit_sum += mod;
        num /= 10;
    }
    if (digit_sum * digit_sum == n) {
        return digit_sum;
    }
    digit_sum = 0;
    // CASE 1
    for (int i = digit_count-1; i >= 1 ; i--) {
        long long number = n;
        long long mod = 0;
        long long sum = 0;
        int divisor = pow(10,i);
        mod = number % divisor;
        sum += mod;
        number /= divisor;
        sum += number ;
        if (sum * sum == n) {
            return sum;
        }
    }
    //CASE 2

    digit_sum += num;
    return digit_sum;
}

int check (unsigned long long n) {
    unsigned long long number = digit_sum(n);
    if (number * number == n) {
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
