#include "../header/main.h"

struct Argument*
parsefile(char *file_path)
{
    struct Argument *current_file = malloc(sizeof(struct Argument));

    current_file->file_path = malloc(sizeof(char) * 50);
    strcpy(current_file->file_path, file_path);

    if (checkifpath(current_file->file_path))
    {
        current_file->parsed_file_path = parsefilepath(file_path);
    } else {
        current_file->parsed_file_path = malloc(sizeof(char) * 50);
        strcpy(current_file->parsed_file_path, current_file->file_path);

        current_file->file_path = parsefilepwd(current_file);
    }

    current_file->logistics = initlogistics();

    current_file->destination_pwd = extendpath(
                                            50, 
                                            current_file->logistics->trash_folder_pwd, 
                                            "/", current_file->parsed_file_path, 
                                            KEEP_HEAD);

    return current_file;
};

void 
freearguments(struct Argument *target)
{
    free(target->logistics);
    free(target->destination_pwd);
    free(target->parsed_file_path);
    free(target->file_path);
    free(target);
}

void
parsequeuedfiles(void (*Execute) (struct Argument *target_file), 
                     char *target_files[], 
                     int min_index, 
                     int max_index)
{
    //when a file is striped it should contain all the variables neccessary to interact with the various functions of manipulation
    struct Argument *parsed_file = parsefile(target_files[max_index]);
    
    //taking into consideration instances where a flag was/wasn't specified
    if ((max_index - 1) == min_index) {
        Execute(parsed_file);
        freearguments(parsed_file);
    } else {
        Execute(parsed_file);
        parsequeuedfiles(Execute, target_files, min_index, max_index-1);
        freearguments(parsed_file);
    }
}

char*
parsefilepath(char *file_path)
{   
    char *provided_path = malloc(sizeof(char) * 25);
    strcpy(provided_path, file_path);

    char *parsed_name = malloc(sizeof(char) * 50);
    int index = 0;

    for (int pp_index = 0; provided_path[pp_index] != '\0'; pp_index++) {
        //skip this and restart index to write over parsed_name from the beginning
        if (provided_path[pp_index] == '/') {
            pp_index++;
            index = 0;
        }
        parsed_name[index++] = provided_path[pp_index];
    }
    parsed_name[index] = '\0';
    free(provided_path);

    return parsed_name;
}

char*
parsefilepwd(struct Argument *file)
{
    char file_path[50];
    strcpy(file_path, file->file_path);
    free(file->file_path);
    
    char *pwd_path = getenv("PWD");

    char *full_PWD;

    size_t size_of_pwd = ((strlen(pwd_path) + strlen(file_path)) + 1);
    
    full_PWD = extendpath(
                size_of_pwd,
                pwd_path,
                SEPARATOR,
                file_path, 
                KEEP_HEAD);

    return full_PWD;
}