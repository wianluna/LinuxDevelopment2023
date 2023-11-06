#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include <rhash.h>


int
main() {
    char *line = NULL;
    size_t nread;
    size_t len = 0;

    char digest[64];
    char output[130];
    rhash_library_init();

    #ifndef READLINE
    while ((nread = getline(&line, &len, stdin)) != -1) {
    #else
    while ((line = readline(NULL)) != NULL) {
    #endif
        char *hash_alg = strtok(line, " ");
        if (!hash_alg) {
            continue;
        }

        unsigned hash_type;
        if (!strcasecmp(hash_alg, "md5")) {
            hash_type = RHASH_MD5;
        } else if (!strcasecmp(hash_alg, "sha1")) {
            hash_type = RHASH_SHA1;
        } else if (!strcasecmp(hash_alg, "tth")) {
            hash_type = RHASH_TTH;
        } else {
            fprintf(stderr, "Error: wrong hash function.\n");
            continue;
        }
    
        unsigned out_type = islower(hash_alg[0]) ? RHPR_BASE64 : RHPR_HEX;

        char *arg = strtok(NULL, " ");
        if (!arg) {
            fprintf(stderr, "Error: wrong second argument.\n");
            continue;
        }

        int res;
        if (arg[0] == '"') {
            res = rhash_msg(hash_type, &arg[1], strlen(&arg[1]), digest);
            if (res < 0) {
                fprintf(stderr, "rhash_msg error\n");
                continue;
            }
        } else {
            res = rhash_file(hash_type, arg, digest);
            if (res < 0) {
                fprintf(stderr, "rhash_file error\n");
                continue;
            }
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type), out_type);
        printf("%s\n", output);

        free(line);
        line = NULL;
    }

    return 0;
}
