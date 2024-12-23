#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "safe_input.c"

// Функция проверки корректности ввода числа с плавающей точкой
bool is_valid_float(const char *str) {
    int len = strlen(str);
    if (len == 0) return false; // Пустая строка
    int dot_count = 0;
    int sign_count = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            dot_count++;
            if (dot_count > 1) return false; // Только одна точка допустима
        } else if (str[i] == '-' || str[i] == '+') {
            if (i != 0) return false; // Знак разрешен только в начале
            sign_count++;
            if (sign_count > 1) return false;
        } else if (str[i] < '0' || str[i] > '9') {
            return false; // Не цифра
        }
    }

    return dot_count <= 1; // Корректно, если не более одной точки
}

// Функция для считывания числа с плавающей точкой с проверкой ввода
float input_float() {
    char buffer[100];
    while (true) {
        printf("Введите элемент массива: ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Убираем символ новой строки
            if (strlen(buffer) == 0) { // Проверяем пустой ввод
                printf("Некорректный ввод. Введите число с плавающей точкой.\n");
                continue;
            }
            if (is_valid_float(buffer)) {
                return strtof(buffer, NULL);
            } else {
                printf("Некорректный ввод. Введите число с плавающей точкой.\n");
            }
        } else {
            printf("Ошибка чтения ввода. Попробуйте еще раз.\n");
        }
    }
}

// Функция для создания массива
float* create_array(int size) {
    return (float*)malloc(size * sizeof(float));
}

// Функция для заполнения массива
void fill_array(float *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = input_float();
    }
}

// Функция для вывода массива
void print_array(const float *array, int size) {
    printf("Массив: ");
    for (int i = 0; i < size; i++) {
        printf("%.2f ", array[i]);
    }
    printf("\n");
}

// Функция для модификации массива с реальным удалением элементов
float* modify_array(float *array, int *size) {
    int new_size = *size;
    for (int i = 1; i < new_size - 1; ) {
        if (array[i] > 0 && array[i - 1] < 0 && array[i + 1] < 0) {
            // Сдвиг элементов влево
            for (int j = i; j < new_size - 1; j++) {
                array[j] = array[j + 1];
            }
            new_size--; // Уменьшаем логический размер массива

            // Реально уменьшаем размер массива
            // Проверка на нулевой размер
            if (new_size == 0){
                free(array);
                printf("\n");
                exit(0);
            }
            array = realloc(array, new_size * sizeof(float));
            
        } else {
            i++;
        }
    }

    *size = new_size; // Обновляем логический размер массива
    return array;
}

int main() {
    int size;
    
    /*while (scanf("%d", &size) != 1 || size <= 0) {
        printf("Некорректный ввод. Введите положительное целое число: ");
        while (getchar() != '\n'); // Очищаем буфер ввода
    }*/
    size = safe_input_int("Введите размер массива: ");
    while (getchar() != '\n');

    float *array = create_array(size);
    if (!array) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    printf("Заполните массив:\n");
    fill_array(array, size);

    printf("Исходный ");
    print_array(array, size);

    array = modify_array(array, &size);

    printf("Модифицированный ");
    print_array(array, size);

    free(array);
    return 0;
}