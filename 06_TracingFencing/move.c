#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(
            "Incorrect command line arguments.\n"
            "Usage: ./move infile outfile\n"
        );
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *input_file = fopen(infile, "r");
    if (!input_file) {
        printf("Error opening the input file.\n");
        return 2;
    }

    FILE *output_file = fopen(outfile, "w");
    if (!output_file) {
        printf("Error opening the output file.\n");
        if (fclose(input_file) == EOF) {
            printf("Error closing the input file.\n");
        }
        return 3;
    }

    char c;
    while ((c = fgetc(input_file)) != EOF) {
        if (fputc(c, output_file) == EOF) {
            printf("Error writing into the output file.\n");
            if (fclose(input_file) == EOF) {
                printf("Error closing the input file.\n");
            }
            if (fclose(output_file) == EOF) {
                printf("Error closing the output file.\n");
            }
            if (remove(outfile) == -1) {
                printf("Error deleting the input file.\n");
            }
            return 4;
        }
    }

    if (ferror(input_file)) {
        printf("Error reading the input file.\n");

        if (fclose(input_file) == EOF) {
            printf("Error closing the input file.\n");
        }
        if (fclose(output_file) == EOF) {
            printf("Error closing the output file.\n");
        }
        if (remove(outfile) == -1) {
            printf("Error deleting the input file.\n");
        }
        return 5;
    }

    if (fclose(input_file) == EOF) {
        printf("Error closing the input file.\n");

        if (fclose(output_file) == EOF) {
            printf("Error closing the output file.\n");
        }
        if (remove(outfile) == -1) {
            printf("Error deleting the input file.\n");
        }

        return 6;
    }

    if (fclose(output_file) == EOF) {
        printf("Error closing the output file.\n");

        if (remove(outfile) == -1) {
            printf("Error deleting the input file.\n");
        }
        return 7;
    }

    if (remove(infile) == -1) {
        printf("Error deleting the input file.\n");
        return 8;
    }

    return 0;
}
