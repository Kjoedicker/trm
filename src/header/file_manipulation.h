
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

void DeleteFile(char *target_folder, char *target_file);
void RestoreFile(struct Logistics *core_logistics, char *target_file, char *restore_path);

#endif