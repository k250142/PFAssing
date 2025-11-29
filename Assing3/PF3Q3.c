#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee e[], int n)
{
    int i;
    printf("\nID\tName\t\tDesignation\t\tSalary\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%s\t\t%s\t\t%.2f\n", e[i].id, e[i].name, e[i].designation, e[i].salary);
    }
}

void findHighestSalary(struct Employee e[], int n)
{
    int i, index = 0;
    for (i = 1; i < n; i++)
    {
        if (e[i].salary > e[index].salary)
            index = i;
    }

    printf("\nEmployee With Highest Salary:\n");
    printf("ID: %d\n", e[index].id);
    printf("Name: %s\n", e[index].name);
    printf("Designation: %s\n", e[index].designation);
    printf("Salary: %.2f\n", e[index].salary);
}

void searchEmployee(struct Employee e[], int n)
{
    int choice, id, i, found = 0;
    char name[50];

    printf("\n1. Search by ID\n2. Search by Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for (i = 0; i < n; i++)
        {
            if (e[i].id == id)
            {
                found = 1;
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", e[i].id);
                printf("Name: %s\n", e[i].name);
                printf("Designation: %s\n", e[i].designation);
                printf("Salary: %.2f\n", e[i].salary);
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter Name: ");
        scanf("%s", name);

        for (i = 0; i < n; i++)
        {
            if (strcmp(e[i].name, name) == 0)
            {
                found = 1;
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", e[i].id);
                printf("Name: %s\n", e[i].name);
                printf("Designation: %s\n", e[i].designation);
                printf("Salary: %.2f\n", e[i].salary);
            }
        }
    }

    if (!found) printf("No employee found.\n");
}

int main()
{
    int n, i;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee e[n];

    for (i = 0; i < n; i++)
    {
        printf("\nEnter ID: ");
        scanf("%d", &e[i].id);

        printf("Enter Name: ");
        scanf("%s", e[i].name);

        printf("Enter Designation: ");
        scanf("%s", e[i].designation);

        printf("Enter Salary: ");
        scanf("%f", &e[i].salary);
    }

    displayEmployees(e, n);
    findHighestSalary(e, n);
    searchEmployee(e, n);

    return 0;
}
