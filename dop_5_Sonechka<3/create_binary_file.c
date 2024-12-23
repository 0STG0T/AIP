#include <stdio.h>

#define FILE_NAME "input_data.bin"

int main() {
    FILE *file = fopen(FILE_NAME, "wb"); // Открываем файл для записи в бинарном режиме
    if (file == NULL) {
        printf("Ошибка при создании файла '%s'!\n", FILE_NAME);
        return 1;
    }
    const int N = 10; // количество элементов для записи в файл
    int numbers[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Что хотим записать в файл
    fwrite(numbers, sizeof(int), N, file); // Записываем числа в файл

    fclose(file); 
    printf("Файл '%s' успешно создан.\n", FILE_NAME);
    return 0;
}