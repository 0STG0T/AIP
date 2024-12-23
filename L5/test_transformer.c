
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sentence_transformer.c"

#define MAX_LINE_LEN 1000
#define MAX_TRANSFORMED_LEN 1000

int main() {
    FILE *input_file = fopen("test_sentences.txt", "r");

    char line[MAX_LINE_LEN];
    char transformed[MAX_TRANSFORMED_LEN];
    int line_number = 0;

    printf("Test Results:\n");
    while (fgets(line, sizeof(line), input_file)) {
        transform_sentence(line, transformed);

        printf("Test Case %d:\n", ++line_number);
        printf("Original: %s\n", line);
        printf("Transformed: %s\n", transformed);
        printf("---------------------------\n");
    }

    fclose(input_file);
    return 0;
}
