#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // isalnum() isdigit() isalpha()

#define MAX_STR_LEN 999    // максимальное количество символов в строке
#define MAX_COUNT_WORDS 30 // максимальное количество слов в предложении
#define MAX_LEN_WORD 10    // максимальное количество симовлов в слове

// функция ввода строки
char *get_original_str()
{
    char *input_str = (char *)malloc(MAX_STR_LEN);
    printf("Введите вашу строку:\n");
    fgets(input_str, MAX_STR_LEN - 1, stdin);
    return input_str;
}

// ищем индекс первой точки в строке
int get_first_dot_idx(const char *original_str)
{
    int dot_idx = 0;
    while (*original_str != '\0')
    {
        if (*original_str == '.')
            return dot_idx;
        original_str++;
        dot_idx++;
    }
    printf("Введённая строка не содержит точку.\n");
    exit(0);
}

// переворот слова
void reverse_word(const char *word, char *output) {
    int word_len = strlen(word); // Длина переворачиваемого слова
    int output_len = strlen(output); // Длина текущего output

    // Переворачиваем слово
    char reversed_word[100];
    for (int i = 0; i < word_len; i++) {
        reversed_word[i] = word[word_len - i - 1];
    }
    reversed_word[word_len] = '\0'; // Завершаем строку нулевым символом

    // Добавляем перевернутое слово в конец output
    strcat(output, reversed_word);

    // Добавляем пробел после перевернутого слова
    strcat(output, " ");
}

// проверяет, все ли символы (английский алфавит или цифра), если да то 1, если нет то 0
int isalnum_word(const char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalnum(word[i]) == 0)
            return 0;
    }
    return 1;
}

// проверяет есть ли в слове хотя бы одна цифорка
int has_digit_word(const char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (isdigit(word[i]))
            return 1;
    }
    return 0;
}

// основная функция
void print_words(const char *original_str, int dot_idx)
{
    int len_until_dot = dot_idx + 1;
    char *current_word = NULL;
    int len_curr_word = 0;
    int words_count = 0;

    char *copy_str = (char *)malloc(sizeof(char) * len_until_dot);
    char output[MAX_STR_LEN];
    output[0] = '\0';
    strncpy(copy_str, original_str, len_until_dot);
    // добавляет завершающий нулевой символ ('\0')
    copy_str[len_until_dot] = '\0';
    // вводим первый раз strtok.
    current_word = strtok(copy_str, " .");
    
    while (current_word != NULL)
    {
        // защита от превышения кол-ва слов
        if (words_count >= MAX_COUNT_WORDS)
        {
            printf("Введённая строка превышает допустимое значение слов.\n");
            output[0] = '\0';
            return;
        }

        // проверяем слово на недопустимые символы
        if (!isalnum_word(current_word))
        {
            printf("Введено слово с некорректными символами!\n");
            output[0] = '\0';
            return;
        }
        // считаем длину строки
        len_curr_word = strlen(current_word);
        // проверяем на превышение длины слова
        if (len_curr_word > MAX_LEN_WORD)
        {
            printf("Введённое слово превышает допустимое значение количества символов в слове.\n");
            output[0] = '\0';
            return;
        }
        // если нет ни одной цифры в слове, то не выводим его
        if (has_digit_word(current_word) == 0)
        {
            // двигаемся дальше
            current_word = strtok(NULL, " .");
            words_count++;
            continue;
        }
        // переворачиваем слово с цифрами
        reverse_word(current_word, output);
        // двигаемся дальше
        current_word = strtok(NULL, " .");
        words_count++;
    }
    printf("Обработанная строка:\n");
    printf("%s", output);
    printf("\nИсходная строка: \n%s", original_str);
    // очищаем копию строчки, над которой происходят преобразования
    free(copy_str);

    output[0] = '\0';
}

