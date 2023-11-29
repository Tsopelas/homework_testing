#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max_number 1000000000000000
#define min_number 1
#pragma GCC optimize ("O3")

<<<<<<< HEAD
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
=======
int count_digits(long long n){
    int count;
    do {
        n /= 10;
        ++count;
    } 
    while (n != 0);
    return count;
}

long long digit_separation(long long n,long long percentage,int count) {
    long long mod;
    long long sum_d;
    long long number = n;

    long long tempNumber = number;

    while (tempNumber > 0) {
        mod = tempNumber % 10;
        tempNumber /= 10; 
        if ((mod + tempNumber) ^ 2 == n){
            sum_d += n;
        }
    }
    return sum_d;
}

int check(long long n){
    long long num = n;
    long long perc = 10;
    
    if (digit_separation(num,perc,count_digits(n))^2 == n) {
>>>>>>> bc80f9a (upd)
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    unsigned long long low = atoll(argv[1]);
    unsigned long long high = atoll(argv[2]);
    if (low > high || low < min_number || high > max_number){
        printf("error\n");
        return 1;
    }
    unsigned long long begin = sqrt(low);
    if (begin * begin < low) {
        ++begin; 
    }
    unsigned long long sum = 0;
    for (unsigned long long i = begin; i * i <= high; i += 2) {
        register unsigned long long sqr = i * i;
        if (check(sqr)) {
            sum += sqr;
        }
    }
    printf("%lld\n",sum);
    return 0;
}