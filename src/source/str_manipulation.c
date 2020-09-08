#include "../header/main.h"

//its more important to know if strcmp is a 1 : 0; as opposed to the distance away from true, if false.
int cmpstr(char *a, char *b)
{
    return (strcmp(a, b) == 0) ? 1 : 0;
}

//multiple paths need to be made extensible, head + / + tail
char *concat(size_t allocation_size, char *head_pwd, const char *separator, char *tail_pwd, int head_direction)
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



