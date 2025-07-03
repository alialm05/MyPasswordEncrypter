#include <stdio.h>
#include <stdlib.h>
#include "encryption_manager.h"

/*void encrypt(FILE* file, FILE* encrypted_file, FILE* key_file) {
    // Encryption logic goes here
    int c;
    while ((c = fgetc(file)) != EOF) {
        // Generate a random key for each character
        int key = rand() % 256; // Random key between 0 and 255
        int encrypted_char = c ^ key;
        fputc(encrypted_char, encrypted_file); // XOR the character with the key
        fputc(key, key_file); // Write the key to the key file
    }
}*/

int main (int argc, char* argv[]){

    if (argc != 2) {
        fprintf(stderr, "Usage: %s  <filename>\n", argv[0]);
        return 1;
    }else {

        setup_enc(argv[1]);

        return 0;
    }
    

}