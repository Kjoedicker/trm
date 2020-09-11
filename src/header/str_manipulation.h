
#ifndef STR_MANIPULATION
#define STR_MANIPULATION

#include "main.h"

int cmpstr(char *a, char *b);

char *concat(size_t allocation_size, char *head_pwd, char *separator, char *tail_pwd, int head_direction);
enum cat_extension {KEEP_HEAD, FREE_HEAD};

int stripcmp(char *argv[], char match);

#endif