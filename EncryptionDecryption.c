#include <stdio.h>
#include <string.h>

// function to perform XOR encryption/decryption
void xor_encrypt(char* str, int key) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = str[i] ^ key; // XOR each character with the key
    }
}

// function to perform bitwise inversion
void bit_invert(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = ~str[i]; // invert each bit of each character
    }
}

int main() {
    char str[100]; // array to store the input string
    int choice, key; // variables to store the user's choice and the XOR key
    char repeat; // variable to store whether the user wants to repeat the program
    do {
        printf("Enter a string to encrypt/decrypt:\n");
        scanf("%s", str); // read in the input string
        printf("Choose an operation:\n");
        printf("1. XOR encryption/decryption\n");
        printf("2. Bitwise inversion\n");
        scanf("%d", &choice); // read in the user's choice
        switch (choice) {
            case 1:
                printf("Enter the key for XOR encryption/decryption:\n");
                scanf("%d", &key); // read in the XOR key
                xor_encrypt(str, key); // call the function to perform XOR encryption/decryption
                break;
            case 2:
                bit_invert(str); // call the function to perform bitwise inversion
                break;
            default:
                printf("Invalid choice.\n"); //  invalid user input
        }
        printf("Result: %s\n", str); // print the result of the operation
        printf("Do you want to perform the inverse operation again? (y/n)\n");
        scanf(" %c", &repeat); // read in whether the user wants to repeat the program
        if (repeat == 'y' || repeat == 'Y') { // if the user wants to repeat the program
            if (choice == 1) {
                xor_encrypt(str, key); // to perform the inverse operation, use the same key for XOR
            } else {
                bit_invert(str); // to perform the inverse operation, use the same operation (bitwise inversion)
            }
            printf("Result after inverse operation: %s\n", str); // print the result of the inverse operation
        }
    } while ( repeat == 'y' || repeat == 'Y'); // repeat the program if the user wants to
    return 0; 
}