#include <stdio.h>
#include <stdlib.h>

#include "dictionary_attack.h"
#include "sha256.h"

#define MAX_PASSWD_LEN 256

/* the SHA256 that should be searched */
BYTE sha256_passwd[SHA256_BLOCK_SIZE];
/* the pointer to the clear-type password */
char *passwd;

/* outputs the SHA256 of a password in the output stream */
int find_passwd(dictionary *current) {
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        if (current->sha256_passwd[i] != sha256_passwd[i])
            return (1);

    /* if we get until here, the SHA256 was a perfect match and we copy the password pointer and break */
    passwd = current->password;
    return (0);
}

/* main entry point of the program */
int main(int argc, char *argv[]) {
    /* parameter check */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dict-file> <passwd-file>\n", argv[0]);
        return (-1);
    }

    FILE *dict_fp = fopen(argv[1], "r");
    if (dict_fp) {
        char buf[MAX_PASSWD_LEN];
        dictionary *head = NULL;

        /* read all lines of the password directory and insert them into the dictionary */
        int no_passwd = 0;
        for (; fgets(buf, MAX_PASSWD_LEN - 1, dict_fp); no_passwd++) {
            int i = 0;
            for (; buf[i] != '\n'; i++)
                ;
            buf[i] = '\0';
            head = add_password(head, buf);
        }

        /* open the password file */
        FILE *passwd_fp = fopen(argv[2], "r");
        if (passwd_fp) {
            char user_id[256];
            char user_sha256[256];

            /* read the user id and the SHA256 of the password */
            while (fscanf(passwd_fp, "%s %s\n", user_id, user_sha256) == 2) {
                /* convert the individual pair of hex digits into an unsigned char (BYTE) */
                for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
                    sscanf(&(user_sha256[i * 2]), "%02hhx", &(sha256_passwd[i]));
                /* reset the password link so the iterator can set it */
                passwd = NULL;
                iterate_dictionary(head, find_passwd);

                /* this should be set to the found entry in the iterator */
                if (passwd)
                    printf("%s %s\n", user_id, passwd);
                else {
                    fprintf(stderr, "Internal error: Could not find password for user %s\n", user_id);
                    return (-4);
                }
            }

            delete_dictionary(head);
        } else {
            fprintf(stderr, "Could not open password file %s\n", argv[1]);
            return (-3);
        }

    } else {
        fprintf(stderr, "Could not open dictionary file %s\n", argv[1]);
        return (-2);
    }

    return (0);
}