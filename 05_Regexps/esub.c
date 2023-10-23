#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BAGS 10


int main(int argc, char **argv) {
    if (argc != 4) {
        printf(
            "Incorrect command line arguments.\n"
            "Usage: ./esub regexp substitution string\n"
        );
        return 1;
    }

    char *substitution = argv[2];
    char *string = argv[3];

    regex_t regexp;
    int rc;
    char err_buffer[100];
    regmatch_t bags[MAX_BAGS];
 
    if ((rc = regcomp(&regexp, argv[1], REG_EXTENDED)) != 0) {
        regerror(rc, &regexp, err_buffer, 100);
        printf("regcomp() failed with '%s'\n", err_buffer);
        return 1;
    }

    if (regexec(&regexp, string, MAX_BAGS, bags, 0) != 0) {
        printf("%s\n", string);
        regfree(&regexp);
        return 0;
    }

    int prev_backslash = 0;
    int cur_pos = 0;

    while (cur_pos < bags[0].rm_so) {
        printf("%c", string[cur_pos]);
        cur_pos++;
    }

    for (int i = 0; i < strlen(substitution); ++i) {
        if (substitution[i] == '\\') {
            if (prev_backslash) {
                prev_backslash = 0;
                printf("\\");
            } else {
                prev_backslash = 1;
            }
        } else if (prev_backslash && isdigit(substitution[i])) {
            int idx_bag = substitution[i] - '0';
            if (bags[idx_bag].rm_so == -1) {
                printf("\nNon-existing capture group \\%d\n", idx_bag);
                regfree(&regexp);
                return 1;
            }
            for (int j = bags[idx_bag].rm_so; j < bags[idx_bag].rm_eo; ++j) {
                printf("%c", string[j]);
            }
            prev_backslash = 0;
        } else if (prev_backslash) {
            printf("\\");
            prev_backslash = 0;
            printf("%c", substitution[i]);
        } else {
            printf("%c", substitution[i]);
        }
    }

    cur_pos = bags[0].rm_eo;
    while (cur_pos < strlen(string)) {
        printf("%c", string[cur_pos]);
        cur_pos++;
    }
    
    printf("\n");
    regfree(&regexp);
    return 0;
}
