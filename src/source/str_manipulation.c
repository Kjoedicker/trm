#include "../header/main.h"

//its more important to know if strcmp is a 1 : 0; as opposed to the distance away from true, if false.
int cmpstr(char *a, char *b)
{
    return (strcmp(a, b) == 0) ? 1 : 0;
}

//multiple paths need to be made extensible, head + / + tail
char *concat(size_t allocation_size, char *head_pwd, char *separator, char *tail_pwd, int head_direction)
{
    char *destination = malloc(sizeof (char) * (allocation_size + 2));
    
    strcpy(destination, head_pwd);
    strcat(destination, separator);
    strcat(destination, tail_pwd);

    if (head_direction == FREE_HEAD) { free(head_pwd); }

    return destination;
}

//strip the first char from the string, and see if it matches  
int stripcmp(char *argv[], char match)
{
    char stripped = argv[1][0];

    return (stripped == match);
}

//parse a given file path for the appeneded file/directory name 
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



