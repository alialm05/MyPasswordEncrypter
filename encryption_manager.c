#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

void decrypt(FILE* encrypted_file, FILE* key_file, FILE* decrypted_file) {
    int enc_c, key;
    while ((enc_c = fgetc(encrypted_file)) != EOF && (key = fgetc(key_file)) != EOF) {
        int dec_c = enc_c ^ key; // XOR the character with the key
        fputc(dec_c, decrypted_file); // Write the decrypted character to the output file
    }
}
void encrypt(FILE* file, FILE* encrypted_file, FILE* key_file) {
    // Encryption logic goes here
    int c;
    while ((c = fgetc(file)) != EOF) {
        // Generate a random key for each character
        int key = rand() % 256; // Random key between 0 and 255
        int encrypted_char = c ^ key;
        fputc(encrypted_char, encrypted_file); // XOR the character with the key
        fputc(key, key_file); // Write the key to the key file
    }
}

int setup_enc(const char* filename){
    FILE* file = fopen(filename, "r"); // file to be encrypted

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    char enc_filename[256];
    char key_filename[256];

    FILE* key_file;

    if (strcmp("./password/passwords.txt", filename) == 0) {
        strcpy(enc_filename, "./password/passwords_enc");
        key_file = fopen("./password/key.txt", "w"); // key file for passwords
    } else {
        // encryption file name:
        //strcpy(enc_filename, "./output/");
        strcpy(enc_filename, filename);
        strremove(enc_filename, ".txt"); // remove the ".txt" suffix
        strcat(enc_filename, "_enc");

        // key file name
        //strcpy(key_filename, "./output/");
        strcpy(key_filename, filename);
        strremove(key_filename, ".txt"); // remove the ".txt" suffix
        strcat(key_filename, "_key.txt"); // add the "_key.txt" suffix
        key_file = fopen(key_filename, "w"); // key file for other files
    }

    FILE* encrypted_file = fopen(enc_filename, "w");
    
    if (encrypted_file == NULL || key_file == NULL) {
        fprintf(stderr, "Error opening output files.\n");
        fclose(file);
        return 1;
    }

    encrypt(file, encrypted_file, key_file);

    fclose(file);
    fclose(encrypted_file);
    fclose(key_file);

    // remove unencrypted file
    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error: Unable to delete the file.\n");
    }
    return 0;
}
 
int setup_decrypt(const char* filename, const char* key_filename){
    FILE *encrypted_file = fopen(filename, "r"); // file to be decrypted
    FILE *key_file = fopen(key_filename, "r"); // key file

    char dec_filename[256];
    if (strcmp("./password/passwords_enc", filename) == 0) {
        strcpy(dec_filename, "./password/passwords.txt"); // assuming the decrypted file will be in the same directory
    } else {
        //printf("file name: %s\n", strstr(filename, '/'));
        strcpy(dec_filename, filename);
        //strcpy(dec_filename, "./output/");
        //strcat(dec_filename, strstr(filename, '/') + 1); // get the base name of the file
        strremove(dec_filename, "_enc"); // remove the "_enc" suffix to get the original filename
        strcat(dec_filename, ".txt"); // add the ".txt" suffix back
    }
    

    if (encrypted_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    } else if (key_file == NULL) {
        fprintf(stderr, "Error opening key file: %s\n", key_filename);
        fclose(encrypted_file);
        return 1;
    }
    
    FILE *decrypted_file = fopen(dec_filename, "w"); // output file for decrypted content
    if (decrypted_file == NULL) {
        fprintf(stderr, "Error creating decrypted file: %s\n", dec_filename);
    }

    decrypt(encrypted_file, key_file, decrypted_file);


    // Decryption logic goes here

    fclose(encrypted_file);
    fclose(key_file);
    fclose(decrypted_file);
}

int display_encrypted_pass(const char* filename, const char* key_filename) {
    FILE *encrypted_file = fopen(filename, "r"); // file to be decrypted
    FILE *key_file = fopen(key_filename, "r"); // key file

    if (encrypted_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    } else if (key_file == NULL) {
        fprintf(stderr, "Error opening key file: %s\n", key_filename);
        fclose(encrypted_file);
        return 1;
    }

    decrypt(encrypted_file, key_file, stdout);
    fclose(encrypted_file);
    fclose(key_file);
}