#ifndef PARSING
#define PARSING

#include "main.h"

struct Argument {
    char *origin;
    char *parsed_origin;
    char *destination;
    char *restore_path;
    char *trash_info;
    char *date_modified;

    struct Logistics *logistics;
};

//free all of the malloc'd data before freeing itself
void freearguments(struct Argument *target);

//data
struct Argument *parsefile(char *origin);

char *parsefilepath(char *target_file);
char *parsefilepwd(struct Argument *file);
char *parseinfofile(char *filename);
void parserestorefile(char *filename, char *restorepath);
char *parsetext(char *text, char *pattern);
void parsemessage(struct Argument *file);

void parsequeuedfiles(
                void (*Execute) (struct Argument *target_file), 
                char *target_files[], 
                int min_index, 
                int max_index);

#endif