



#include <stdio.h>
#define MAX 5

// Function prototypes
void push(int stack[], int *top);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {
    int stack[MAX];
    int top = -1;
    int choice;
    printf("=== Stack Implementation ===\n");
    do {
        printf("\n1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                push(stack, &top);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 5);
    return 0;
}
void push(int stack[], int *top) {
    if(*top == MAX - 1) {
        printf("Stack Overflow! Cannot push.\n");
        return;
    }
    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);
    (*top)++;
    stack[*top] = value;
    printf("%d pushed to stack.\n", value);
}
void pop(int stack[], int *top) {
    if(*top == -1) {
        printf("Stack Underflow! Cannot pop.\n");
        return;
    }
    printf("%d popped from stack.\n", stack[*top]);
    (*top)--;
}
void peek(int stack[], int top) {
    if(top == -1) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", stack[top]);
}
void display(int stack[], int top) {
    if(top == -1) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for(int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}