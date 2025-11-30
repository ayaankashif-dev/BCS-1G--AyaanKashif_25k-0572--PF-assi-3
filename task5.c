#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 4
#define MAX_LINE_LENGTH 512

void printAllLines(char **lines, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", lines[i]);
    }
}

void insertLine(char ***lines, int *size, int *capacity, int index, const char *text) {
    if (index < 0 || index > *size) {
        printf("Invalid index for insertion.\n");
        return;
    }
    if (*size == *capacity) {
        int newCapacity = (*capacity) * 2;
        char **newLines = (char**) realloc(*lines, newCapacity * sizeof(char *));
        if (!newLines) {
            perror("realloc");
            exit(1);
        }
        *lines = newLines;
        *capacity = newCapacity;
    }
    for (int i = *size; i > index; i--) {
        (*lines)[i] = (*lines)[i - 1];
    }
    (*lines)[index] = (char* )malloc(strlen(text) + 1);
    if (!(*lines)[index]) {
        perror("malloc");
        exit(1);
    }
    strcpy((*lines)[index], text);
    (*size)++;
}

void deleteLine(char ***lines, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Invalid index for deletion.\n");
        return;
    }
    free((*lines)[index]);
    for (int i = index; i < (*size) - 1; i++) {
        (*lines)[i] = (*lines)[i + 1];
    }
    (*size)--;
}

void shrinkToFit(char ***lines, int *capacity, int size) {
    char **newLines = (char**)realloc(*lines, size * sizeof(char *));
    if (!newLines && size > 0) {
        perror("realloc");
        exit(1);
    }
    *lines = newLines;
    *capacity = size;
}

void saveToFile(char **lines, int size, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        fprintf(f, "%s\n", lines[i]);
    }
    fclose(f);
}

void freeAll(char ***lines, int *size) {
    for (int i = 0; i < *size; i++) {
        free((*lines)[i]);
    }
    free(*lines);
    *lines = NULL;
    *size = 0;
}

void loadFromFile(char ***lines, int *size, int *capacity, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }
    freeAll(lines, size);
    *capacity = INITIAL_CAPACITY;
    *lines = (char** )malloc((*capacity) * sizeof(char *));
    if (!*lines) {
        perror("malloc");
        exit(1);
    }
    char buffer[MAX_LINE_LENGTH];
    *size = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, f)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (*size == *capacity) {
            int newCapacity = (*capacity) * 2;
            char **newLines = (char**) realloc(*lines, newCapacity * sizeof(char *));
            if (!newLines) {
                perror("realloc");
                exit(1);
            }
            *lines = newLines;
            *capacity = newCapacity;
        }
        (*lines)[*size] = (char*)malloc(strlen(buffer) + 1);
        if (!(*lines)[*size]) {
            perror("malloc");
            exit(1);
        }
        strcpy((*lines)[*size], buffer);
        (*size)++;
    }
    fclose(f);
}

/*
Dynamic allocation is more efficient than fixed-size arrays because memory is allocated only as needed for user input. This reduces waste for short input and enables unlimited lines until system memory is exhausted.
*/

int main() {
    char **lines = (char** )malloc(INITIAL_CAPACITY * sizeof(char *));
    if (!lines) {
        perror("malloc");
        return 1;
    }
    int size = 0, capacity = INITIAL_CAPACITY;

    int choice;
    char buffer[MAX_LINE_LENGTH];
    while (1) {
        printf("1. Insert line\n");
        printf("2. Delete line\n");
        printf("3. Print all lines\n");
        printf("4. Shrink to fit\n");
        printf("5. Save to file\n");
        printf("6. Load from file\n");
        printf("7. Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) break;
        getchar();
        if (choice == 1) {
            printf("Enter index to insert: ");
            int idx;
            if (scanf("%d", &idx) != 1) break;
            getchar();
            printf("Enter line text: ");
            fgets(buffer, MAX_LINE_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            insertLine(&lines, &size, &capacity, idx, buffer);
        } else if (choice == 2) {
            printf("Enter index to delete: ");
            int idx;
            if (scanf("%d", &idx) != 1) break;
            deleteLine(&lines, &size, idx);
        } else if (choice == 3) {
            printAllLines(lines, size);
        } else if (choice == 4) {
            shrinkToFit(&lines, &capacity, size);
        } else if (choice == 5) {
            printf("Enter filename: ");
            fgets(buffer, MAX_LINE_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            saveToFile(lines, size, buffer);
        } else if (choice == 6) {
            printf("Enter filename: ");
            fgets(buffer, MAX_LINE_LENGTH, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            loadFromFile(&lines, &size, &capacity, buffer);
        } else if (choice == 7) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    freeAll(&lines, &size);
    return 0;
}
