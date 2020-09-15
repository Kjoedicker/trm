#include "../header/main.h"

//writes a message to a file
void WriteTo(char *location,  char *message)
{
    FILE *file_p;
    file_p = fopen(location, "w+");

    fputs(message, file_p);

    fclose(file_p);
}

//its more important to know if strcmp is a 1 : 0; as opposed to the distance away from true, if false.
int cmpstr(char *a, char *b)
{
    return (strcmp(a, b) == 0) ? 1 : 0;
}

//given a file, read write the first 100 characters to a buffer, returning the address
char *read_message(char *file_path)
{
    FILE *fp;
    char *buff = malloc(sizeof(char) * 100);

    fp = fopen(file_path, "r");
    
    fgets(buff, 100, (FILE*)fp);

    fclose(fp);
    return buff;
}


//multiple paths need to be made extensible, head + / + tail
char *concat(size_t allocation_size, 
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

//strip the first char from the string, and see if it matches  
int ParseFilecmp(char *argv[], char match)
{
    char ParseFileped = argv[1][0];

    return (ParseFileped == match);
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




