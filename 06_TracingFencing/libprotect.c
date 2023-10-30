#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>


int remove(const char *pathname) {
    if (strstr(pathname, "PROTECT") == 0) {
        int (*std_remove)(const char *) = dlsym(RTLD_NEXT, "remove");
        return std_remove(pathname);
    }

    return 0;
}
