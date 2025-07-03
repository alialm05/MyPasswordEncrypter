#include <stdio.h>
#include <stdlib.h>
#include "encryption_manager.h"

const char* password_filename = "./password/passwords.txt";
const char *key_filename = "./password/key.txt";
const char *enc_filename = "./password/passwords_enc";

int fileExists(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file) { 
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}

void addToFile(const char* website, const char* username, const char* password) {

    // Ensure the password file exists
    FILE *file;
    if (fileExists(password_filename)) {
        file = fopen(password_filename, "a");
    }else {
        // check if the encryptred file exists
        if (fileExists(enc_filename)) {
            setup_decrypt(enc_filename, key_filename);
            file = fopen(password_filename, "a");
        } else {
            // if the encrypted file exists, open the encrypted file
            printf("No encrypted or decrypted file password file exists, add a password to start!\n");
        }
    }

    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s: username=%s, password=%s\n", website, username, password);
    fclose(file);
    printf("Password added successfully.\n");
}

int main (int argc, char* argv[]) {
    
    printf("Welcome to the Password Manager!\nPlease choose an option:\n");
    printf("1. Add a password\n");
    printf("2. Encrypt passwords (outputs to file)\n");
    printf("3. Decrypt passwords (outputs to file)\n");
    printf("4. Display passwords (outputs to console)\n");
    printf("5. Exit\n");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Adding a password...\n");

            char website[24];
            printf("Add a password to the file, first, what is the website the password is for?.\n");
            scanf("%16s", website);

            printf("What is the username for %s?\n", website);
            char username[64];
            scanf("%63s", username);

            printf("What is the password for %s?\n", website);
            char password[64];
            scanf("%63s", password);

            addToFile(website, username, password);

            break;
        case 2:
            printf("Encrypting passwords...\n");
            setup_enc(password_filename);
            break;
        case 3:
            if (fileExists(password_filename)) {
                printf("Decrypted file already exists.\n");
                return 0; 
            }
            printf("Decrypting passwords...\n");
            setup_decrypt(enc_filename, key_filename);
            break;
        case 4:
            printf("Displaying passwords...\n");
            display_encrypted_pass(enc_filename, key_filename);
            break;
        case 5:
            printf("Exiting the Password Manager. Goodbye!\n");
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
            break;
    }

    return 0;
}