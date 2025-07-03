#include <stdio.h>
#include <stdlib.h>

void addToFile(const char* website, const char* username, const char* password) {
    FILE *file = fopen("passwords.txt", "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s: username=%s, password=%s\n", website, username, password);
    fclose(file);
    printf("Password added successfully.\n");
}

int main (int argc, char *argv[]) {
    
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

    return 0;
}