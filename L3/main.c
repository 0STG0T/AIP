#include <stdio.h>
#include "safe_input.c"

#define N 2 // Задаем размер матрицы


// функция ввода матрицы
void input_matrix(int matrix[N][N]);

// функция вывода исходной матрицы
void print_matrix(int matrix[N][N]);

// функция вывода матрицы в заданном порядке
void print_matrix_in_order(int matrix[N][N]);


int main(){
    // инициализация матрицы
    int matrix[N][N];

    // ввод матрицы
    input_matrix(matrix);

    // вывод заданной матрицы
    print_matrix(matrix);

    // вывод матрицы в заданном порядке
    print_matrix_in_order(matrix);
}

void input_matrix(int matrix[N][N]){
    printf("Приступим к вводу квадратной матрицы порядка %d.\n", N);
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("Введите элемент матрицы [%d, %d]: ", i, j);
            matrix[i][j] = safe_input_int("");
        }
    }
    printf("\n");
}

void print_matrix(int matrix[N][N]){
    printf("Введенная вами матрица:\n");
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_matrix_in_order(int matrix[N][N]){
    printf("Последовательный вывод матрицы в указанном порядке:\n");
    // выводим первый элемент последовательности
    printf("%d\n", matrix[N-1][0]);
    // я выбрал идти по главной диагонали снизу вверх
    for (int i=N-2;i>=0;i--){
        // вывод горизонтальной части угла слева на право, включая вершину угла
        for (int j=0;j<=(N-1 - i);j++){
            printf("%d ", matrix[i][j]);
        }
        // вывод вертикальной части угла сверху вниз, не включая вершину угла
        for (int j=i+1;j<N;j++){
            printf("%d ", matrix[j][N-1 - i]);
        }
        printf("\n");
    }
}