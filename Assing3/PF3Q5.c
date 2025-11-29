#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 5
#define MAX_LINE 1000

char **lines = NULL;
int size = 0;
int capacity = 0;

// Ensure there is enough space for a new line
void ensureCapacity() {
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
        char **temp = realloc(lines, newCapacity * sizeof(char *));
        if (!temp) {
            perror("Memory realloc failed");
            exit(EXIT_FAILURE);
        }
        lines = temp;
        capacity = newCapacity;
    }
}

// Shrink array to fit exactly the number of lines
void shrinkToFit() {
    if (size == capacity) return; // Already fit
    char **temp = realloc(lines, size * sizeof(char *));
    if (!temp && size > 0) {
        perror("Shrink failed");
        return;
    }
    lines = temp;
    capacity = size;
}

// Insert a line at given index
void insertLine(int index, const char *text) {
    if (index < 0) {
        printf("Invalid index\n");
        return;
    }

    ensureCapacity();

    // Shift pointers to make space
    for (int i = size; i > index; i--) {
        lines[i] = lines[i - 1];
    }

    lines[index] = malloc(strlen(text) + 1);
    if (!lines[index]) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(lines[index], text);
    size++;
}

// Delete a line at given index
void deleteLine(int index) {
    if (index < 0 || index >= size) {
        printf("Invalid index\n");
        return;
    }

    free(lines[index]);

    // Shift pointers to compact array
    for (int i = index; i < size - 1; i++) {
        lines[i] = lines[i + 1];
    }
    size--;
}

// Print all lines
void printAllLines() {
    printf("\n--- Editor Buffer ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

// Free all allocated memory
void freeAll() {
    for (int i = 0; i < size; i++) {
        free(lines[i]);
    }
    free(lines);
    lines = NULL;
    size = 0;
    capacity = 0;
}

// Save buffer to file
void saveToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File open failed");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }
    fclose(fp);
}

// Load buffer from file (rebuild dynamic allocations)
void loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        return;
    }

    char buffer[MAX_LINE];

    // Free existing lines first
    freeAll();
    capacity = INITIAL_CAPACITY;
    lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        perror("Memory allocation failed");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_LINE, fp)) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline
        insertLine(size, buffer);
    }
    fclose(fp);
}

int main() {
    capacity = INITIAL_CAPACITY;
    lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int choice;
    char text[MAX_LINE];
    int index;

    while (1) {
        printf("\n1. Insert Line\n2. Delete Line\n3. Print All\n4. Save\n5. Load\n6. Shrink To Fit\n7. Exit\n");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }
        getchar(); // Remove trailing newline

        switch (choice) {
            case 1:
                printf("Enter index: ");
                if (scanf("%d", &index) != 1) { printf("Invalid input\n"); while(getchar()!='\n'); break; }
                getchar();
                printf("Enter text: ");
                if (!fgets(text, MAX_LINE, stdin)) break;
                text[strcspn(text, "\n")] = 0;
                insertLine(index, text);
                break;

            case 2:
                printf("Enter index: ");
                if (scanf("%d", &index) != 1) { printf("Invalid input\n"); while(getchar()!='\n'); break; }
                deleteLine(index);
                break;

            case 3:
                printAllLines();
                break;

            case 4:
                saveToFile("buffer.txt");
                break;

            case 5:
                loadFromFile("buffer.txt");
                break;

            case 6:
                shrinkToFit();
                printf("Array shrunk to fit.\n");
                break;

            case 7:
                freeAll();
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

