#ifndef PARSING
#define PARSING

#include "main.h"

#define Parse void

struct Argument {
    char *file_path;
    char *destination_pwd;
    char *parsed_file_path;
    char *trace_file_loc;

    struct Logistics *logistics;
};

//free all of the malloc'd data before freeing itself
Parse free_Argument(struct Argument *target);

//data
struct Argument *ParseFile(char *file_path);

char *ParseFilePath(char *target_file);
char *ParseFilePWD(struct Argument *file);

Parse ParseQueuedFiles(
                void (*Execute) (struct Argument *target_file), 
                char *target_files[], 
                int min_index, 
                int max_index);

#endif