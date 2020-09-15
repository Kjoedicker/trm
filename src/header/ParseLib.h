#ifndef PATH_MANIPULATION1
#define PATH_MANIPULATION1

#include "main.h"

#define Parse void
#define Parse_char char

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

//action
Parse_char *ParseFilePath(char *target_file);
Parse_char *ParseFilePWD(struct Argument *file);




// int ParseQueuedFiles(Parse_char *target_folder, Parse_char *target_files[], int total);
Parse ParseQueuedFiles(void (*Execute) (struct Argument *target_file), 
                     char *target_files[], 
                     int min_index, 
                     int max_index);





#endif