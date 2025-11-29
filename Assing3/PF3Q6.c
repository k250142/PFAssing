#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define FILENAME "members.dat"

// Student structure definition
typedef struct {
    int studentID;
    char fullName[MAX_NAME_LENGTH];
    char batch[20];
    char membershipType[10];
    char registrationDate[11]; // YYYY-MM-DD
    char dateOfBirth[11];      // YYYY-MM-DD
    char interest[10];         // IEEE/ACM/Both
} Student;

// Global variables for in-memory operations
Student *students = NULL;
int studentCount = 0;
int capacity = 0;

// Function prototypes
void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
int addStudent(Student s, const char *filename);
int updateStudent(int studentID);
int deleteStudent(int studentID);
void displayAllStudents();
void generateBatchReport();
int isStudentIDUnique(int studentID);
void toUpperCase(char *str);
void trimWhitespace(char *str);
void freeMemory();

// Load all student records from file into memory
void loadDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    // Get file size to determine number of records
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    studentCount = fileSize / sizeof(Student);
    
    if (studentCount > 0) {
        capacity = studentCount + 10; // Extra capacity for new records
        students = (Student*)malloc(capacity * sizeof(Student));
        if (students == NULL) {
            printf("Memory allocation failed!\n");
            fclose(file);
            exit(1);
        }
        
        size_t readCount = fread(students, sizeof(Student), studentCount, file);
        if (readCount != studentCount) {
            printf("Error reading database file!\n");
        } else {
            printf("Successfully loaded %d student records.\n", studentCount);
        }
    }
    
    fclose(file);
}

// Save all student records from memory to file
void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }
    
    size_t writeCount = fwrite(students, sizeof(Student), studentCount, file);
    if (writeCount != studentCount) {
        printf("Error writing to database file!\n");
    } else {
        printf("Successfully saved %d student records.\n", studentCount);
    }
    
    fclose(file);
}

// Append a new student record to file and memory
int addStudent(Student s, const char *filename) {
    // Check if student ID is unique
    if (!isStudentIDUnique(s.studentID)) {
        printf("Error: Student ID %d already exists!\n", s.studentID);
        return 0;
    }
    
    // Add to memory array
    if (studentCount >= capacity) {
        capacity += 10;
        Student *temp = (Student*)realloc(students, capacity * sizeof(Student));
        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return 0;
        }
        students = temp;
    }
    
    students[studentCount] = s;
    studentCount++;
    
    // Append to file
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Error: Cannot open file for appending!\n");
        return 0;
    }
    
    size_t writeCount = fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    
    if (writeCount != 1) {
        printf("Error writing student record to file!\n");
        return 0;
    }
    
    printf("Student added successfully!\n");
    return 1;
}

// Update a student's batch or membership type
int updateStudent(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            printf("Updating student: %s (ID: %d)\n", students[i].fullName, studentID);
            printf("Current batch: %s\n", students[i].batch);
            printf("Current membership: %s\n", students[i].membershipType);
            
            int choice;
            printf("\nWhat would you like to update?\n");
            printf("1. Batch\n");
            printf("2. Membership Type\n");
            printf("3. Both\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            getchar(); // Clear newline
            
            if (choice == 1 || choice == 3) {
                printf("Enter new batch (CS/SE/Cyber Security/AI): ");
                fgets(students[i].batch, sizeof(students[i].batch), stdin);
                trimWhitespace(students[i].batch);
                toUpperCase(students[i].batch);
            }
            
            if (choice == 2 || choice == 3) {
                printf("Enter new membership type (IEEE/ACM): ");
                fgets(students[i].membershipType, sizeof(students[i].membershipType), stdin);
                trimWhitespace(students[i].membershipType);
                toUpperCase(students[i].membershipType);
                
                // Update interest based on membership type
                if (strcmp(students[i].membershipType, "IEEE") == 0) {
                    strcpy(students[i].interest, "IEEE");
                } else if (strcmp(students[i].membershipType, "ACM") == 0) {
                    strcpy(students[i].interest, "ACM");
                }
            }
            
            // Save the updated database
            saveDatabase(FILENAME);
            printf("Student updated successfully!\n");
            return 1;
        }
    }
    
    printf("Error: Student with ID %d not found!\n", studentID);
    return 0;
}

// Remove a student from file and memory
int deleteStudent(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            printf("Deleting student: %s (ID: %d)\n", students[i].fullName, studentID);
            
            // Shift all elements after the deleted one
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            
            // Save the updated database (this overwrites the entire file)
            saveDatabase(FILENAME);
            printf("Student deleted successfully!\n");
            return 1;
        }
    }
    
    printf("Error: Student with ID %d not found!\n", studentID);
    return 0;
}

// Display all student records in a readable format
void displayAllStudents() {
    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }
    
    printf("\n%-10s %-20s %-15s %-12s %-15s %-12s %-10s\n", 
           "ID", "Name", "Batch", "Membership", "Reg Date", "DOB", "Interest");
    printf("--------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%-10d %-20s %-15s %-12s %-15s %-12s %-10s\n",
               students[i].studentID,
               students[i].fullName,
               students[i].batch,
               students[i].membershipType,
               students[i].registrationDate,
               students[i].dateOfBirth,
               students[i].interest);
    }
    printf("Total records: %d\n", studentCount);
}

// Generate batch-wise reports
void generateBatchReport() {
    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }
    
    char batch[20];
    printf("Enter batch to generate report (CS/SE/Cyber Security/AI): ");
    fgets(batch, sizeof(batch), stdin);
    trimWhitespace(batch);
    toUpperCase(batch);
    
    printf("\nReport for %s batch:\n", batch);
    printf("%-10s %-20s %-12s %-10s\n", "ID", "Name", "Membership", "Interest");
    printf("--------------------------------------------------\n");
    
    int count = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("%-10d %-20s %-12s %-10s\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membershipType,
                   students[i].interest);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No students found in %s batch.\n", batch);
    } else {
        printf("Total students in %s batch: %d\n", batch, count);
    }
}

// Check if student ID is unique
int isStudentIDUnique(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            return 0;
        }
    }
    return 1;
}

// Convert string to uppercase
void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

// Remove leading/trailing whitespace
void trimWhitespace(char *str) {
    int i = 0, j = 0;
    int len = strlen(str);
    
    // Remove trailing newline/whitespace
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == ' ' || str[len-1] == '\t')) {
        str[len-1] = '\0';
        len--;
    }
    
    // Remove leading whitespace
    while (str[i] == ' ' || str[i] == '\t') {
        i++;
    }
    
    if (i > 0) {
        for (j = 0; str[i]; j++, i++) {
            str[j] = str[i];
        }
        str[j] = '\0';
    }
}

// Free allocated memory
void freeMemory() {
    if (students != NULL) {
        free(students);
        students = NULL;
    }
}

// Get student input from user
Student getStudentInput() {
    Student s;
    
    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    getchar(); // Clear newline
    
    printf("Enter Full Name: ");
    fgets(s.fullName, sizeof(s.fullName), stdin);
    trimWhitespace(s.fullName);
    
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    fgets(s.batch, sizeof(s.batch), stdin);
    trimWhitespace(s.batch);
    toUpperCase(s.batch);
    
    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membershipType, sizeof(s.membershipType), stdin);
    trimWhitespace(s.membershipType);
    toUpperCase(s.membershipType);
    
    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.registrationDate, sizeof(s.registrationDate), stdin);
    trimWhitespace(s.registrationDate);
    
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dateOfBirth, sizeof(s.dateOfBirth), stdin);
    trimWhitespace(s.dateOfBirth);
    
    // Set interest based on membership type
    if (strcmp(s.membershipType, "IEEE") == 0) {
        strcpy(s.interest, "IEEE");
    } else if (strcmp(s.membershipType, "ACM") == 0) {
        strcpy(s.interest, "ACM");
    } else {
        strcpy(s.interest, "Both");
    }
    
    return s;
}

// Main menu interface
void displayMenu() {
    printf("\n=== IEEE/ACM Membership Registration Manager ===\n");
    printf("1. Register a new student\n");
    printf("2. Update student information\n");
    printf("3. Delete student registration\n");
    printf("4. View all registrations\n");
    printf("5. Generate batch-wise report\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    printf("IEEE/ACM Membership Registration System\n");
    printf("Loading database...\n");
    
    // Load existing database
    loadDatabase(FILENAME);
    
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch (choice) {
            case 1: {
                Student newStudent = getStudentInput();
                addStudent(newStudent, FILENAME);
                break;
            }
            case 2: {
                int studentID;
                printf("Enter Student ID to update: ");
                scanf("%d", &studentID);
                getchar();
                updateStudent(studentID);
                break;
            }
            case 3: {
                int studentID;
                printf("Enter Student ID to delete: ");
                scanf("%d", &studentID);
                getchar();
                deleteStudent(studentID);
                break;
            }
            case 4:
                displayAllStudents();
                break;
            case 5:
                generateBatchReport();
                break;
            case 6:
                printf("Saving database and exiting...\n");
                saveDatabase(FILENAME);
                freeMemory();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}