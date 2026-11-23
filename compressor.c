
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Compress the input string
void compress(char input[], char output[]) {
    int i = 0;
    int j = 0;

    while (input[i] != '\0') {
        int count = 1;

        while (input[i] == input[i + 1]) {
            count++;
            i++;
        }

        j += sprintf(output + j, "%d#%d;",
                     count, (unsigned char)input[i]);

        i++;
    }

    output[j] = '\0';
}

// Decompress the encoded string
void decompress(char input[], char output[]) {
    int i = 0;
    int j = 0;

    while (input[i] != '\0') {
        char *end;

        int count = strtol(input + i, &end, 10);

        if (*end != '#') {
            printf("Invalid compressed data!\n");
            output[0] = '\0';
            return;
        }

        i = (int)(end - input) + 1;

        int ascii = strtol(input + i, &end, 10);

        if (*end != ';' || count < 1 ||
            ascii < 0 || ascii > 255 ||
            j + count >= 3000) {
            printf("Invalid compressed data!\n");
            output[0] = '\0';
            return;
        }

        for (int k = 0; k < count; k++) {
            output[j++] = (char)ascii;
        }

        i = (int)(end - input) + 1;
    }

    output[j] = '\0';
}

int main() {
    char input[500];
    char compressed[3000];
    char decompressed[3000];

    int choice;

    while (1) {
        printf("\n===== TEXT COMPRESSOR =====\n");
        printf("1. Compress Text\n");
        printf("2. Decompress Text\n");
        printf("3. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 1;
        }

        getchar();

        if (choice == 3) {
            printf("Thank you!\n");
            break;
        }

        if (choice != 1 && choice != 2) {
            printf("Invalid choice!\n");
            continue;
        }

        printf("Enter your text: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error!\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (choice == 1) {
            compress(input, compressed);

            printf("\nOriginal Text: %s\n", input);
            printf("Compressed Text: %s\n", compressed);

            int originalSize = strlen(input);
            int compressedSize = strlen(compressed);

            printf("Original Size: %d bytes\n", originalSize);
            printf("Compressed Size: %d bytes\n", compressedSize);

            if (originalSize > 0) {
                float reduction =
                    (1.0 - (float)compressedSize / originalSize)
                    * 100;

                printf("Space Reduction: %.2f%%\n", reduction);
            }
        }
        else {
            decompress(input, decompressed);

            if (decompressed[0] != '\0') {
                printf("\nDecompressed Text: %s\n",
                       decompressed);
            }
        }
    }

    return 0;
}
