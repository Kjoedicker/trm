#include "../header/main.h"

struct Argument*
parsefile(char *origin)
{
    struct Argument *current_file = malloc(sizeof(struct Argument));

    current_file->restore_path = NULL;

    current_file->date_modified = getdate();

    current_file->origin = malloc(sizeof(char) * 50);
    strcpy(current_file->origin, origin);
    
    if (checkifpath(current_file->origin))
    {
        current_file->parsed_origin = parsefilepath(origin);
    } else {
        current_file->parsed_origin = malloc(sizeof(char) * 50);
        strcpy(current_file->parsed_origin, current_file->origin);

        current_file->origin = parsefilepwd(current_file);
    }

    current_file->logistics = initlogistics();

    current_file->destination = extendpath(
        50, 
        current_file->logistics->trash_folder, 
        "/files/", current_file->parsed_origin, 
        KEEP_HEAD
    );

    char *separator = "/\0";
    size_t trash_info_size = (
        strlen(current_file->logistics->trash_info) +                             
        strlen(separator) + 
        strlen(current_file->parsed_origin)
    );

    current_file->trash_info = extendpath(trash_info_size, current_file->logistics->trash_info, separator, current_file->parsed_origin, KEEP_HEAD);

    return current_file;
};

void 
freearguments(struct Argument *target)
{
    free(target->logistics);
    free(target->destination);
    free(target->parsed_origin);
    free(target->restore_path);
    free(target->origin);
    free(target);
}

void 
parserestorefile(char *filename, char *restorepath)
{
    struct Argument *parsed_file = parsefile(filename);
    parsed_file->restore_path = malloc((sizeof(char) * (strlen(restorepath) + strlen(parsed_file->parsed_origin) + 1)));
    strcpy(parsed_file->restore_path, restorepath);

    restorefile(parsed_file);
}

void
parsequeuedfiles(void (*Execute) (struct Argument *target_file), 
                     char *target_files[], 
                     int min_index, 
                     int max_index)
{

    struct Argument *parsed_file = parsefile(target_files[max_index]);
    
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
parsefilepath(char *origin)
{   
    char *provided_path = malloc(sizeof(char) * 25);
    strcpy(provided_path, origin);

    char *parsed_name = malloc(sizeof(char) * 50);
    int index = 0;

    for (int pp_index = 0; provided_path[pp_index] != '\0'; pp_index++) {
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
    char origin[50];
    strcpy(origin, file->origin);
    free(file->origin);
    
    char *pwd_path = getenv("PWD");

    char *full_PWD;

    size_t size_of_pwd = ((strlen(pwd_path) + strlen(origin)) + 1);
    
    full_PWD = extendpath(
        size_of_pwd,
        pwd_path,
        SEPARATOR,
        origin, 
        KEEP_HEAD
    );

    return full_PWD;
}