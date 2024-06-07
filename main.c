#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void create_binary_file(const char *filename) {
    SetConsoleOutputCP(CP_UTF8);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Ошибка при создании файла");
        exit(EXIT_FAILURE);
    }

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    fwrite(numbers, sizeof(int), 10, file);
    fclose(file);
}

int is_even(int number) {
    return number % 2 == 0;
}

void process_binary_file(const char *filename) {
    SetConsoleOutputCP(CP_UTF8);
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка при открытии исходного файла");
        exit(EXIT_FAILURE);
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {
        perror("Ошибка при открытии временного файла");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int number;
    printf("Содержимое исходного файла %s:\n", filename);
    printf("-------------------------\n");
    printf("Числа: ");
    while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%d ", number);
        if (is_even(number)) {
            fwrite(&number, sizeof(int), 1, tempFile);
        }
    }
    printf("\n");
    printf("-------------------------\n");

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.bin", filename);

    // Открыть преобразованный файл для чтения и вывести его содержимое
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка при открытии преобразованного файла");
        exit(EXIT_FAILURE);
    }

    printf("Содержимое преобразованного файла %s:\n", filename);
    printf("-------------------------\n");
    printf("Числа: ");
    while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%d ", number);
    }
    printf("\n");
    printf("-------------------------\n");

    fclose(file);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const char *filename = "input.bin";

    create_binary_file(filename);
    process_binary_file(filename);

    printf("Нечетные числа удалены, четные числа сохранены в исходном порядке.\n");

    return EXIT_SUCCESS;
}