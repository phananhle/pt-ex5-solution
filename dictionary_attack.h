#ifndef __DICTIONARY_ATTACK_H__
#define __DICTIONARY_ATTACK_H__

#include "sha256.h"

/* the structure that stores a password of a dictionary */
typedef struct dictionary_ {
    char *password;                        /* the password in clear type */
    BYTE sha256_passwd[SHA256_BLOCK_SIZE]; /* the SHA256 of the password */
    struct dictionary_ *next;              /* the pointer to the next password (or NULL) */
} dictionary;

/* adds a new entry to a dictionary list and returns the new head */
extern dictionary *add_password(dictionary *head, const char *passwd);
/* deletes a whole dictionary */
extern void delete_dictionary(dictionary *head);
/* iterates through a dictionary until a condition is true */
extern void iterate_dictionary(dictionary *head, int (*condition)(dictionary *current));

#endif