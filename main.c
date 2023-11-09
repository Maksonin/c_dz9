#include <stdio.h>
#include <string.h>

#include "mylib.h"

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);

int main(void){
    hello();
    char str[] = "Put the task number (1-6) - ";

    switch (setIntVar(str)){
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4();
            break;
        case 5:
            task5();
            break;
        case 6:
            task6();
            break; 
        default:
            printf("whaaa?\n");
            break;           
    }
}

/* Задача 1. В файле .txt даны два слова не более 100 символов каждое, разделенные
одним пробелом. Найдите только те символы слов, которые встречаются в
обоих словах только один раз. Напечатайте их через пробел в файл .txt в
лексикографическом порядке. */
#define SIZE1 100
void task1(void){
    char word1[SIZE1];
    char word2[SIZE1];

    FILE *f;

    // предварительное заполнение файла
    char str[] = "helloqwerty wreyhldoyy";

    if( (f = fopen(".\\task1\\task1.txt", "w" )) == NULL ){
        perror("Error - ");
        return;
    }
    else { 
        fprintf(f, "%s", str);
        fclose(f);
    }

    // начало выполнения задания
    if( (f = fopen(".\\task1\\task1.txt", "a+" )) == NULL ){
        perror("Error - ");
        return;
    }
    else{
        fscanf(f, "%100s %100s", word1, word2);
    }

    printf("1 - %s\n2 - %s\n",word1, word2);
    fprintf(f,"\n");

    int num = 0;
    char *w1;
    char *w2;
    int len1 = 0;
    int len2 = 0;
    // Если первое слово больше второго, то все его символы сравниваются со всеми символами второго
    if(strlen(word1) >= strlen(word2)){
        w1 = &word1[0];
        w2 = &word2[0];
        len1 = strlen(word1);
        len2 = strlen(word2);
    }
    else { // и наоборот
        w1 = &word2[0];
        w2 = &word1[0];
        len1 = strlen(word2);
        len2 = strlen(word1);
    }

    // поочереднаяя проверка обоих слов поочереди
    for(int i = 0; i < len1; i++){
        // проверка каждой буквы первого слова на повтор
        for(int j = 0; j < len1; j++){
            if((*(w1 + i) == *(w1 + j)) && (j != i)) {
                // printf(" %c ", *(w1 + i));
                num++;
                break;
            }   
        }

        // если num больше нуля - не проверяем второе слово на совпадение
        if(num > 0){
            num = 0;
            continue;
        }

        // побуквенная проверка второго слова
        for(int j = 0; j < len2; j++){
            if(*(w1 + i) == *(w2 + j)){
                // printf("%c ", *(w1 + i));
                num++;
            }
        }
        // если текущая проверяемая буква встречается один раз - выводим её
        if(num == 1){
            printf("%c ", *(w1 + i));
            fprintf(f,"%c ", *(w1 + i));
            num = 0;
        }
    }

    fclose(f);
    printf("\n");
}

/* Задача 2. В файле .txt дана символьная строка не более 1000 символов. Необходимо
заменить все буквы "а" на буквы "b" и наоборот, как заглавные, так и
строчные. Результат записать в .txt. */
#define SIZE2 1000
void task2(void){
    char str[SIZE2];
    FILE *f;
    if( (f = fopen(".\\task2\\task2.txt", "a+" )) == NULL ){
        perror("Error - ");
        return;
    }
    else{
        fscanf(f, "%1000s", str);
    }

    printf("%s\n",str);

    for(int i = 0; i < strlen(str); i++){
        if(str[i] == 'a'){
            str[i] += 1;
            continue;
        }
        if(str[i] == 'A'){
            str[i] += 1;
            continue;
        }
        if(str[i] == 'b'){
            str[i] -= 1;
            continue;
        }
        if(str[i] == 'B'){
            str[i] -= 1;
            continue;
        }
    }
    printf("%s\n",str);
    fprintf(f,"\n%s",str);
    fclose(f);
}

/* Задача 3. В файле .txt дана строка, не более 1000 символов, содержащая буквы, целые
числа и иные символы. Требуется все числа, которые встречаются в строке,
поместить в отдельный целочисленный массив. Например, если дана строка
"data 48 call 9 read13 blank0a", то в массиве числа 48, 9, 13 и 0. Вывести
массив по возрастанию в файл .txt. */
#define SIZE3 1000
#define CONDITION ((str1[i] >= '0') && (str1[i] <= '9'))
void task3(void){

    char str1[SIZE3];
    int str2[SIZE3] = {0};
    FILE *f;
    // открытие файла
    if( (f = fopen(".\\task3\\task3.txt", "a+" )) == NULL ){
        perror("Error - ");
        return;
    }
    else{
        fscanf(f, "%1000[^\n]", str1); // считывание 1000 символов в соответствующий массив
    }

    printf("%s\n", str1);
    
    int tmpMult = 0; // переменная для хранения множителя числа
    int j = 0; // вспомогательная переменная для записи найденных чисел в другой массив 
    size_t l1 = strlen(str1); // определение длины считанной строки
    
    // перебор элементов строки для поиска чисел
    for(int i = l1 - 1; i >= 0; i--){
        if(CONDITION){ // если текущий символ - число?
            if((str1[i+1] >= '0') && (str1[i+1] <= '9')){ // если предыдущий символ тоже был числом?
                tmpMult *= 10; // увеличиваем множитель числа
            }

            if(tmpMult == 0)
                tmpMult = 1;
            
            str2[j] += -('0' - str1[i]) * tmpMult; // формируем число типа int из строки
        }
        // если текущий символ не число, а множитель не равен нулю, т.е. предыдущие символы были числами
        if(!CONDITION && (tmpMult > 0)){
            tmpMult = 0; // сбрасываем множитель разрядов числа
            j++; // переходим на следующий индекс массива
        }
    }

    sortArray(str2, j, 1); // сортировка массива
    printIntArray(str2, j); // вывод массива

    int tmp = 0; // переменная для временного хранения числа и его последующей конвертации в символ
    char charTmp[8]; // массив для составления числа с нескольими разрядами
    int j1 = 8; // счетчик для charTmp

    fprintf(f,"\n");

    // перебор отсортированного числового массива
    for(int i = 0; i < j; i++){
        tmp = str2[i]; // сохраняем текущее обрабатываемое число во временную переменную

        if(tmp > 9){ // если данное число больше многоразрядное
            while(tmp > 0){ // то порязрядно записываем его во вспомогательный массив 
                charTmp[j1-1] = '0' + (tmp % 10);
                tmp /= 10; // само число при этом сокращаем 
                j1--;
            }

            for(int d = j1; d < 8; d++)
                fprintf(f,"%c", charTmp[d]); // записываем полученное число в файл
        }
        else { // если число одноразрядное - просто записываем его в файл
            fprintf(f,"%c", '0' + tmp);
        }

        j1 = 8;
        fprintf(f," "); 
    }
    fclose(f);
}

/* В файле .txt строка из маленьких и больших английских букв, знаков
препинания и пробелов. Требуется удалить из нее повторяющиеся символы и
все пробелы. Результат записать в файл .txt */
#define SIZE4 1000

void task4(void){
    FILE *f;
    char str[SIZE4];
    // открытие файла
    if( (f = fopen(".\\task4\\task4.txt", "a+" )) == NULL ){
        perror("Error - ");
        return;
    }
    else{
        fscanf(f, "%1000[^\n]", str); // считывание 1000 символов в соответствующий массив
    }

    printf("%s\n",str);

    fprintf(f,"\n");

    _Bool tmp1 = 0;

    for(int i = 0; i < strlen(str); i++){
        if(str[i]==' ')
            continue;
        for(int i1 = i; i1 >= 0; i1--){
            if(str[i] == str[i1-1])
                tmp1++;
        }
        if(tmp1 == 0)
            fprintf(f, "%c", str[i]);
        else
            tmp1 = 0;
    }

    fclose(f);
}

/* В файле .txt дана строка слов, разделенных пробелами. Найти самое длинное
слово и вывести его в файл .txt. Случай, когда самых длинных слов может быть
несколько, не обрабатывать */
#define SIZE5 1000

void task5(void){
    FILE *f;
    char str[SIZE5];
    // открытие файла
    if( (f = fopen(".\\task5\\task5.txt", "a+" )) == NULL ){
        perror("Error - ");
        return;
    }
    else{
        fscanf(f, "%1000[^\n]", str); // считывание 1000 символов в соответствующий массив
    }

    printf("%s\n",str);

    fprintf(f,"\n");

    int tmp = 0;
    int max = 0;
    int index = 0;
    for(int i = 0; i < strlen(str); i++){
        tmp++;

        if((str[i] == ' ') || (i == strlen(str)-1)){
            if(tmp > max){
                max = tmp;
                index = (i + 1) - tmp;
            }
            tmp = 0;
        }
    }

    for(int i = index; i < index + max; i++){
        printf("%c",str[i]);
        fprintf(f,"%c",str[i]);
    }
    printf("\n");
}

/* В файле .txt дано предложение. Необходимо определить, сколько слов
заканчиваются на букву 'а'. Ответ записать в файл .txt */
#define SIZE6 1000

void task6(void){
    FILE *f;
    char str[SIZE6];
    // открытие файла
    if( (f = fopen(".\\task6\\task6.txt", "a+" )) == NULL ){
        perror("Error - ");
        return;
    }
    else{
        fscanf(f, "%1000[^\n]", str); // считывание 1000 символов в соответствующий массив
    }
    
    printf("\n%s\n",str);

    fprintf(f,"\n");

    int index = 0;
    int haveA = 0;
    for(int i = 0; i < strlen(str); i++){
        if((str[i] == ' ') || (i == strlen(str) - 1)){
            if((str[i-1] == 'a') || (str[i] == 'a'))
                haveA++;
        }
    }

    printf("%d\n",haveA);
}