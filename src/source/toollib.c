#include "../header/main.h"

void 
writetofile(char *location,  char *message)
{
    FILE *file_p;
    file_p = fopen(location, "w+");

    fputs(message, file_p);

    fclose(file_p);
}

int pathexists(char *path)
{
    return (access(path, F_OK) == 0);
}

int 
cmpstrings(char *a, char *b)
{
    return (strcmp(a, b) == 0) ? 1 : 0;
}

char 
*readfile(char *file_path)
{
    FILE *fp;

    int readsize = strlen(file_path) + 100;
    char *buff = malloc(sizeof(char) * readsize);

    fp = fopen(file_path, "r");
    
    fgets(buff, readsize, (FILE*)fp);

    fclose(fp);
    return buff;
}

void
reextend(struct Argument *target_file)
{
    char *extension = "_re\0";

    size_t resize = strlen(target_file->destination_pwd) + strlen(extension);
    target_file->destination_pwd = extendpath(
        resize,
        target_file->destination_pwd,
        "",
        extension,
        FREE_HEAD
    );

    resize = strlen(target_file->trace_file_loc) + strlen(extension);
    target_file->trace_file_loc = extendpath(
        resize,
        target_file->trace_file_loc,
        "",
        extension,
        FREE_HEAD
    );

    //(#18) should the restore path reflect the filename change persistant in duplicate files?
    // resize = strlen(target_file->file_path) + strlen(extension);
    // target_file->file_path = extendpath(
    //     resize,
    //     target_file->file_path,
    //     "",
    //     extension,
    //     FREE_HEAD
    // );
}

char*
extendpath(
    size_t allocation_size, 
    char *head_pwd, 
    char *separator, 
    char *tail_pwd, 
    int head_direction)
{
    char *destination = malloc(sizeof (char) * (allocation_size + 2));

    sprintf(destination, "%s%s%s", head_pwd, separator, tail_pwd);

    if (head_direction == FREE_HEAD) { free(head_pwd); }

    return destination;
}

int 
checkifpath(char *file_path)
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

void 
createfolder(char *folder) 
{
    int file_exists;
    if ((file_exists = mkdir(folder, 0755)) == 0) {
        printf("%s - Created\n", folder);
    } else {
        printf("Error upon creation\n");
    }
}