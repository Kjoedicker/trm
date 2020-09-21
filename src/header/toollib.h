#ifndef STR_MANIPULATION
#define STR_MANIPULATION

#include "main.h"

int cmpstrings(char *a, char *b);
int pathexists(char *path);
int checkifpath(char *file_path);
// TODO(#4): test
void createfolder(char *folder);
void writetofile(char *location,  char *message);
void reextend(struct Argument *target_file);
char *readfile(char *file_path);
char *extendpath(size_t allocation_size, char *head_pwd, char *separator, char *tail_pwd, int head_direction);
enum {KEEP_HEAD, FREE_HEAD};

#endif
