
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

#define SEPARATOR "/"

void deletefile(struct Argument *target_file);
void restorefile(struct Argument *target_file);

void listdir(struct Logistics *core_logistics, int size_details);

enum {CONCISE, VERBOSE};

#endif