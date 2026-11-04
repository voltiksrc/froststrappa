#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validate.h"

#define FROSTSTRAPPA_VERSION "0.1.0"

void help(void) {
    puts("froststrappa - Crypt Linux bootstrapper");
    putchar('\n');
    puts("usage: froststrappa <target_root> [packages...]");
    puts("Options:");
    puts("  --help,    Show this help message.");
    puts("  --version, Show froststrappas version.");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "froststrappa: please enter the target root\n");
        printf("you would like to install on.\n");
        return 1;
    }

    // Set our arguments to the first subcommand
    // after 'froststrappa'
    char* args = argv[1];

    if (strcmp(args, "--help") == 0 || strcmp(args, "-h") == 0) {
        help();
        return 0;
    } else if (strcmp(args, "--version") == 0) {
        printf("froststrappa %s\n", FROSTSTRAPPA_VERSION);
        return 0;
    } else if (argv[1][0] == '-') {
        fprintf(stderr, "froststrappa: unknown flag '%s'\n", args);
        return 1;
    }

    // Make sure there is atleast one package specified
    // otherwise no packages will be installed.
    if (argc < 3) {
        fprintf(stderr, "froststrappa: no packages specified\n");
        return 1;
    }

    // First positional argument is the target root
    char* resolved_path = realpath(argv[1], NULL);

    if (resolved_path == NULL) {
        perror("realpath");
        return 1;
    }

    bool valid = check_target(resolved_path);

    if (valid) {
        valid = check_mount(resolved_path);
    }

    free(resolved_path);

    if (!valid) {
        return 1;
    }

    // Iterate through every selected package
    for (int i = 2; i < argc; i++) {
        printf("Package: %s\n", argv[i]);
    }

    return 0;
}
