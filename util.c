
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_home_path(const char* path)
{
    const char* home = getenv("HOME");

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

