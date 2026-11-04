#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include "validate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_mount(const char* target_root) {
    FILE* fp = fopen("/proc/self/mountinfo", "r");
    if (fp == NULL) {
        perror("froststrappa: mountinfo");
        return false;
    }

    char* line = NULL;
    size_t capacity = 0;
    bool mounted = false;

    while (getline(&line, &capacity, fp) != -1) {
        int field = 0;
        char* saveptr = NULL;
        char* token = strtok_r(line, " ", &saveptr);

        while (token != NULL) {
            field++;

            // The fifth field in mountinfo is the mountpoint.
            if (field == 5) {
                mounted = strcmp(token, target_root) == 0;
                break;
            }

            token = strtok_r(NULL, " ", &saveptr);
        }

        if (mounted)
            break;
    }

    // Free the line allocated by getline and close mountinfo.
    free(line);
    fclose(fp);

    if (!mounted)
        fprintf(stderr, "froststrappa: '%s' is not mounted.\n", target_root);

    return mounted;
}

bool check_target(const char* target_root) {
    if (target_root == NULL || target_root[0] != '/') {
        fprintf(stderr, "froststrappa: invalid target root.\n");
        return false;
    }

    // main() must pass a path already resolved by realpath().
    if (strcmp(target_root, "/") == 0 || strcmp(target_root, "/root") == 0) {
        fprintf(stderr, "froststrappa: I will not voluntarily destroy your system buddy.\n");
        return false;
    }

    return true;
}
