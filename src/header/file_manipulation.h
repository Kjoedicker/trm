
#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

#include "main.h"

void DeleteFile(struct Logistics *core_logistics, char *target_file);
void RestoreFile(struct Logistics *core_logistics, char *target_file, char *restore_path);

#endif