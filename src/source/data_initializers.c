#include "../header/main.h"
 
//writes a message to a file
//in ~/.trash/deleted_file => creates a file containing pre deletion pwd for restoration
void InitTraceFile(char *location,  char *message)
{
    printf("%s\n", location);
    FILE *file_p;
    file_p = fopen(location, "w+");

    fputs(message, file_p);

    fclose(file_p);
}

//init a Logistics struct member containing a path to the trash folder, aswell as a indicator to if it currently exists 
struct Logistics *InitLogistics()
{
    struct Logistics *core_logistics = malloc(sizeof(struct Logistics));
    
    //trash is a constant, but the HOME env changes so we need to grab that pwd and concat it for later reference
    char *home_path  = getenv("HOME"),
         *trash_path = "/.trash";

    strcpy(core_logistics->trash_pwd, home_path);
    strcat(core_logistics->trash_pwd, trash_path);

    //determines if we will attempt to create a trash folder
    core_logistics->status = (access(core_logistics->trash_pwd, F_OK) == 0) 
                                ? TRASH_EXIST
                                : TRASH_NULL;

    //incase trash folder doesn't exist
    InitTrashFolder(core_logistics);

    return core_logistics;
}

//create the trash folder if non existent
void InitTrashFolder(struct Logistics *core_logistics)
{
    //if the trash folder exists nothing needs to be done
    if (core_logistics->status) { return; }

    int file_exists;
    if ((file_exists = mkdir(core_logistics->trash_pwd, 0755)) == 0)
    {
        printf("%s - Created\n", core_logistics->trash_pwd);
    }

    else 
    {
        printf("Error upon creation\n");
    }
}


