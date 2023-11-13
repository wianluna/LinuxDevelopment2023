#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

#include "config.h"

#define LOCALE_PATH "."
#define _(STRING) gettext(STRING)


int main(int argc, char **argv) {
    bindtextdomain("game", LOCALE_PATH);
    textdomain("game");
    setlocale(LC_ALL, "");

    printf(_("Choose number from 1 to 100\n"));

    int left = 1;
    int right = 100;

    while (left != right) {
        int median = (left + right) / 2;
        printf(_("Is your number greater than %d? (y/n)\n"), median);

        char answer[50];
        scanf("%s", answer);

        if (strcmp(answer, _("y")) == 0) {
            left = median + 1;
        } else if (strcmp(answer, _("n")) == 0) {
            right = median;
        }
    }

    printf(_("Your number is %d\n"), right);
    return 0;
}
