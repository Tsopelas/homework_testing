#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_NUMBER 1000000000000
#define MIN_NUMBER 1
#define MAX_DIGITS 100

long long arr[MAX_DIGITS];
long long compositions[MAX_DIGITS];
long long resultComposition[MAX_DIGITS];

void evaluateCompositions(int n, int i, int maxN, char *strNum) {
    if (n == 0) {
        // Copy the successful composition to resultComposition
        for (int k = 0; k < i; k++) {
            resultComposition[k] = compositions[k];
        }
    } else if (n > 0) {
        for (int k = 1; k <= maxN; k++) {
            arr[i] = k;
            int idx = i > 0 ? compositions[i - 1] : 0;
            int digit = atoi(strNum + idx);
            compositions[i] = digit;
            evaluateCompositions(n - digit, i + 1, maxN, strNum);
        }
    }
}

int check(int n) {
    char strNum[MAX_DIGITS];
    sprintf(strNum, "%d", n);
    int N = strlen(strNum);

    double sqrtResult = sqrt(n);
    printf("Checking if %s with square root %.1lf is an S-Number\n", strNum, sqrtResult);
    int isSNumber = 0;
    resultComposition[0] = (int)sqrtResult;

    for (int i = 0; i < N; i++) {
        arr[i] = 0;
    }

    evaluateCompositions(N, 0, N, strNum);

    int total = 0;
    for (int j = 0; j < N; j++) {
        total += compositions[j];
    }

    if (total == (int)sqrtResult) {
        isSNumber = 1;
    }

    if (isSNumber) {
        for (int i = 0; i < N; i++) {
            printf("%lld", resultComposition[i]);
            if (resultComposition[i + 1] != 0) {
                printf(" + ");
            }
        }
        printf("= %.1lf\n", sqrtResult);
        printf("%s is an S-Number\n", strNum);
    } else {
        printf("%s doesn't look like an S-Number\n", strNum);
    }

    return isSNumber;
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
    printf("%lld\n", sum);
    return 0;
}
