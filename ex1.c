#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//Function for rotating the given image by 90 degrees.
void rotateImage(const uint8_t* inputPixels, uint8_t* outputPixels, int width, int height, int inputPadding, int outputPadding) {
    // The main for runs through the x and y dimensions of the image and assembles the rotated output.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int inputIndex = (y * (width * 3 + inputPadding) + x * 3); // Calculate the input index.
            int outputIndex = ((width - x - 1) * (height * 3 + outputPadding) + y * 3); // Calculate the output index.
            // Perform the rotation.
            outputPixels[outputIndex] = inputPixels[inputIndex];
            outputPixels[outputIndex + 1] = inputPixels[inputIndex + 1];
            outputPixels[outputIndex + 2] = inputPixels[inputIndex + 2];
        }
    }
}

//Function for checking if the BMP image that was inputted can be read correctly.
int correction_test(uint8_t* header, int* inputPadding) {
    // First Check: Are the BMP Headers correct.
    if (fread(header, sizeof(uint8_t), 54, stdin) != 54) {
        fprintf(stderr, "Error reading BMP header\n");
        return 1; // Return 1 if yes.
    }
    // Second Check: Is the file .bmp?
    if (header[0] != 'B' || header[1] != 'M') {
        fprintf(stderr, "Error: Not a BMP file\n");
        return 1; // Return 1 if yes.
    }
    if (*(uint16_t*)&header[28] != 24) {
        // Third Check: Is the image 24-bit.
        fprintf(stderr, "Error: Only 24-bit BMP images are supported\n");
        return 1; // Return 1 if yes.
    }

    // Calculate input padding.
    int width = *(int*)&header[18]; /// Calculate original width.
    *inputPadding = (4 - (width * 3 % 4)) % 4; // Calculate padding.
    return 0; // Return 0 if all checks pass.
}

//The main function handles the input and correctly manages the rest of the functions.
int main(int argc, char** argv) {
    // Check if the command line argument is correct.
    if (argc != 1) {
        fprintf(stderr, "Error: Program needs to be called as ./fauxtoshop < input.bmp > output.bmp\n");
        return 1; //Return 1 if not.
    }

    uint8_t header[54]; // Assign static memory to the header table.
    int inputPadding; // Declare the padding of the original image.
    //Call the correction_test function to check whether the input image fits the criteria and at the same time calculate the padding.
    if (correction_test(header, &inputPadding)) {
        return 1; // Return 1 if it fails the check.
    }
    // Assemble original image dimensions.
    int width = *(int*)&header[18]; // Declare the original width.
    int height = *(int*)&header[22]; // Declae the original height.

    int outputPadding = (4 - (height * 3 % 4)) % 4; // Calculate output padding

    uint8_t* inputPixels = (uint8_t*)malloc(3 * width * height + inputPadding * height); // Assign dynamic memory to the table inputPixels.
    uint8_t* outputPixels = (uint8_t*)malloc(3 * height * width + outputPadding * width); // Assign dynamic memory to the table outputPixels.

    // Check if the input image can correctly open.
    if (fread(inputPixels, sizeof(uint8_t), 3 * width * height + inputPadding * height, stdin) != 3 * width * height + inputPadding * height) {
        fprintf(stderr, "Error reading image data\n");
        // Free memory from inputPixes and outputPixels if the program fails to read the image.
        free(inputPixels); // 
        free(outputPixels);
        return 1;
    }

    // Call the rotate function to perform the rotation.
    rotateImage(inputPixels, outputPixels, width, height, inputPadding, outputPadding);

    *(int*)&header[18] = height; // Calculate the output height.
    *(int*)&header[22] = width; // Calculate the input height.

    // Check if the output image's headers have correctly been calculated.
    if (fwrite(header, sizeof(uint8_t), 54, stdout) != 54) {
        fprintf(stderr, "Error writing BMP header\n");
        // Free memory from inputPixes and outputPixels if the rotation failed.
        free(inputPixels);
        free(outputPixels);
        return 1; // Return 1 if it failed.
    }

    // Check if the output image was rotated correctly.
    if (fwrite(outputPixels, sizeof(uint8_t), 3 * width * height + outputPadding * width, stdout) != 3 * width * height + outputPadding * width) {
        fprintf(stderr, "Error writing rotated image data\n");
        // Free memory from inputPixes and outputPixels if the rotation failed.
        free(inputPixels); 
        free(outputPixels);
        return 1; // Return 1 if it failed.
    }

    // Free memory from inputPixes and outputPixels.
    free(inputPixels);
    free(outputPixels);

    return 0; // Return 0 and end program.
}
