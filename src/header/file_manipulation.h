
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

#define SEPARATOR "/"

//delete a file in a directory
void DeleteFile(struct Argument *target_file);

void RestoreFile(struct Logistics *core_logistics, char *target_file, char *restore_path);

//view the contents of directory
//(#5 edit to take Argument member)
void ListDir(struct Logistics *core_logistics, int size_details);

enum action_verbosity {CONCISE, VERBOSE};


#endif