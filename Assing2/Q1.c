#include <stdio.h>
#include <string.h>
#define MAX 100

void addBook(int isbns[], char titles[][50], float prices[], int qty[], int *cnt) {
    int id;
    printf("Enter isbn: ");
    scanf("%d", &id);
    for (int i = 0; i < *cnt; i++) {
        if (isbns[i] == id) {
            printf("isbn already exist!\n");
            return;
        }
    }
    isbns[*cnt] = id;
    printf("Enter title: ");
    getchar(); 
    fgets(titles[*cnt], 50, stdin);
    titles[*cnt][strcspn(titles[*cnt], "\n")] = 0;
    printf("Enter price: ");
    scanf("%f", &prices[*cnt]);
    printf("Enter quantity: ");
    scanf("%d", &qty[*cnt]);
    (*cnt)++;
    printf("book added!\n");
}
void processSale(int isbns[], int qty[], int cnt) {
    int id, sold;
    printf("Enter isbn: ");
    scanf("%d", &id);
    for (int i = 0; i < cnt; i++) {
        if (isbns[i] == id) {
            printf("Enter copies sold: ");
            scanf("%d", &sold);
            if (qty[i] < sold) {
                printf("not enough stock!\n");
            } else {
                qty[i] -= sold;
                printf("sale done, new quantity = %d\n", qty[i]);
            }
            return;
        }
    }
    printf("book not found!\n");
}
void lowStock(int isbns[], char titles[][50], float prices[], int qty[], int cnt) {
    printf("\nLow Stock Books (<5)\n");
    int any = 0;
    for (int i = 0; i < cnt; i++) {
        if (qty[i] < 5) {
            printf("%d  %s  %.2f  %d\n", isbns[i], titles[i], prices[i], qty[i]);
            any = 1;
        }
    }
    if (!any) {
        printf("none low stock\n");
    }
}
int main() {
    int isbns[MAX];
    char titles[MAX][50];
    float prices[MAX];
    int qty[MAX];
    int count = 0;
    int opt;
    while (1) {
        printf("\n--- Liberty Books Menu ---\n");
        printf("1. Add new book\n");
        printf("2. Process sale\n");
        printf("3. Low stock report\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                addBook(isbns, titles, prices, qty, &count);
                break;
            case 2:
                processSale(isbns, qty, count);
                break;
            case 3:
                lowStock(isbns, titles, prices, qty, count);
                break;
            case 4:
                printf("bye\n");
                return 0;
            default:
                printf("invalid option\n");
                break;
        }
    }
    return 0;
}
