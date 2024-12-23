
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sentence_transformer.c"

#define MAX_LINE_LEN 1000
#define MAX_TRANSFORMED_LEN 1000

int main() {

    char line[MAX_LINE_LEN];
    char transformed[MAX_TRANSFORMED_LEN];

    printf("Write your sentence:");
    fgets(line, MAX_LINE_LEN, stdin);

    printf("Test Results:\n");

    transform_sentence(line, transformed);

    printf("Original: %s\n", line);
    printf("Transformed: %s\n", transformed);

    return 0;
}
