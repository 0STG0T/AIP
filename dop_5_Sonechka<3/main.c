#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.c"

#define FILE_NAME "input_data.bin" // ПОМЕНЯЙТЕ ЕСЛИ У ВАС ДРУГОЙ ФАЙЛ

int main(){

    // инициализация очередей
    queue lower, higher;
    init_queue(&lower);
    init_queue(&higher);

    int c;

    printf("Введите ваше число C: ");
    scanf("%d", &c);

    // открываем файл
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Ошибка при чтении файла '%s'\n", FILE_NAME);
        exit(1);
    }

    int tmp;
    while (fread(&tmp, sizeof(int), 1, file) == 1) { // Читаем числа из файла
        if (tmp < c) {
            enqueue(&lower, tmp); // добавляем в очередь которая для элементов меньше С
        } else {
            enqueue(&higher, tmp); // добавляем в очередь которая для всех остальных элементов
        }
    }

    fclose(file); // закрываем файл

    // вывод результатов
    printf("Числа меньше C=%d:\n", c);
    while (len_queue(lower)){
        printf("%d ", dequeue(&lower));
    }

    printf("\nОстальные числа:\n");
    while (len_queue(higher)){
        printf("%d ", dequeue(&higher));
    }

    // очистка динамически выделенной памяти
    free_queue(&lower);
    free_queue(&higher);
}