
#include <errno.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wordexp.h>

#include "util.h"

#define ROOT_DIR                "~"
#define CM_DIR                  ROOT_DIR "/.conman/"
#define CM_METAFILE_USING       CM_DIR ".using"

typedef struct {
    char file[PATH_MAX];
    char link[PATH_MAX];
    char category[PATH_MAX];
    bool copy;
} config_file_t;

int setup_conman_dir()
{
    char* result = NULL;
    if (!expand_path(CM_DIR, &result)) {
        return EXIT_FAILURE;
    }
    if (mkdir(result, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) {
        if (errno != EEXIST) {
            perror("me");
            return EXIT_FAILURE;
        }
    }
    free(result);

    result = NULL;
    if (!expand_path(CM_METAFILE_USING, &result)) {
        return EXIT_FAILURE;
    }
    FILE* data = fopen(result, "a");
    if (data == NULL) {
        perror(CM_METAFILE_USING);
        return EXIT_FAILURE;
    }
    if (fclose(data)) {
        perror("c");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * init() creates the CM_DIRECTORY directory and creates an empty CM_DATA file.
 * This effectively creates a way to test if a directory is a conman directory.
 */
int init(int c, char* v[])
{
    if (c != 0) {
        fprintf(
            stderr,
            "conman init does not take additional parameters\n"
        );
        return EXIT_FAILURE;
    }

    // create .git directory
    char* result = NULL;
    if (!expand_path(CM_METAFILE_USING, &result)) {
        return EXIT_FAILURE;
    }
    FILE* data = fopen(result, "r");
    if (data == NULL) {
        perror(CM_METAFILE_USING);
        return EXIT_FAILURE;
    }

    char buff[512] = {0};
    fgets(buff, 512, data);
    buff[strlen(buff) - 1] = '\0';

    if (fclose(data)) {
        perror(NULL);
        return EXIT_FAILURE;
    }

    char git_path[2048] = {0};
    char* gpi = git_path;
    result = NULL;
    if (!expand_path(CM_DIR, &result)) {
        return EXIT_FAILURE;
    }
    strcpy(gpi, result);
    gpi += strlen(result);
    strcpy(gpi, buff);
    gpi += strlen(buff);

    // TOOD mkdir
    if (mkdir(git_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) {
        if (errno != EEXIST) {
            perror("me");
            return EXIT_FAILURE;
        }
    }

    strcpy(gpi, "/.git");

    fprintf(stderr, "%s\n", git_path);

    pid_t pid = fork();
    if (pid == 0) {
        execlp("git", "git", "--git-dir", git_path, "init", NULL);
    } else if (pid > 0) {

    } else {
        perror(NULL);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int use(int c, char* v[])
{
    if (c == 0) {
        fprintf(
            stderr,
            "usage: conman use <repository>\n"
        );
        return EXIT_FAILURE;
    }

    char* path = NULL;
    if (!expand_path(CM_METAFILE_USING, &path)) {
        fprintf(
            stderr,
            "Could not expand %s\n",
            CM_METAFILE_USING
        );
        return EXIT_FAILURE;
    }
    FILE* data = fopen(path, "w");
    if (data == NULL) {
        perror(NULL);
        return EXIT_FAILURE;
    }
    int result = is_alphanumeric(v[0]) ? EXIT_SUCCESS : EXIT_FAILURE;
    if (result == EXIT_SUCCESS) {
        fprintf(data, "%s\n", v[0]);
    } else {
        fprintf(
            stderr,
            "Input was not alphanumeric '%s'\n",
            v[0]
        );
    }
    if (fclose(data)) {
        perror(NULL);
        return EXIT_FAILURE;
    }
    return result;
}

/**
 * Common use cases include:
 *
 *   conman add ./file
 *   conman add /home/user/.file
 *   conman add ./dir
 *   conman add /home/user/dir
 */
int add(int c, char* v[]) {
    // v[0] == filename
    // detect if file or directory?
    // mv the file
    // symlink back

    struct stat buf;
    if (stat(v[0], &buf) == 0) {
        return EXIT_FAILURE;
    }
    if (buf.st_mode & S_IFMT == buf.st_mode) {

    }
}

int main(int argc, char* argv[])
{
    if (setup_conman_dir() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    if (argc < 2) {
        return EXIT_FAILURE;
    }

    char* command = argv[1];
    argv = argv + 2;
    argc = argc - 2;

    int result = EXIT_FAILURE;

    if (!strcmp(command, "add")) {
        add(argc, argv);
    } else if (!strcmp(command, "clone")) {

    } else if (!strcmp(command, "commit")) {

    } else if (!strcmp(command, "diff")) {

    } else if (!strcmp(command, "init")) {
        result = init(argc, argv);
    } else if (!strcmp(command, "link")) {

    } else if (!strcmp(command, "pull")) {

    } else if (!strcmp(command, "push")) {

    } else if (!strcmp(command, "remote")) {

    } else if (!strcmp(command, "rm")) {

    } else if (!strcmp(command, "use")) {
        result = use(argc, argv);
    }

    // .conman will need to maintain a record of files in the git repo and their
    // associated location in the filesystem
    // .conman/files is the git repository itself

    return result;
}

