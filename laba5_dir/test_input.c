#include "laba5.c"
#include <stdio.h>

int main()
{
    // инициализация и ввод строки
    char *original_str = NULL;
    original_str = get_original_str();

    // выполняем нашу программу
    int first_dot_idx = get_first_dot_idx(original_str);

    print_words(original_str, first_dot_idx);

    free(original_str);
    return 0;
}