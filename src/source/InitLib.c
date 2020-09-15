#include "../header/main.h"
 

//init a Logistics struct member containing a path to the trash folder, aswell as a indicator to if it currently exists 
struct Logistics *InitLogistics()
{
    struct Logistics *core_logistics = malloc(sizeof(struct Logistics));
    
    //trash is a constant, but the HOME env changes so we need to grab that pwd and concat it for later reference
    //set TRASH_FOLDER as alias in bashrc 
    char *home_path  = getenv("TRASH_FOLDER");
    strcpy(core_logistics->trash_pwd, home_path);

    //make a reference to the trace folder
    strcpy(core_logistics->trace_file_loc, core_logistics->trash_pwd);
    strcat(core_logistics->trace_file_loc, "/.trace");

    //determines if we will attempt to create a trash folder
    core_logistics->trash_status = (access(core_logistics->trash_pwd, F_OK) == 0)                              
                                ? EXIST
                                : IS_NULL;

    //determines if we will attempt to create a .trace folder
    core_logistics->trace_status = (access(core_logistics->trace_file_loc, F_OK) == 0) 
                                ? EXIST
                                : IS_NULL;

    //incase trash folder doesn't exist
    InitTrashFolders(core_logistics);
    
    return core_logistics;
}

//chech if .trash or .trace needs to be created
void InitTrashFolders(struct Logistics *core_logistics)
{
    //if the trash folder exists nothing needs to be done
    if (core_logistics->trash_status &&
        core_logistics->trace_status) { 
            return; 
    }

    //if there isn't a .trash folder create one
    if (!core_logistics->trash_status) {
        InitFolder(core_logistics->trash_pwd);
    }

    //if there isn't a .trash/.trace folder create one
    if (!core_logistics->trace_status) {
        InitFolder(core_logistics->trace_file_loc);
    }

}

//create a folder
void InitFolder(char *folder)
{
    int file_exists;
    if ((file_exists = mkdir(folder, 0755)) == 0) {
        printf("%s - Created\n", folder);
    }

    else {
        printf("Error upon creation\n");
    }
}


