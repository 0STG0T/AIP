#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LIMIT 1000 // Максимальный размер буфера

// Функция для добавления числа в массив
void insert(int data[], int *count, int value) {
    if (*count < BUFFER_LIMIT) {
        data[(*count)++] = value; // Добавляем число и увеличиваем счётчик
    } else {
        printf("Предупреждение: буфер переполнен!\n");
    }
}

// Функция для вывода массива на экран
void show(int data[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main() {
    const char *input_file = "data.bin"; // Имя файла
    int limit;

    // Считываем пороговое значение
    printf("Введите граничное число: ");
    if (scanf("%d", &limit) != 1) {
        printf("Ошибка: введите корректное целое число!\n");
        return 1;
    }

    // Буферы для чисел
    int lower_buffer[BUFFER_LIMIT] = {0}; // Числа меньше граничного
    int upper_buffer[BUFFER_LIMIT] = {0}; // Числа больше или равные граничному
    int lower_count = 0; // Количество чисел в lower_buffer
    int upper_count = 0; // Количество чисел в upper_buffer

    // Открываем файл
    FILE *file = fopen(input_file, "rb");
    if (!file) {
        printf("Ошибка: невозможно открыть файл '%s'!\n", input_file);
        return 1;
    }

    int current_value;
    while (fread(&current_value, sizeof(int), 1, file) == 1) { // Читаем числа из файла
        if (current_value < limit) {
            insert(lower_buffer, &lower_count, current_value); // Добавляем в буфер ниже граничного
        } else {
            insert(upper_buffer, &upper_count, current_value); // Добавляем в буфер выше или равно граничному
        }
    }

    fclose(file); // Закрываем файл

    // Вывод результатов
    printf("Числа ниже границы %d:\n", limit);
    show(lower_buffer, lower_count);

    printf("Числа выше или равные границе %d:\n", limit);
    show(upper_buffer, upper_count);

    return 0;
}