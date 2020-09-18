#ifndef STR_MANIPULATION
#define STR_MANIPULATION

#include "main.h"

int cmpstrings(char *a, char *b);
int pathexists(char *path);
int checkifpath(char *file_path);

void createfolder(char *folder);
void writetofile(char *location,  char *message);

char *readfile(char *file_path);
void reextend(struct Argument *target_file);
char *extendpath(size_t allocation_size, char *head_pwd, char *separator, char *tail_pwd, int head_direction);
enum {KEEP_HEAD, FREE_HEAD};

#endif