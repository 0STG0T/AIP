#include <stdlib.h>
#include <string.h>
#include "laba5.c"

#define MAX_LINE_LEN 1000
#define MAX_TRANSFORMED_LEN 1000

int main()
{
    FILE *input_file = fopen("./text_strings.txt", "r");

    char current_string[MAX_LINE_LEN];
    char changed[MAX_TRANSFORMED_LEN];
    int line_idx = 0;

    while (fgets(current_string, sizeof(current_string), input_file))
    {
        // выполняем нашу программу обработки

        int first_dot_idx = get_first_dot_idx(current_string);
        print_words(current_string, first_dot_idx);

        printf("\n\n");

        // очищаем наши строки чтоб ничего не наслаивалось.
        char current_string[MAX_LINE_LEN];
        char changed[MAX_TRANSFORMED_LEN];
    }

    fclose(input_file);
    return 0;
}