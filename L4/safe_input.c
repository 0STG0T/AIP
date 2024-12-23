#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int safe_input_int(const char *prompt) {
    char int_alphabet[] = "-0123456789";

    char s[100];
    printf("%s", prompt); 
    scanf("%99s", s);

    int s_len = strlen(s);

    if (s_len < 1) {
        printf("Вы должны ввести число!\n");
        return safe_input_int(prompt);
    }

    // Проверка знака минус: если он есть, то он должен быть только первым символом
    int start_index = 0;
    if (s[0] == '-') {
        if (s_len == 1) { 
            printf("Введите корректное целое число!\n");
            return safe_input_int(prompt);
        }
        start_index = 1; // Начинаем проверку цифр со второго символа
    }

    // Проверяем, что каждый символ (кроме знака минус) принадлежит алфавиту цифр
    for (int i = start_index; i < s_len; i++) {
        bool flag = false; 
        for (int j = 1; j < 11; j++) { 
            if (s[i] == int_alphabet[j]) {
                flag = true; 
                break; 
            }
        }
        if (!flag) {
            printf("Введите корректное целое число!\n");
            return safe_input_int(prompt);
        }
    }

    // Преобразуем строку в целое число
    int m = atoi(s);
    if (m < 1){
        printf("Введите корректное целое число!\n");
        return safe_input_int(prompt);
    }
    return m;
}
