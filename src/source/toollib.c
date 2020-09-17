#include "../header/main.h"

void 
writetofile(char *location,  char *message)
{
    FILE *file_p;
    file_p = fopen(location, "w+");

    fputs(message, file_p);

    fclose(file_p);
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

    int readsize = 100;
    char *buff = malloc(sizeof(char) * readsize);

    fp = fopen(file_path, "r");
    
    fgets(buff, 100, (FILE*)fp);

    fclose(fp);
    return buff;
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