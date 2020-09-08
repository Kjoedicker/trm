
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

//global seperator for concat_paths
const char *SEPARATOR = "\\0";

//delete a file in a directory
void DeleteFile(char *target_folder, char *target_file);

void RestoreFile(struct Logistics *core_logistics, char *target_file, char *restore_path);

//view the contents of directory
void ListDir(char *target_folder, int size_details);
enum action_verbosity {CONCISE, VERBOSE};


#endif