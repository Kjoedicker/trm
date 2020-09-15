#include "../header/main.h"

//given the command line arguments, recursively execute actions on each argument
int ParseQueuedFiles(void (*Execute) (struct Argument *target_file), 
                     char *target_files[], 
                     int min_index, 
                     int max_index)
{
  
    //when a file is striped it should contain all the variables neccisssary to interact with the various functions of manipulation
    struct Argument *parsed_file = strip(target_files[max_index]);
    
    //taking into consideration instances where a flag was/wasn't specified
    if ((max_index - 1) == min_index)
    {
        Execute(parsed_file);
        free_Argument(parsed_file);

        return 0;
    }

    else 
    {
        Execute(parsed_file);
        ParseQueuedFiles(Execute, target_files, min_index, max_index-1);
        free_Argument(parsed_file);
    }

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

    current_file->file_path = malloc(sizeof(char) * 50);
    strcpy(current_file->file_path, file_path);


    if (IsPath(current_file->file_path))
    {
        //need a stripped down version to get the filename
        current_file->parsed_file_path = ParseFilePath(file_path);
    }

    else 
    {
        current_file->parsed_file_path = malloc(sizeof(char) * 50);

        //a stripped down path was already provided
        strcpy(current_file->parsed_file_path, current_file->file_path);

        //however a full path needs to be created
        current_file->file_path = GetFilePWD(current_file);
    }

    current_file->logistics = InitLogistics();

    current_file->destination_pwd = concat(50, current_file->logistics->trash_pwd, "/", current_file->parsed_file_path, KEEP_HEAD);

    return current_file;
};


void free_Argument(struct Argument *target)
{
    free(target->logistics);
    free(target->destination_pwd);
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
    char file_path[50];
    strcpy(file_path, file->file_path);
    free(file->file_path);
    
    char *pwd_path = getenv("PWD");

    char *full_PWD;

    //we need to access the execution path to properly handle the file
    size_t size_of_pwd = ( (strlen(pwd_path) + strlen(file_path) ) + 1);
    
    full_PWD = concat(size_of_pwd,
                        pwd_path,
                        SEPARATOR,
                        file_path, 
                        KEEP_HEAD);

    return full_PWD;
}

