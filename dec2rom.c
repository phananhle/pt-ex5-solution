#include <stdio.h>
#include <stdlib.h>

/* prints an integer in roman numerals */
void print_roman(int n) {
    /* not that we added '9' and '4' in order to ensure that the subtraction rule is correctly applied */
    char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    int pos = 0;

    while (n > 0) {
        /* jump to the position that is still smaller than the number remaining */
        while (values[pos] > n)
            pos++;
        /* print that symbol and subtract it from the value */
        printf("%s", symbols[pos]);
        n -= values[pos];
    }
    printf("\n");

    return;
}

/* main entry point for the program */
int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        print_roman(atoi(argv[i]));
    }

    return (0);
}