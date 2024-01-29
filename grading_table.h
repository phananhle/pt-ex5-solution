#ifndef GRADING_TABLE_H
#define GRADING_TABLE_H

#include <stdint.h>
#include <stdio.h>

struct grading_entry_t {
    uint32_t mat_no;              /* matriculation number */
    uint16_t series;              /* series */
    uint16_t points;              /* points scored */
    struct grading_entry_t *next; /* pointer to the next entry */
};

typedef struct grading_entry_t *grading_table_ptr;

/* reads a grading table from the file stream */
extern grading_table_ptr read_list(FILE *fp);
/* deletes the complete list of grades */
extern void delete_list(grading_table_ptr head);
/* traverses the list of all grading */
extern void traverse_list(grading_table_ptr head, void (*visitor)(grading_table_ptr current));
/* reduces all grades recursively to a single number */
extern int reduce_list(grading_table_ptr head, int (*visitor)(grading_table_ptr current, int val), int start_val);

#endif /* GRADING_TABLE */
