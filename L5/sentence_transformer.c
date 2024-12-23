#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 10           // Максимальная длина слова
#define MAX_SENTENCE_LEN 1000     // Максимальная длина предложения
#define MAX_WORDS_COUNT 30        // Максимальное количество слов в предложении

// Функция для проверки, является ли символ буквой или цифрой
int is_letter_or_digit(char ch) {
    return ((ch >= 'A' && ch <= 'Z') ||  
            (ch >= 'a' && ch <= 'z') || 
            (ch >= '0' && ch <= '9'));   
}

// Функция для проверки, является ли символ допустимым (буква, цифра или символ пунктуации)
int is_valid_char(char ch) {
    return ((ch >= 'A' && ch <= 'Z') ||  
            (ch >= 'a' && ch <= 'z') || 
            (ch >= '0' && ch <= '9')) ||
            (ch == '.' || ch == ',' || ch == '!' || ch == '?' || ch == ' ' || ch == '\0' || ch == '\n');  
}

// Функция для очистки слова от небуквенных и нецифровых символов в конце
void clean_word(const char *input, char *output) {
    int len = strlen(input);
    int end = len - 1;

    // Удаляем небуквенные и нецифровые символы с конца слова
    while (end >= 0 && !is_letter_or_digit(input[end])) {
        end--;
    }

    // Копируем очищенное слово в output
    strncpy(output, input, end + 1);
    output[end + 1] = '\0';
}

// Функция для трансформации слова (перемещение последнего символа в начало)
void transform_word(char *word) {
    int len = strlen(word);
    if (len > 1) {
        int last_index = len - 1;

        // Находим индекс последнего буквенного или цифрового символа
        while (last_index > 0 && !is_letter_or_digit(word[last_index])) {
            last_index--;
        }

        // Перемещаем последний символ в начало слова
        char tmp = word[last_index];
        for (int i = last_index; i > 0; i--) {
            word[i] = word[i - 1];
        }
        word[0] = tmp;
    }
}

// Функция для трансформации предложения
void transform_sentence(const char *sentence, char *output) {

    // Находим индекс первой точки в предложении
    int dot_index = strcspn(sentence, ".");
    if (dot_index < 0){
        output[0] = '\0';
        strcat(output, "Check you input!!!");
        return;
    }

    // Проверяем, не превышает ли длина предложения максимально допустимую
    if (strlen(sentence) > MAX_SENTENCE_LEN){
        output[0] = '\0';
        strcat(output, "Sentence is too big!");
        return;
    }

    // Проверяем, являются ли все символы в предложении допустимыми
    for (int i=0;i<strlen(sentence);i++){
        if (!is_valid_char(sentence[i])){
            output[0] = '\0';
            strcat(output, "Check you input!!!");
            return;
        }
    }

    // Массив для хранения слов
    char words[MAX_WORDS_COUNT][MAX_WORD_LEN];
    int word_count = 0;

    // Временная строка для работы с предложением
    char temp_sentence[MAX_SENTENCE_LEN];
    strncpy(temp_sentence, sentence, MAX_SENTENCE_LEN);

    // Индекс последнего символа в предложении
    int last_character_index = dot_index;

    // Заменяем все символы после точки на точку и завершаем строку
    while (!is_letter_or_digit(temp_sentence[last_character_index]) && last_character_index > 0)
    {
        temp_sentence[last_character_index] = '.';
        temp_sentence[last_character_index+1] = '\0';
        last_character_index--;
    }
    
    // Завершаем строку после точки
    temp_sentence[dot_index+1] = '\0';

    // Разбиваем предложение на слова
    char *token = strtok(temp_sentence, " ");
    while (token != NULL) {
        
        // Проверяем, не превышает ли длина слова максимально допустимую
        if (strlen(token) > MAX_WORD_LEN){
            output[0] = '\0';
            strcat(output, "Oh... your word is so big!!!");
            return;
        }

        // Копируем слово в массив слов
        strncpy(words[word_count], token, MAX_WORD_LEN);
        word_count++;

        // Проверяем, не превышает ли количество слов максимально допустимое
        if (word_count >= MAX_WORDS_COUNT){
            output[0] = '\0';
            strcat(output, "Too many words!!!\n\n");
            return;
        }

        // Получаем следующее слово
        token = strtok(NULL, " ");
    }

    // Очищаем последнее слово от небуквенных и нецифровых символов
    char cleaned_last_word[MAX_WORD_LEN];
    clean_word(words[word_count - 1], cleaned_last_word);

    // Инициализируем выходной буфер
    output[0] = '\0';

    // Обрабатываем каждое слово, кроме последнего
    for (int i = 0; i < word_count - 1; i++) {
        char cleaned_current_word[MAX_WORD_LEN];
        clean_word(words[i], cleaned_current_word);

        // Сравниваем очищенные слова
        if (strcmp(cleaned_current_word, cleaned_last_word) != 0) {
            transform_word(words[i]);
            strcat(output, words[i]);
            if (i < word_count - 2) {
                strcat(output, " ");
            }
        }
    }
}