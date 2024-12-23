#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 6

// Выделение памяти под матрицу
double **allocate_matrix(int rows, int cols) {
    double **m = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) m[i] = malloc(cols * sizeof(double));
    return m;
}

// Освобождение памяти матрицы
void free_matrix(double **m, int rows) {
    for (int i = 0; i < rows; i++) free(m[i]);
    free(m);
}

// Копирование матрицы
void copy_matrix(double **src, double **dest, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            dest[i][j] = src[i][j];
}

// Ввод матрицы
void input_matrix(double **m, int rows, int cols) {
    printf("Введите матрицу %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            scanf("%lf", &m[i][j]);
}

// Вывод матрицы
void print_matrix(double **m, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) printf("%6.2lf ", m[i][j]);
        printf("\n");
    }
}

// Сложение матриц
double **add_matrix(double **A, double **B, int rows, int cols) {
    double **res = allocate_matrix(rows, cols);
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

// Вычитание матриц
double **sub_matrix(double **A, double **B, int rows, int cols) {
    double **res = allocate_matrix(rows, cols);
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

// Умножение матриц
double **mul_matrix(double **A, double **B, int rowsA, int colsA, int colsB) {
    double **res = allocate_matrix(rowsA, colsB);
    for (int i = 0; i < rowsA; i++) 
        for (int j = 0; j < colsB; j++) {
            res[i][j] = 0;
            for (int k = 0; k < colsA; k++) 
                res[i][j] += A[i][k] * B[k][j];
        }
    return res;
}

// Вычисление определителя
double determinant(double **m, int n) {
    if (n == 1) return m[0][0];
    if (n == 2) return m[0][0] * m[1][1] - m[0][1] * m[1][0];

    double det = 0;
    for (int k = 0; k < n; k++) {
        double **minor = allocate_matrix(n - 1, n - 1);
        for (int i = 1; i < n; i++) {
            int col_idx = 0;
            for (int j = 0; j < n; j++) {
                if (j != k) minor[i - 1][col_idx++] = m[i][j];
            }
        }
        det += (k % 2 == 0 ? 1 : -1) * m[0][k] * determinant(minor, n - 1);
        free_matrix(minor, n - 1);
    }
    return det;
}

// Построение минора матрицы
double **minor_matrix(double **m, int size, int row, int col) {
    double **minor = allocate_matrix(size - 1, size - 1);
    int r = 0, c = 0;
    for (int i = 0; i < size; i++) {
        if (i == row) continue;
        c = 0;
        for (int j = 0; j < size; j++) {
            if (j == col) continue;
            minor[r][c++] = m[i][j];
        }
        r++;
    }
    return minor;
}

// Поиск обратной матрицы через алгебраические дополнения
double **inverse_matrix(double **m, int n) {
    double det = determinant(m, n);
    if (fabs(det) < 1e-9) {
        printf("Матрица вырождена, обратной не существует.\n");
        return NULL;
    }

    double **inv = allocate_matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double **minor = minor_matrix(m, n, i, j);
            double minor_det = determinant(minor, n - 1);
            inv[j][i] = ( (i + j) % 2 == 0 ? 1 : -1 ) * minor_det / det;
            free_matrix(minor, n - 1);
        }
    }
    return inv;
}

// Приведение к главному ступенчатому виду (REF)
void ref_matrix(double **m, int rows, int cols) {
    int lead = 0;
    for (int r = 0; r < rows; r++) {
        if (lead >= cols) return;

        // Находим ненулевой ведущий элемент
        int i = r;
        while (fabs(m[i][lead]) < 1e-9) {
            i++;
            if (i == rows) {
                i = r;
                lead++;
                if (lead == cols) return;
            }
        }

        // Меняем строки местами
        if (i != r) {
            double *temp = m[i];
            m[i] = m[r];
            m[r] = temp;
        }

        // Обнуляем элементы ниже ведущего
        for (int k = r + 1; k < rows; k++) {
            if (fabs(m[k][lead]) > 1e-9) {
                double factor = m[k][lead] / m[r][lead];
                for (int j = lead; j < cols; j++) {
                    m[k][j] -= factor * m[r][j];
                }
            }
        }
        lead++;
    }
}