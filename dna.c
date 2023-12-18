#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 100

char *getFileContents(char *filename, size_t *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    int c;
    size_t capacity = INITIAL_CAPACITY;
    *size = 0;
    char *content = (char *)malloc(capacity * sizeof(char));

    if (content == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    while ((c = fgetc(file)) != EOF) {
        if (c == 'A' || c == 'C' || c == 'T' || c == 'G') {
            content[(*size)++] = c;

            if (*size == capacity) {
                capacity *= 2;
                content = (char *)realloc(content, capacity * sizeof(char));

                if (content == NULL) {
                    perror("Error reallocating memory");
                    fclose(file);
                    return NULL;
                }
            }
        }
    }

    content[*size] = '\0';

    fclose(file);

    return content;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    size_t size1;
    char *file1Contents = getFileContents(argv[1], &size1);
    if (file1Contents == NULL) {
        return 2;
    }

    size_t size2;
    char *file2Contents = getFileContents(argv[2], &size2);
    if (file2Contents == NULL) {
        free(file1Contents);
        return 3;
    }

    int maxLen = 0; 
    int endIndex = 0;  
    int **commonLengths = (int **)malloc((size1 + 1) * sizeof(int *));
    for (int i = 0; i <= size1; i++) {
        commonLengths[i] = (int *)malloc((size2 + 1) * sizeof(int));
    }
    for (int i = 0; i <= size1; i++){
        for (int j = 0; j <= size2; j++) {
            if (i == 0 || j == 0)
                commonLengths[i][j] = 0;
            else if (file1Contents[i - 1] == file2Contents[j - 1]) {
                commonLengths[i][j] = commonLengths[i - 1][j - 1] + 1;
                if (commonLengths[i][j] > maxLen) {
                    maxLen = commonLengths[i][j];
                    endIndex = i - 1;
                }
            } else {
                commonLengths[i][j] = 0;
            }
        }
    }

    if (maxLen > 0) {
        for (int i = endIndex - maxLen + 1; i <= endIndex; i++) {
            printf("%c", file1Contents[i]);
        }
    }
    printf ("\n");
    for (int i = 0; i <= size1; i++) {
        free(commonLengths[i]);
    }
    free(commonLengths);
    free(file1Contents);
    free(file2Contents);

    return 0;
}
