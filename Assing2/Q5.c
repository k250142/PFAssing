#include <stdio.h>
#include <string.h>
#include <ctype.h>

void displayMenu();
void encodeMessage(char message[]);
void decodeMessage(char message[]);
char toggleBits(char ch);

int main() {
    int choice;
    char message[1000];
    printf("=== TCS Message Encoding/Decoding Tool ===\n");
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1:
                printf("Enter message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                encodeMessage(message);
                break;
            case 2:
                printf("Enter message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0; 
                decodeMessage(message);
                break;
            case 3:
                printf("Exiting TCS tool. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while(choice != 3);   
    return 0;
}
void displayMenu() {
    printf("\n===== TCS MENU =====\n");
    printf("1. Encode Message\n");
    printf("2. Decode Message\n");
    printf("3. Exit\n");
}
char toggleBits(char ch) {
    return ch ^ 0x12;
}
void encodeMessage(char message[]) {
    int length = strlen(message);
    char encoded[1000];
    if(length == 0) {
        printf("Empty message!\n");
        return;
    }
    printf("\nEncoding Process:\n");
    printf("Original: %s\n", message);
    for(int i = 0; i < length; i++) {
        encoded[i] = message[length - 1 - i];
    }
    encoded[length] = '\0';
    printf("After reversal: %s\n", encoded);
    for(int i = 0; i < length; i++) {
        encoded[i] = toggleBits(encoded[i]);
    } 
    printf("Encoded message: %s\n", encoded);
}
void decodeMessage(char message[]) {
    int length = strlen(message);
    char decoded[1000];
    if(length == 0) {
        printf("Empty message!\n");
        return;
    }
    printf("\nDecoding Process:\n");
    printf("Encoded: %s\n", message);
    for(int i = 0; i < length; i++) {
        decoded[i] = toggleBits(message[i]);
    }
    decoded[length] = '\0';
    printf("After bit untoggling: %s\n", decoded);
    for(int i = 0; i < length; i++) {
        message[i] = decoded[length - 1 - i];
    }
    message[length] = '\0';
    printf("Decoded message: %s\n", message);
}