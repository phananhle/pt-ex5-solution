#include "dictionary_attack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* adds a new entry to a dictionary list and returns the new head */
dictionary *add_password(dictionary *head, const char *passwd) {
    dictionary *new_entry = (dictionary *)malloc(sizeof(dictionary));

    /* copy password */
    new_entry->password = (char *)malloc((strlen(passwd) + 1) * sizeof(char));
    strcpy(new_entry->password, passwd);

    /* add the new SHA256 for the password */
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (BYTE *)passwd, strlen(passwd));
    sha256_final(&ctx, new_entry->sha256_passwd);

    /* make the old head the next element and return the pointer to the new element as the new head */
    new_entry->next = head;
    return (new_entry);
}
/* deletes a whole dictionary */
void delete_dictionary(dictionary *head) {
    while (head) {
        free(head->password);
        dictionary *tmp = head->next;
        free(head);
        head = tmp;
    }

    return;
}
/* iterates through a dictionary until a condition is true */
void iterate_dictionary(dictionary *head, int (*condition)(dictionary *current)) {
    while (head && condition(head)) {
        head = head->next;
    }

    return;
}
