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
    if (argc < 2) {
        printf("Need a number as a parameter.\n");
        return 1;
    }

    char *strNum = argv[1];

    for (int i = 0; strNum[i] != '\0'; i++) {
        if (!isdigit((unsigned char)strNum[i])) {
            printf("Input parameter must be a whole number. No decimals, no negatives.\n");
            return 1;
        }
    }

    int num = atoi(strNum);
    double sqrtResult = sqrt(num);
    printf("Checking if %s with square root %.1lf is an S-Number\n", strNum, sqrtResult);
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
        for (int i = 0; i < N; i++) {
            printf("%d", resultComposition[i]);
            if (resultComposition[i + 1] != 0) {
                printf(" + ");
            }
        }
        printf("= %.1lf\n", sqrtResult);
        printf("%s is an S-Number\n", strNum);
    } else {
        printf("%s doesn't look like an S-Number\n", strNum);
    }

    return 0;
}
