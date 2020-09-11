#include "../header/main.h"

int ParseQueuedFiles(char *target_folder, char *target_files[], int total)
{
    struct Argument *parsed_file = strip(target_files[total]);

    if ((total - 1) == 0)
    {
        printf("%s\n", parsed_file->parsed_argument);
        // DeleteFile(target_folder, target_files[total]);
        free(parsed_file);
        return 0;
    }

    // DeleteFile(target_folder, target_files[total]);
    printf("%s\n", parsed_file->parsed_argument);
    ParseQueuedFiles(target_folder, target_files, total-1);

    free(parsed_file);
    return 0;
}

//given a path, return the destination
char *ParseFilePath(char *argument)
{   
    //copy over so we can work with a terminated string
    char *provided_path = malloc(sizeof(char) * 25);
    strcpy(provided_path, argument);

    char *parsed_name = malloc(sizeof(char) * 50);
    int index = 0;

    for (int pp_index = 0; provided_path[pp_index] != '\0'; pp_index++)
    {
        //skip this and restart index to write over parsed_name from the beginning
        if (provided_path[pp_index] == '/')
        {
            pp_index++;
            index = 0;
        }

        parsed_name[index++] = provided_path[pp_index];
    }

    //we write over parsed_name every '/', each write over varies in size so its important to mark the end.
    parsed_name[index] = '\0';

    free(provided_path);

    return parsed_name;
}


//take the path provided in the command line and strip it down into usuable chunks
struct Argument *strip(char *argument)
{
    struct Argument *parsed_argument = malloc(sizeof(struct Argument));

    parsed_argument->argument = malloc(sizeof(char) * 25);
    strcpy(parsed_argument->argument, argument);

    parsed_argument->parsed_argument = ParseFilePath(argument);
    parsed_argument->IsPath = IsPath(argument);

    return parsed_argument;
};

//return 0 : 1 if full path to a file 
int IsPath(char *argument)
{   
    int index = 0;
    for (; argument[index] != '\0'; index++)
    {
        if (argument[index] == '/')
        {
            return 1;
        }      
    }

    return 0;
}

