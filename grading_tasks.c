#include <stdio.h>

#include "grading_table.h"

/* prints the grading entry */
void taskA(grading_table_ptr current) {
    printf("%d hat in %d %d Punkt(e) erreicht.\n", current->mat_no, current->series, current->points);
}

/* prints the grading entry if the number of points were less than 10 */
void taskB(grading_table_ptr current) {
    if (current->points < 10) {
        printf("%d %d\n", current->mat_no, current->series);
    }
}

/* counts the number of grading entries */
int taskC(grading_table_ptr current, int val) {
    return val + 1;
}

/* determines the maximum number of points */
int taskD(grading_table_ptr current, int val) {
    return (current->points > val) ? current->points : val;
}

/* counts the number of points for series 3 */
int taskE(grading_table_ptr current, int val) {
    return (current->series == 3) ? val + current->points : val;
}

/* main entry point for the program */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s (a|b|c|d|e) [filename]\n", argv[0]);
        return 1;
    }

    char task = argv[1][0];
    FILE *fp = (argc == 3) ? fopen(argv[2], "r") : stdin;

    grading_table_ptr list = read_list(fp);

    switch (task) {
        case 'a':
            traverse_list(list, taskA);
            break;
        case 'b':
            traverse_list(list, taskB);
            break;
        case 'c':
            printf("%d\n", reduce_list(list, taskC, 0));
            break;
        case 'd':
            printf("%d\n", reduce_list(list, taskD, 0));
            break;
        case 'e':
            printf("%d\n", reduce_list(list, taskE, 0));
            break;
        default:
            fprintf(stderr, "Unknown task: %c\n", task);
            return 2;
    }
    delete_list(list);

    return 0;
}