#include "../header/main.h"

void 
writetofile(struct Argument *file)
{
    FILE *file_p;
    file_p = fopen(file->trash_info, "w+");

    fprintf(file_p, "%s\n%s%s\n%s",
        "[Trash Info]",
        "Path=", file->origin,
        file->date_modified
    );

    fclose(file_p);
}

char *getdate() {
    char *date = malloc(sizeof(char) * 50);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "DeletionDate=%d-%02d-%02d%02d:%02d:%02d", 
            tm.tm_year + 1900, 
            tm.tm_mon + 1, 
            tm.tm_mday, 
            tm.tm_hour, 
            tm.tm_min, 
            tm.tm_sec);

    return date;
}

int 
pathexists(char *path)
{
    return (access(path, F_OK) == 0);
}

int 
cmpstrings(char *a, char *b)
{
    return (strcmp(a, b) == 0) ? 1 : 0;
}

char 
*readfile(char *origin)
{
    FILE *fp;

    int readsize = strlen(origin) + 100;
    char *buff = malloc(sizeof(char) * readsize);

    fp = fopen(origin, "r");
    
    fgets(buff, readsize, (FILE*)fp);

    fclose(fp);
    return buff;
}

void
reextend(struct Argument *target_file)
{
    char *extension = "_re\0";

    size_t resize = strlen(target_file->destination) + strlen(extension);
    target_file->destination = extendpath(
        resize,
        target_file->destination,
        "",
        extension,
        FREE_HEAD
    );

    resize = strlen(target_file->trash_info) + strlen(extension);
    target_file->trash_info = extendpath(
        resize,
        target_file->trash_info,
        "",
        extension,
        FREE_HEAD
    );

    if (target_file->restore_path == NULL) {
        target_file->restore_path = malloc(sizeof(char) * strlen(target_file->origin) + 2);
        strcpy(target_file->restore_path, target_file->origin);
    }

    resize = strlen(target_file->restore_path) + strlen(extension);
    target_file->restore_path = extendpath(
        resize,
        target_file->restore_path,
        "",
        extension,
        FREE_HEAD
    );
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
checkifpath(char *origin)
{   
    int index = 0;
    for (; origin[index] != '\0'; index++)
    {
        if (origin[index] == '/')
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
    printf("\n%s\n", folder);
    if ((file_exists = mkdir(folder, 0755)) == 0) {
        printf("%s - Created\n", folder);
    } else {
        printf("Error upon creation\n");
    }
}

int checktext(char *text) {
    //strcmp returns 0 if it is a match, so we need to check for 0
    if (!strcmp(text, "")) {
      return INVALID;
    } else {
      return VALID;
    }
}