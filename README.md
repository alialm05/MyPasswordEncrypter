### A Encryption Tool to encrypt and decrypt files using the impossible-to-crack one-time pad encryption technique.
# Usage
This is mainly intended to be a password manager, and you can run it using: `./pass_manager`
The decrypted file is outputted in the password folder. 

# Encyprt Decrypt
- Use  `./encrypt <filename>` to encrypt a file, this will output an ecnrypted file with a `_enc` suffix alongside its associated key
- Use `./decrypt <filename> <keyfile>` to decrypt a file, it will generate the file with its original name
