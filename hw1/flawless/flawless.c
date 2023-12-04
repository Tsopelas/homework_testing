#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma GCC optimize ("O3")
#define MAX_NUMBER 1000000000000
#define MIN_NUMBER 1

//Function to separate last digits from the number.
unsigned long long decompute_B(unsigned long long testNumber, unsigned long long divisor) {
    return testNumber % divisor;
}
//Function to separate first digits from the number.
unsigned long long decompute_A(unsigned long long testNumber, unsigned long long divisor) {
    return floor((float)testNumber / divisor);
}

//The decypher function runs the basic mod/div analyzation using recursion and returns sum to the brute force function.
unsigned long long decypher(unsigned long long number,unsigned long long other_number,int divisor,unsigned long long original) {
    if (number <= 0) {
        return 1;
    }
    unsigned long long mod;
    mod = number % divisor;
    number /=  divisor;
    unsigned long long sum = number + mod + other_number;
    if (sum * sum == original && mod != 0 && number != 0){
        return sum;
    }
    unsigned long long mod_other = other_number % 10;
    unsigned long long div = other_number / 10;
    sum = number + mod + mod_other + div;
    if (sum * sum == original && mod != 0 && number != 0){
        return sum;
    }
    return decypher(number,other_number,divisor,original);
}

//The brute force function breaks up the number into parts and calls the decypher function back and forth for each of its digit combinations in order to check all possible sums.
unsigned long long brute_force_analyze(unsigned long long testNumber) {
    unsigned long long summary = 0;
    int count_digits = floor(log10(testNumber)) + 1;
    for (unsigned long long i = 1; i <= count_digits; i++) { 
        unsigned long long divisor = pow(10, i);
        unsigned long long a = decompute_A(testNumber, divisor);
        unsigned long long b = decompute_B(testNumber, divisor);
        int digits_a = floor(log10(a)) + 1;
        unsigned long long division = 1;
        summary = a + b;
        if (summary * summary == testNumber) {
            return summary;
        }
        for (int j = 1; j <= digits_a; j++) {
            division *= 10;
            summary = decypher(a,b,division,testNumber);
            if (summary != 1) {
                return summary;
            }
        }
        unsigned long long temp2 = b;
        int digits_b = floor(log10(b)) + 1;
        division = 1;
        for (int j = 1; j <= digits_b; j++) {
            division *= 10;
            summary = decypher(b,a,division,testNumber);
            if (summary != 1) {
                return summary;
            }
        }
    }
}

//The flawless_check function checks if the sum of a numbers digits equals the square root of the number, meaning its a flawless square.
int flawless_check(unsigned long long n, unsigned long long i) {
    unsigned long long sum = brute_force_analyze(n); // Call brute force for number n.
    // Check if the number is a flawless square.
    if (sum == i) {
        return 1; //Return 1 if it is.
    }
    return 0; //Return 0 if it's not.
}

// The main function is responsible for reading and calculating the basic inputs from the user.
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
        if (flawless_check(sqr,i)) {
            sum += sqr;
        }
    }
    printf("%lld\n",sum);
    return 0;
}
