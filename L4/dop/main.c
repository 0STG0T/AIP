#include <stdio.h>
#include <stdlib.h>
#include "matrix_operations.c"

int main() {
    int rowsA, colsA, rowsB, colsB;
    printf("Введите размер первой матрицы (не более %dx%d): ", MAX_SIZE, MAX_SIZE);
    scanf("%d %d", &rowsA, &colsA);
    if (rowsA > MAX_SIZE || colsA > MAX_SIZE) {
        printf("Ошибка: превышен максимальный размер.\n");
        return 1;
    }

    printf("Введите размер второй матрицы (не более %dx%d): ", MAX_SIZE, MAX_SIZE);
    scanf("%d %d", &rowsB, &colsB);
    if (rowsB > MAX_SIZE || colsB > MAX_SIZE) {
        printf("Ошибка: превышен максимальный размер.\n");
        return 1;
    }

    // Создаем и вводим две матрицы
    double **A = allocate_matrix(rowsA, colsA);
    double **B = allocate_matrix(rowsB, colsB);
    printf("Введите первую матрицу:\n");
    input_matrix(A, rowsA, colsA);
    printf("Введите вторую матрицу:\n");
    input_matrix(B, rowsB, colsB);

    int choice;
    printf("\nВыберите операцию:\n");
    printf("1. Сложение матриц\n");
    printf("2. Вычитание матриц\n");
    printf("3. Умножение матриц\n");
    printf("4. Обратная матрица для первой матрицы\n");
    printf("5. Приведение первой матрицы к главному ступенчатому виду\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    double **result = NULL;

    switch (choice) {
        case 1: // Сложение
            if (rowsA == rowsB && colsA == colsB) {
                result = add_matrix(A, B, rowsA, colsA);
                printf("\nРезультат сложения матриц:\n");
                print_matrix(result, rowsA, colsA);
                printf("\nГлавный ступенчатый вид:\n");
                ref_matrix(result, rowsA, colsA);
                print_matrix(result, rowsA, colsA);
                free_matrix(result, rowsA);
            } else {
                printf("Ошибка: размеры матриц должны совпадать для сложения.\n");
            }
            break;

        case 2: // Вычитание
            if (rowsA == rowsB && colsA == colsB) {
                result = sub_matrix(A, B, rowsA, colsA);
                printf("\nРезультат вычитания матриц:\n");
                print_matrix(result, rowsA, colsA);
                printf("\nГлавный ступенчатый вид (REF):\n");
                ref_matrix(result, rowsA, colsA);
                print_matrix(result, rowsA, colsA);
                free_matrix(result, rowsA);
            } else {
                printf("Ошибка: размеры матриц должны совпадать для вычитания.\n");
            }
            break;

        case 3: // Умножение
            if (colsA == rowsB) {
                result = mul_matrix(A, B, rowsA, colsA, colsB);
                printf("\nРезультат умножения матриц:\n");
                print_matrix(result, rowsA, colsB);
                printf("\nГлавный ступенчатый вид:\n");
                ref_matrix(result, rowsA, colsB);
                print_matrix(result, rowsA, colsB);
                free_matrix(result, rowsA);
            } else {
                printf("Ошибка: количество столбцов первой матрицы должно равняться количеству строк второй матрицы.\n");
            }
            break;

        case 4: // Обратная матрица
            if (rowsA == colsA) {
                result = inverse_matrix(A, rowsA);
                if (result) {
                    printf("\nОбратная матрица:\n");
                    print_matrix(result, rowsA, colsA);
                    printf("\nГлавный ступенчатый вид (REF):\n");
                    ref_matrix(result, rowsA, colsA);
                    print_matrix(result, rowsA, colsA);
                    free_matrix(result, rowsA);
                }
            } else {
                printf("Ошибка: матрица должна быть квадратной для нахождения обратной.\n");
            }
            break;

        case 5: // REF первой матрицы
            result = allocate_matrix(rowsA, colsA);
            copy_matrix(A, result, rowsA, colsA);
            printf("\nГлавный ступенчатый вид для первой матрицы:\n");
            ref_matrix(result, rowsA, colsA);
            print_matrix(result, rowsA, colsA);
            free_matrix(result, rowsA);
            break;

        default:
            printf("Ошибка: неверный выбор.\n");
    }

    // Освобождаем память
    free_matrix(A, rowsA);
    free_matrix(B, rowsB);
    return 0;
}