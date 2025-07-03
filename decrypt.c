#include <stdio.h>
#include <stdlib.h>
#include "encryption_manager.h"

/*void decrypt(FILE* encrypted_file, FILE* key_file, FILE* decrypted_file) {
    int enc_c, key;
    while ((enc_c = fgetc(encrypted_file)) != EOF && (key = fgetc(key_file)) != EOF) {
        int dec_c = enc_c ^ key; // XOR the character with the key
        fputc(dec_c, decrypted_file); // Write the decrypted character to the output file
    }
}*/

int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <encrypted_file> <key_file>\n", argv[0]);
        return 1;
    }
    else {

        setup_decrypt(argv[1], argv[2]);

    }

}