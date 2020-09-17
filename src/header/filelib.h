
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

#define SEPARATOR "/"

//delete a file in a directory
void deletefile(struct Argument *target_file);
void restorefile(struct Argument *target_file);

//view the contents of directory
//(#5 edit to take Argument member)
void listdir(struct Logistics *core_logistics, int size_details);

enum {CONCISE, VERBOSE};


#endif