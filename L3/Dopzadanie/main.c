#include <stdio.h>
#include <math.h>

// Функция, которую нужно проинтегрировать
double f(double x) {
    if (x <= 0) {
        return 0; // Возвращаем 0, если x не положительный
    }
    double term1 = log(asin(1 / pow(x, 6.0/7.0)));
    double term2 = cbrt(cos(1 / pow(x, 3.0/7.0)));
    return term1 * term2;
}

// Метод Симпсона
double simpson_integration(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i += 2) {
        sum += 4 * f(a + i * h);
    }
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * f(a + i * h);
    }

    return sum * h / 3;
}

// Метод правых прямоугольников
double right_rectangles_integration(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

int main() {
    double a, b;
    int n;

    while (1) {
        printf("Введите нижний предел интегрирования a (положительное число): ");
        if (scanf("%lf", &a) != 1) {
            printf("Ошибка ввода: ожидалось число.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
            continue;
        }

        if (a <= 0) {
            printf("Некорректный предел интегрирования: a должно быть положительным.\n");
            continue;
        }

        printf("Введите верхний предел интегрирования b (положительное число, больше a): ");
        if (scanf("%lf", &b) != 1) {
            printf("Ошибка ввода: ожидалось число.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
            continue;
        }

        if (b <= 0 || b <= a) {
            printf("Некорректный предел интегрирования: b должно быть положительным и больше a.\n");
            continue;
        }

        printf("Введите количество разбиений n (положительное целое число): ");
        if (scanf("%d", &n) != 1) {
            printf("Ошибка ввода: ожидалось целое число.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
            continue;
        }

        if (n <= 0) {
            printf("Некорректное количество разбиений: n должно быть положительным.\n");
            continue;
        }

        break;
    }

    double simpson_result = simpson_integration(a, b, n);
    double right_rectangles_result = right_rectangles_integration(a, b, n);

    printf("Результат интегрирования методом Симпсона: %lf\n", simpson_result);
    printf("Результат интегрирования методом правых прямоугольников: %lf\n", right_rectangles_result);

    return 0;
}