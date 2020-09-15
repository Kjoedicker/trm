#ifndef PATH_MANIPULATION1
#define PATH_MANIPULATION1

#include "main.h"

struct Argument {
    char *file_path;
    char *destination_pwd;
    char *parsed_file_path;
    char *trace_file_loc;

    struct Logistics *logistics;
};

//data
struct Argument *strip(char *file_path);

//action
char *ParseFilePath(char *target_file);
char *GetFilePWD(struct Argument *file);


//logic
int IsPath(char *file_path);

// int ParseQueuedFiles(char *target_folder, char *target_files[], int total);
int ParseQueuedFiles(void (*Execute) (struct Argument *target_file), 
                     char *target_files[], 
                     int min_index, 
                     int max_index);


//free all of the malloc'd data before freeing itself
void free_Argument(struct Argument *target);


#endif