#ifndef PATH_MANIPULATION
#define PATH_MANIPULATION

struct Argument {
    char *argument;
    char *parsed_argument;
    int IsPath;
    char *current_pwd;
    char *destination_pwd;
};

//data
struct Argument *strip(char *argument);

//action
char *ParseFilePath(char *target_file);

//logic
int IsPath(char *argument);

int ParseQueuedFiles(char *target_folder, char *target_files[], int total);

#endif