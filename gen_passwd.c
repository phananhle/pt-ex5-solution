#include <stdio.h>
#include <stdlib.h>

#include "dictionary_attack.h"
#include "sha256.h"

#define MAX_PASSWD_LEN 256

/* pointer to output stream */
FILE *fp_out;
/* chance that a password will be put into the output stream */
float p;

/* outputs the SHA256 of a password in the output stream */
int output_passwd(dictionary *current) {
    static int user_cnt;

    if ((float)rand() / (float)RAND_MAX < p) {
        fprintf(fp_out, "user%d ", ++user_cnt);
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
            fprintf(fp_out, "%02x", current->sha256_passwd[i]);
        fprintf(fp_out, "\n");
    }
    return (1);
}

/* main entry point of the program */
int main(int argc, char *argv[]) {
    /* parameter check */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s N <dict-name> [<file-name>]\n", argv[0]);
        return (-1);
    }

    int N = atoi(argv[1]);
    FILE *dict_fp = fopen(argv[2], "r");
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

        printf("%d passwords read and hashed\n", no_passwd);

        /* open the output stream */
        fp_out = (argc == 3) ? stdout : fopen(argv[3], "w");
        if (fp_out) {
            p = (float)N / (float)no_passwd;
            iterate_dictionary(head, output_passwd);
            delete_dictionary(head);
        } else {
            fprintf(stderr, "Could not open output file %s\n", (argc == 3) ? argv[3] : "stdin");
            return (-3);
        }
    } else {
        fprintf(stderr, "Could not open dictionary file %s\n", argv[2]);
        return (-2);
    }

    return (0);
}
