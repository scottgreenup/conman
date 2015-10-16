
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool expand_path(const char* path, char** result)
{
    char* home_dir = getenv("HOME");
    if (home_dir == NULL) {
        fprintf(
            stderr,
            "The environment given to conman doesn't have \"HOME\" set."
        );
        return false;
    }

    char* buf = (char*)calloc(2048, sizeof(*buf));
    char* bufi = buf;

    for (const char* c = path; c[0] != '\0'; c++) {
        if (c[0] == '~') {
            strcpy(bufi, home_dir);
            bufi += strlen(home_dir);
        } else {
            bufi[0] = c[0];
            bufi++;
        }
    }

    *result = buf;
    return true;
}

bool is_valid_home_path(const char* path)
{
    const char* home = getenv("HOME");
    if (home == NULL) {
        fprintf(
            stderr,
            "The environment given to conman doesn't have \"HOME\" set."
        );
        return false;
    }

    int path_len = strlen(path);
    int home_len = strlen(home);
    if (path_len > home_len) {
        if (!strncmp(path, home, home_len)) {
            return true;
        }
    }
    if (path[0] != '~') {
        return false;
    }
    return true;
}

bool is_valid_root_path(const char* path)
{
    if (path[0] != '/') {
        return false;
    }
    int len = strlen(path);
    return true;
}

bool is_alphanumeric(const char* string)
{
    for (const char* c = string; c[0] != '\0'; c++) {
        if ((c[0] >= 48 && c[0] <= 57)
        || (c[0] >= 65 && c[0] <= 90)
        || (c[0] >= 97 && c[0] <= 122)) {
            continue;
        }

        return false;
    }
    return true;
}

