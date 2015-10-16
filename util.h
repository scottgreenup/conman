#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * Expand path will expand common shell aliases, including '~' for the home
 * directory.
 */
bool expand_path(const char* path, char** result);

/**
 * Checks if the path is a valid path string that starts with getenv("HOME")
 * or with '~'
 */
bool is_valid_home_path(const char* path);

/**
 * Checks if the path is a valid path that starts from root.
 */
bool is_valid_root_path(const char* path);

/**
 * Check string is alphanumeric
 */
bool is_alphanumeric(const char* string);

#endif
