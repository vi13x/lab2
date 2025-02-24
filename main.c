#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#define MAX_NUMBERS 100 // Максимальное количество чисел в файле

// Функция для записи чисел в файл
void write_numbers_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int n;
    printf("Введите количество чисел: ");
    scanf("%d", &n);

    printf("Введите %d чисел:\n", n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        fprintf(file, "%d ", num);
    }

    fclose(file);
}

// Функция для чтения и вывода содержимого файла
void read_numbers_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int num;
    printf("Содержимое файла:\n");
    while (fscanf(file, "%d", &num) == 1) {
        printf("%d ", num);
    }
    printf("\n");

    fclose(file);
}

// Функция для подсчёта количества вхождений числа в файле
void count_number_occurrences(const char *filename, int target) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int count = 0, num;
    while (fscanf(file, "%d", &num) == 1) {
        if (num == target) {
            count++;
        }
    }

    printf("Число %d встречается в файле %d раз(а).\n", target, count);

    fclose(file);
}

// Функция для циклического сдвига чисел в файле вправо на k позиций
void shift_numbers_in_file(const char *filename, int k) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    int numbers[MAX_NUMBERS], count = 0;

    // Читаем числа из файла в массив
    while (fscanf(file, "%d", &numbers[count]) == 1 && count < MAX_NUMBERS) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Файл пуст.\n");
        return;
    }

    // Выполняем циклический сдвиг вправо
    k = k % count;
    if (k > 0) {
        int temp[MAX_NUMBERS];
        for (int i = 0; i < count; i++) {
            temp[(i + k) % count] = numbers[i];
        }
        for (int i = 0; i < count; i++) {
            numbers[i] = temp[i];
        }
    }

    // Записываем изменённые данные обратно в файл
    file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка открытия файла для записи");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d ", numbers[i]);
    }
    fclose(file);

    printf("Циклический сдвиг на %d позиций выполнен.\n", k);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    SetConsoleOutputCP(CP_UTF8);
    char *filename = argv[1];
    int choice, target, k;

    do {
        printf("\nМеню:\n");
        printf("1. Записать числа в файл\n");
        printf("2. Вывести содержимое файла\n");
        printf("3. Найти количество вхождений числа\n");
        printf("4. Выполнить циклический сдвиг\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                write_numbers_to_file(filename);
                break;
            case 2:
                read_numbers_from_file(filename);
                break;
            case 3:
                printf("Введите число для поиска: ");
                scanf("%d", &target);
                count_number_occurrences(filename, target);
                break;
            case 4:
                printf("Введите количество позиций для сдвига: ");
                scanf("%d", &k);
                shift_numbers_in_file(filename, k);
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Некорректный выбор, попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}
