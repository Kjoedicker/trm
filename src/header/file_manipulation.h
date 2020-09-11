
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

#define SEPARATOR "/"

//delete a file in a directory
void DeleteFile(char *target_folder, char *target_file);

void RestoreFile(struct Logistics *core_logistics, char *target_file, char *restore_path);

//view the contents of directory
void ListDir(char *target_folder, int size_details);
enum action_verbosity {CONCISE, VERBOSE};


#endif