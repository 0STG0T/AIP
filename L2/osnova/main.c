#include <stdio.h>
#include <float.h>
#include "safe_input.c"

double min_xy(double * arr, int k, int x, int y){
    double min_value = 0;
    int first_min_index = 0;
    // поиск первого допустимого минимума (X <= b <= Y)
    for (;first_min_index < k;first_min_index++){
        if (arr[first_min_index] >= x && arr[first_min_index] <= y){
            min_value = arr[first_min_index];
            break;
        }
    }
    // поиск самого минимума
    for (int i=first_min_index+1;i<k;i++){
        if (arr[i] >= x && arr[i] <= y && arr[i] < min_value){
            min_value = arr[i];
        }
    }
    return min_value;
}

// поиск первого максимального элемента, возвращает его номер в массиве
int argmax(double * arr, int k){
    double max_value = arr[0];
    int min_i_for_max_value = 0;

    // поиск максимума
    for (int i=1;i<k;i++){
        // строгое неравенство чтоб в min_i_for_max_value не записывались не минимальные i
        if (arr[i] > max_value){
            max_value = arr[i];
            min_i_for_max_value = i;
        }
    }
    return min_i_for_max_value;
}   

double mean_of_elements_after_max(double * arr, int k){
    // первый номер максимального элемента
    int max_i = argmax(arr, k);
    if (max_i == k - 1){
        printf("Максимальный элемент последний!");
        exit(0);
    }
    // считаем среднее арифметическое этих элементов
    double mean = 0;

    for (int i=max_i+1;i<k;i++){
        mean += arr[i];
    }

    mean /= (k-max_i-1);

    return mean;
}

int main(){

    int k = 0, x = 0, y = 0;
    do {
        k = safe_input_int("Введите целое положительное значение k - количество элементов массива:");
    } while (k <= 0);
    
    x = safe_input_int("Введте целое число X:");
    y = safe_input_int("Введте целое число Y:");
    // обьявление массива 
    double arr[k];

    // ввод массива
    printf("Введите k вещественных чисел разделяя их переносом строки:\n");
    for (int i=0;i<k;i++){
        double element = safe_real_input("");
        arr[i] = element;
    }

    // Задание 1: расчитать min (b1,...,bk) для X i <= b_i <= Y массива
    double min_value = min_xy(arr, k, x, y);
    printf("Наименьший элемент в массиве, удовлетворяющий условию X <= b <= Y: %f\n", min_value);

    /* Задание 2: 
        Среднее арифметическое элементов, 
        расположенных после первого максимального элемента.
        Массив вещественный.
    */

    double mean = mean_of_elements_after_max(arr, k);

    printf("Среднее арифметическое элементов, расположенных после первого максимального элемента: %f\n", mean);
    
    return 0;
}