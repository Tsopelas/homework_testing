#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DIGITS 100

int arr[MAX_DIGITS];
int compositions[MAX_DIGITS];
int resultComposition[MAX_DIGITS];

void evaluateCompositions(int n, int i, int maxN) {
    if (n == 0) {
        // Copy the successful composition to resultComposition
        for (int k = 0; k < i; k++) {
            resultComposition[k] = compositions[k];
        }
    } else if (n > 0) {
        for (int k = 1; k <= maxN; k++) {  // Fix: Change < to <=
            arr[i] = k;
            evaluateCompositions(n - k, i + 1, maxN);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Need a number as a parameter.\n");
        return 1;
    }

    unsigned long long low = atoll(argv[1]);
    unsigned long long high = atoll(argv[2]);

    long long sum = 0;
    for (unsigned long long n = low; n <= high; n++) {
        double sqrtResult = sqrt(n);
        bool isSNumber = false;
        int N = strlen(strNum);
        if (sqrtResult == (int)sqrtResult) {
            resultComposition[0] = (int)sqrtResult;
            isSNumber = true;
        } else {
            for (int i = 0; i < N; i++) {
            arr[i] = 0;
            }
            evaluateCompositions(N, 0, N);
            for (int j = 0; j < N; j++) {
                int idx = 0;
                int total = 0;
                for (int i = 0; i < arr[j]; i++) {
                    compositions[i] = atoi(strNum + idx);
                    total += compositions[i];
                    idx += arr[j];
                }
                if (total == sqrtResult) {
                    isSNumber = true;
                    break;
                }
            }
        }
        if (isSNumber) {
            sum += n;
        }
    }
    printf("%lld\n",sum);
    return 0;
}
