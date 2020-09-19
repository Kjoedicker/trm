#ifndef PARSING
#define PARSING

#include "main.h"

struct Argument {
    char *file_path;
    char *destination_pwd;
    char *parsed_file_path;
    char *trace_file_loc;
    char *restore_path;

    struct Logistics *logistics;
};

//free all of the malloc'd data before freeing itself
void freearguments(struct Argument *target);

//data
struct Argument *parsefile(char *file_path);

char *parsefilepath(char *target_file);
char *parsefilepwd(struct Argument *file);
void parserestorefile(char *filename, char *restorepath);

void parsequeuedfiles(
                void (*Execute) (struct Argument *target_file), 
                char *target_files[], 
                int min_index, 
                int max_index);

#endif