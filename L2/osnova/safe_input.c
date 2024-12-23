// file to store safe input functions

#include <stdbool.h>
#include <string.h>

// to have HUGE_VAL only for strtod
#include <math.h>
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
    return m;
}

// simple string check
bool is_real(char *s){
    char real_alphabet[] = "0123456789.-";
    int s_len = strlen(s);

    // check if len is greater than 0
    if (s_len < 1){
        return false;
    }

    // check that no character out of alphabet
    for (int i=0; i<s_len;i++){
        bool flag = false; // suppose character is not in alpha

        for (int j=0;j<12;j++){
            if (s[i] == real_alphabet[j]){
                flag = true; // its in alpha
            }
        }
        if (flag != true){
            return false;
        }
    }

    // conuters for dots and minuses
    int dot_counter = 0, minus_counter = 0;

    for (int i=0; i<s_len;i++){
        if (s[i] == '.'){
            dot_counter++;

            // not more than 1 dot
            if (dot_counter > 1){
                return false;
            }
            // dot is not the first or last character
            if (i == 0 || i == s_len-1){
                return false;
            }
        } 
        // for minuses
        else{
            if (s[i] == '-'){
                minus_counter++;
                // no more than 1 minus
                if (minus_counter > 1){
                    return false;
                }

                // minus is not first element
                if (i > 0){
                    return false;
                }
            }
        }
    }
    // return true if nothing is wrong with the number
    return true;
}

// function that safely inputs a real number and returns it as double
// pre_input_str is defined because i have more than one different use for this funciton
double safe_real_input(char *pre_input_str) {

    char x[100];  
    printf("%s", pre_input_str);
    scanf("%s", x);  
    if (!is_real(x)) {
        printf("Please enter a real number with a . separator!\n");
        
        return safe_real_input(pre_input_str); // try again
    }

    
    double dx = strtod(x, NULL);
    // conversion error
    if (dx == HUGE_VAL || dx == -HUGE_VAL){
        printf("Conversion Fault!\n");
        return safe_real_input(pre_input_str); // try again
    }

    return dx;  // string to double
}
