
#include <errno.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "util.h"

#define CM_DIRECTORY "./.conman/"
#define CM_DATA CM_DIRECTORY "data"

typedef struct {
    char file[PATH_MAX];
    char link[PATH_MAX];
    char category[PATH_MAX];
    bool copy;
} config_file_t;

void print_usage()
{
    fprintf(
        stderr,
        "\n"
        "conman usage:\n"
        "\n"
        "    conman init\n"
        "        Run this to init a directory that will hold config files.\n"
        "\n"
        "    conman add <filename> <linklocation> [category]\n"
        "\n"
        "    conman drop <filename>\n"
        "        Removes a filename from the registry, non-deleting\n"
        "\n"
        "    conman rm <filename>\n"
        "        Removes a filename from the registry\n"
        "\n"
        "    conman linkall [category]\n"
        "        Links all files to their link location\n"
        "\n"
        "    conman edit <filename> <attribute> <value>\n"
        "        Attributes include filename, linklocation, copy, and category\n"
        "\n"
        "    conman info [filename]\n"
        "        Lists all filenames or,\n"
        "        shows associated attributes with a filename\n"
    );
}

/**
 * init() creates the CM_DIRECTORY directory and creates an empty CM_DATA file.
 * This effectively creates a way to test if a directory is a conman directory.
 */
int init(int c, char* v[])
{
    if (c != 0) {
        return EXIT_FAILURE;
    }
    if (mkdir(CM_DIRECTORY, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) {
        if (errno != EEXIST) {
            perror(NULL);
            return EXIT_FAILURE;
        }
    }

    FILE* data = fopen(CM_DATA, "w");
    if (data == NULL) {
        perror(NULL);
        return EXIT_FAILURE;
    }
    if (fclose(data)) {
        perror(NULL);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * add() expects at 2 or 3 arguments in v:
 *  1. the filename to be saved
 *  2. the location to be symbolically linked to
 *  3. optionally, the category the filename comes under
 */
int add(int c, char* v[])
{
    config_file_t cf;

    if (c == 2) {
        if (access(v[0], F_OK)) {
            perror(NULL);
            return EXIT_FAILURE;
        }

        bool valid_home = is_valid_home_path(v[1]);
        bool valid_root = is_valid_root_path(v[1]);

        /* TODO allow relative path naming for the link location */
        if (!valid_home && !valid_root) {
            fprintf(
                stderr,
                "The link location must be a full path name.\n"
            );
            return EXIT_FAILURE;
        }

        if (valid_home && valid_root) {
            int home_len = strlen(getenv("HOME"));

            cf.file[0] = '~';

            memcpy(cf.file + 1)


        }

        /* TODO check file exists */
        /* TODO check linklocation is free */
        /* TODO add file to the registry */


        if (c == 3) {
            /* TODO add category attribute to object */
        }

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int drop(int c, char* v[])
{
    return EXIT_FAILURE;
}

int main(int argc, char* argv[])
{
    if (argc < 2 || !strcmp(argv[1], "-h")) {
        print_usage();
        return EXIT_FAILURE;
    }

    int result = EXIT_FAILURE;

    if (!strcmp(argv[1], "init")) {
        result = init(argc - 2, argv + 2);
    } else if (!strcmp(argv[1], "add")) {
        result = add(argc - 2, argv + 2);
    } else if (!strcmp(argv[1], "drop")) {

    } else if (!strcmp(argv[1], "rm")) {

    } else if (!strcmp(argv[1], "linkall")) {

    } else if (!strcmp(argv[1], "edit")) {

    } else if (!strcmp(argv[1], "info")) {

    }

    if (result == EXIT_FAILURE) {
        print_usage();
    }
    return result;
}

