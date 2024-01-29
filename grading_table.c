#include "grading_table.h"

#include <stdlib.h>

/* reads a grading table from the file stream */
grading_table_ptr read_list(FILE *fp) {
    grading_table_ptr head = NULL, tail = NULL;

    while (1) {
        /* allocate memory for the new entry */
        grading_table_ptr new_entry = malloc(sizeof(struct grading_entry_t));

        /* read the entry from disc */
        fread(&new_entry->mat_no, sizeof(new_entry->mat_no), 1, fp);
        if (feof(fp)) {
            free(new_entry);
            return head;
        }
        fread(&new_entry->series, sizeof(new_entry->series), 1, fp);
        fread(&new_entry->points, sizeof(new_entry->points), 1, fp);

        /* append the entry to the tail of the list */
        new_entry->next = NULL;
        if (!head) {
            head = tail = new_entry;
        } else {
            tail->next = new_entry;
            tail = new_entry;
        }
    }

    return head;
}

/* deletes the complete list of grades */
void delete_list(grading_table_ptr head) {
    while (head) {
        /* remote the current head and promote the next entry to the head of the list */
        grading_table_ptr tmp = head->next;
        free(head);
        head = tmp;
    }

    return;
}

/* traverses the list of all grading */
void traverse_list(grading_table_ptr head, void (*visitor)(grading_table_ptr current)) {
    while (head) {
        /* jump from current head to the successor */
        visitor(head);
        head = head->next;
    }

    return;
}

/* reduces all grades recursively to a single number */
int reduce_list(grading_table_ptr head, int (*visitor)(grading_table_ptr current, int val), int start_val) {
    int val = start_val;

    while (head) {
        val = visitor(head, val);
        head = head->next;
    }
    return val;
}
