#include "../header/main.h"




int ParseQueuedFiles(char *target_folder, char *target_files[], int total)
{
    struct Argument *parsed_file = strip(target_files[total]);

    if ((total - 1) == 0)
    {
        printf("%s\n", parsed_file->parsed_file_path);
        // DeleteFile(target_folder, target_files[total]);
        
        free_Argument(parsed_file);
        return 0;
    }

    // DeleteFile(target_folder, target_files[total]);

    printf("%s\n", parsed_file->parsed_file_path);
    ParseQueuedFiles(target_folder, target_files, total-1);

    free_Argument(parsed_file);
    return 0;
}

//given a path, return the destination
char *ParseFilePath(char *file_path)
{   
    //copy over so we can work with a terminated string
    char *provided_path = malloc(sizeof(char) * 25);
    strcpy(provided_path, file_path);

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
struct Argument *strip(char *file_path)
{
    struct Argument *current_file = malloc(sizeof(struct Argument));

    current_file->file_path = malloc(sizeof(char) * 25);
    strcpy(current_file->file_path, file_path);
    
    if (IsPath(file_path))
    {
        //need a stripped down version to get the filename
        current_file->parsed_file_path = ParseFilePath(file_path);
    }

    else 
    {
        //a stripped down path was already provided
        strcpy(current_file->parsed_file_path, file_path);

        //however a full path needs to be created
        current_file->file_path = GetFilePWD(current_file);
    }

    return current_file;
};


void free_Argument(struct Argument *target)
{
    free(target->parsed_file_path);
    free(target->file_path);
    free(target);
}

//return 0 : 1 if full path to a file 
int IsPath(char *file_path)
{   
    int index = 0;
    for (; file_path[index] != '\0'; index++)
    {
        if (file_path[index] == '/')
        {
            return 1;
        }      
    }

    return 0;
}

//based on the current director and the filename, return a full file path to the file
char *GetFilePWD(struct Argument *file)
{
    char *pwd_path = getenv("PWD");

    char *full_PWD;

    //we need to access the execution path to properly handle the file
    
    size_t size_of_pwd = ( (strlen(pwd_path) + strlen(file->file_path) ) + 1);
    full_PWD = concat(size_of_pwd,
                                    pwd_path,
                                    SEPARATOR,
                                    file->file_path, 
                                    KEEP_HEAD);

    return full_PWD;
}

