#ifndef STR_MANIPULATION
#define STR_MANIPULATION

#include "main.h"
#include <time.h>
int cmpstrings(char *a, char *b);
int pathexists(char *path);
int checkifpath(char *origin);
int checktext(char *text);
void createfolder(char *folder);
char *getdate();
void writetofile(struct Argument *file);
void reextend(struct Argument *target_file);
char *readfile(char *origin);
char *extendpath(size_t allocation_size, char *head_pwd, char *separator, char *tail_pwd, int head_direction);
enum {KEEP_HEAD, FREE_HEAD};
enum {INVALID, VALID};

#endif
