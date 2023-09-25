#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define DX 3


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Provide filename\n");
        return 1;
    }
    
    struct stat info;
    stat(argv[1], &info);
    off_t len = info.st_size;
    char *buf = (char *)calloc(len + 1, sizeof(char));

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Opening of the file is failed\n");
        return 1;
    }
    read(fd, buf, info.st_size);
    close(fd);

    int num_lines = 0;
    for (int i = 0; i < len; ++i) {
        if (buf[i] == '\n') {
            ++num_lines;
        }
    }

    int* idx_lines = (int *)calloc(num_lines, sizeof(int));
    int j = 1;
    idx_lines[0] = 0;
    for (int i = 0; i < len; ++i) {
        if (buf[i] == '\n') {
            idx_lines[j] = i + 1;
            ++j;
        }
    }

    initscr();
    noecho();
    cbreak();
    printw("%s", argv[1]);
    refresh();

    WINDOW *win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);

    keypad(win, TRUE);
    scrollok (win, TRUE);

    for (int i = 0; i < COLS - 2 * DX - 2 && i< num_lines; ++i) {
        buf[idx_lines[i + 1] - 1] = '\0';
        mvwprintw(win, i + 2, 3, "%d: %.80s\n", i + 1, buf + idx_lines[i]);
        buf[idx_lines[i + 1] - 1] = '\n';
    }
    box(win, 0, 0);

    int c;
    int n = 0;
    while ((c = wgetch(win)) != 27) {
        if (c == KEY_DOWN || c == 32) {
            if (n < num_lines) {
                ++n;
            }
        } else if (c == KEY_UP) {
            if (n > 0) {
                --n;
            }
        }
    
        werase(win);
        for (int i = 0; i < COLS - 2 * DX - 2 && i + n < num_lines; ++i) {
            buf[idx_lines[i + n + 1] - 1] = '\0';
            mvwprintw(win, i + 2, 3, "%d: %.80s\n", i + n + 1, buf + idx_lines[i + n]);
            buf[idx_lines[i + n + 1] - 1] = '\n';
        }
        box(win, 0, 0);
        wrefresh(win);
    }
    endwin();

    free(idx_lines);
    free(buf);
    return 0;
}