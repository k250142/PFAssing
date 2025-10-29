#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 5

char customerName[50];
char customerCNIC[15];
int productCodes[] = {1, 2, 3, 4, 5};
char productNames[][20] = {"Milk", "Bread", "Butter", "Rice", "Eggs"};
int quantities[] = {50, 10, 20, 8, 15};
float prices[] = {100, 200, 300, 150, 250};
int cart[MAX_PRODUCTS] = {0};
float totalBill = 0;
int hasCustomerInfo = 0;

void displayMainMenu();
void getCustomerInfo();
void displayInventory();
void addItemToCart();
void displayTotalBill();
void showInvoice();

int main() {
    int choice;
    printf("=== Supermarket Billing System ===\n");
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                getCustomerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                printf("Inventory updates automatically when you purchase.\n");
                break;
            case 4:
                addItemToCart();
                break;
            case 5:
                displayTotalBill();
                break;
            case 6:
                showInvoice();
                break;
            case 7:
                printf("Thank you! Goodbye.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
        printf("\n");
    } while(choice != 7);
    return 0;
}
void displayMainMenu() {
    printf("\n===== MAIN MENU =====\n");
    printf("1. Customer Information\n");
    printf("2. Display Inventory\n");
    printf("3. Update Inventory\n");
    printf("4. Add Item to Cart\n");
    printf("5. Display Total Bill\n");
    printf("6. Show Invoice\n");
    printf("7. Exit\n");
}
void getCustomerInfo() {
    printf("\nEnter customer name: ");
    scanf("%s", customerName);
    printf("Enter CNIC: ");
    scanf("%s", customerCNIC);
    hasCustomerInfo = 1;
    printf("Customer info saved!\n");
}
void displayInventory() {
    printf("\n=== INVENTORY ===\n");
    printf("Code\tName\tQty\tPrice\n");
    for(int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%d\t%s\t%d\t%.2f\n", productCodes[i], productNames[i], quantities[i], prices[i]);
    }
}
void addItemToCart() {
    int code, qty;
    displayInventory();
    printf("\nEnter product code: ");
    scanf("%d", &code);
    if(code < 1 || code > MAX_PRODUCTS) {
        printf("Invalid product code!\n");
        return;
    }
    int index = code - 1;
    printf("Enter quantity: ");
    scanf("%d", &qty);
    if(qty > quantities[index]) {
        printf("Only %d available in stock!\n", quantities[index]);
        return;
    }
    if(qty < 1) {
        printf("Quantity must be positive!\n");
        return;
    }
    cart[index] += qty;
    quantities[index] -= qty;
    totalBill += (prices[index] * qty);
    printf("Added %d %s to cart.\n", qty, productNames[index]);
}
void displayTotalBill() {
    if(totalBill == 0) {
        printf("Cart is empty!\n");
        return;
    }
    printf("\n=== BILL ===\n");
    printf("Subtotal: Rs. %.2f\n", totalBill);
    char promo[20];
    printf("Enter promo code (or 'skip'): ");
    scanf("%s", promo);
    if(strcmp(promo, "Eid2025") == 0) {
        float discount = totalBill * 0.25;
        printf("25% discount applied: -Rs. %.2f\n", discount);
        printf("Final Total: Rs. %.2f\n", totalBill - discount);
    } else {
        printf("No discount applied.\n");
        printf("Final Total: Rs. %.2f\n", totalBill);
    }
}
void showInvoice() {
    if(!hasCustomerInfo) {
        printf("Please enter customer info first!\n");
        return;
    }
    if(totalBill == 0) {
        printf("No items in cart!\n");
        return;
    }
    printf("\n=== INVOICE ===\n");
    printf("Customer: %s\n", customerName);
    printf("CNIC: %s\n", customerCNIC);
    printf("\nItems Purchased:\n");
    
    for(int i = 0; i < MAX_PRODUCTS; i++) {
        if(cart[i] > 0) {
            printf("%s: %d x Rs. %.2f = Rs. %.2f\n", productNames[i], cart[i], prices[i], cart[i] * prices[i]);
        }
    }
    printf("\nSubtotal: Rs. %.2f\n", totalBill);
    char choice;
    printf("Apply Eid2025 promo? (y/n): ");
    scanf(" %c", &choice);
    if(choice == 'y' || choice == 'Y') {
        float discount = totalBill * 0.25;
        printf("Discount: Rs. %.2f\n", discount);
        printf("Final Amount: Rs. %.2f\n", totalBill - discount);
    } else {
        printf("Final Amount: Rs. %.2f\n", totalBill);
    }
}