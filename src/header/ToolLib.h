
#ifndef STR_MANIPULATION
#define STR_MANIPULATION

#include "main.h"

int cmpstr(char *a, char *b);

char *concat(size_t allocation_size, char *head_pwd, char *separator, char *tail_pwd, int head_direction);
enum cat_extension {KEEP_HEAD, FREE_HEAD};

char *read_message(char *file_path);

int IsPath(char *file_path);

void WriteTo(char *location,  char *message);

int ParseFilecmp(char *argv[], char match);

#endif