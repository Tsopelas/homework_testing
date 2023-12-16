#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 100

char *getFileContents(char *filename, size_t *size);

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

    int size;
    if (size1 < size2) {
        size = size1;
    } else {
        size = size2;
    }

    int counter = 0;
    int max = 0;
    char max_comb[size];
    for (int i = 1; i < size; i++){
        if (file1Contents[i] == file2Contents[i]){
            counter++;
            char combination[counter];
            combination[0] = '\0'; // Initialize the string
            char temp[2] = {file1Contents[i], '\0'};
            strcat(combination,temp);
            if (counter > max){
                max = counter;
                printf("%s",combination);
            }
        }
        else{
            counter = 0;
        }
    }
    free(file1Contents);
    free(file2Contents);

    return 0;
}

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

    content[*size] = '\0';

    fclose(file);

    return content;
}
