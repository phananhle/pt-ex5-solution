#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char shift(int c, int key)
{
    if (!isalpha(c)) return c; // only shift alphabetic characters
    
    int offset = isupper(c) ? 'A' : 'a'; 

    c -= offset;
    c += key;
    c = ((c < 0) ? (c + 26) : c) % 26;
    c += offset;
    return c;
}

/* encrypts a string with a Caesar chiffre */
void caesar_encrypt(char *s, int key) {
    key %= 26; /* we dont want to risk an over / underflow */
    for (; *s; s++) {
        *s = shift(*s, key);
    }
}

/* decrypts a string with a Caesar chiffre */
void caesar_decrypt(char *s, int key) {
    key = -key; /* decrypting is shifting in negative direction */
    key %= 26;  /* we dont want to risk an over / underflow */
    for (; *s; s++) {
        *s = shift(*s, key);
    }
}

#define MAX_LEN 1024

int main(int argc, char *argv[]) {
    static char buffer[MAX_LEN];

    /* parameter check */
    if (argc != 3) {
        printf("Usage: %s [encrypt|decrypt] key\n", argv[0]);
        return 1;
    }

    /* extract the key */
    int key = atoi(argv[2]);

    /* parse the command string */
    if (!strcmp("encrypt", argv[1])) {
        while (fgets(buffer, MAX_LEN, stdin)) {
            caesar_encrypt(buffer, key);
            fputs(buffer, stdout);
        }
    } else if (!strcmp("decrypt", argv[1])) {
        while (fgets(buffer, MAX_LEN, stdin)) {
            caesar_decrypt(buffer, key);
            fputs(buffer, stdout);
        }
    } else {
        printf("Invalid command.\n");
    }

    return (0);
}
