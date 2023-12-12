#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void rotateImage(const uint8_t* inputPixels, uint8_t* outputPixels, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int inputIndex = (y * width + x) * 3;
            int outputIndex = ((width - x - 1) * height + y) * 3;

            outputPixels[outputIndex] = inputPixels[inputIndex];
            outputPixels[outputIndex + 1] = inputPixels[inputIndex + 1];
            outputPixels[outputIndex + 2] = inputPixels[inputIndex + 2];
        }
    }
}

int correction_test(uint8_t* header){
    if (fread(header, sizeof(uint8_t), 54, stdin) != 54) {
        printf("Error reading BMP header\n");
        return 1;
    }
    if (header[0] != 'B' || header[1] != 'M') {
        fprintf(stderr, "error: not a BMP file\n");
        return 1;
    }
    if (*(uint16_t*)&header[28] != 24) {
        fprintf(stderr, "Only 24-bit BMP images are supported\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 1) {
        printf("Error: Program needs to be called as ./fauxtoshop < input.bmp > output.bmp\n");
        return 1;
    }
    uint8_t header[54];
    if (correction_test(header)){
        return 1;
    }

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];


    uint8_t* inputPixels = (uint8_t*)malloc(3 * width * height);
    uint8_t* outputPixels = (uint8_t*)malloc(3 * width * height);

    if (fread(inputPixels, sizeof(uint8_t), 3 * width * height, stdin) != 3 * width * height) {
        fprintf(stderr, "Error reading image data\n");
        free(inputPixels);
        free(outputPixels);
        return 1;
    }

    rotateImage(inputPixels, outputPixels, width, height);

    *(int*)&header[18] = height;
    *(int*)&header[22] = width;

    if (fwrite(header, sizeof(uint8_t), 54, stdout) != 54) {
        fprintf(stderr, "Error writing BMP header\n");
        free(inputPixels);
        free(outputPixels);
        return 1;
    }

    if (fwrite(outputPixels, sizeof(uint8_t), 3 * width * height, stdout) != 3 * width * height) {
        fprintf(stderr, "Error writing rotated image data\n");
        free(inputPixels);
        free(outputPixels);
        return 1;
    }

    free(inputPixels);
    free(outputPixels);

    return 0;
}
