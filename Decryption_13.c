#include <stdio.h>
#include <string.h>

void xor_encrypt(char* str, int key) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = str[i] ^ key;
    }
}

void bit_invert(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = ~str[i];
    }
}

int main() {
    char str[100];
    int choice, key;
     char repeat;
    do {
        printf("Enter a string to encrypt/decrypt:\n");
        scanf("%s", str);
        printf("Choose an operation:\n");
        printf("1. XOR encryption/decryption\n");
        printf("2. Bitwise inversion\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the key for XOR encryption/decryption:\n");
                scanf("%d", &key);
                xor_encrypt(str, key);
                break;
            case 2:
                bit_invert(str);
                break;
            default:
                printf("Invalid choice.\n");
        }
        printf("Result: %s\n", str);
        printf("Do you want to perform the inverse operation again? (y/n)\n");
       
       scanf(" %c", &repeat); // note the space before %c to consume any previous newline character
        if (repeat == 'y' || repeat == 'Y') {
            if (choice == 1) {
                xor_encrypt(str, key); // to perform the inverse operation, use the same key for XOR
            } else {
                bit_invert(str); // to perform the inverse operation, use the same operation (bitwise inversion)
            }
            printf("Result after inverse operation: %s\n", str);
        }
    } while ( repeat == 'y' || repeat == 'Y');
    return 0;
}