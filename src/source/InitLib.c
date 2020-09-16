#include "../header/main.h"
 
struct 
Logistics *InitLogistics()
{
    struct Logistics *core_logistics = malloc(sizeof(struct Logistics));
    
    char *trash_folder_pwd  = getenv("TRASH_FOLDER");
    strcpy(core_logistics->trash_folder_pwd, trash_folder_pwd);

    //make a reference to the trace folder
    sprintf(core_logistics->trace_file_loc, "%s%s", core_logistics->trash_folder_pwd, "./trace");

    core_logistics->trash_folder_status = (access(core_logistics->trash_folder_pwd, F_OK) == 0)                              
                                ? EXIST
                                : IS_NULL;

    core_logistics->trace_folder_status = (access(core_logistics->trace_file_loc, F_OK) == 0) 
                                ? EXIST
                                : IS_NULL;

    InitTrashFolders(core_logistics);
    
    return core_logistics;
}

void 
InitTrashFolders(struct Logistics *core_logistics) 
{

    if (!core_logistics->trash_folder_status &&
        !core_logistics->trace_folder_status) { 
    
        if (!core_logistics->trash_folder_status) {
            InitFolder(core_logistics->trash_folder_pwd);
        }

        if (!core_logistics->trace_folder_status) {
            InitFolder(core_logistics->trace_file_loc);
        }

    } else {
        return;
    }

}

void 
InitFolder(char *folder) 
{
    int file_exists;
    if ((file_exists = mkdir(folder, 0755)) == 0) {
        printf("%s - Created\n", folder);
    } else {
        printf("Error upon creation\n");
    }
}


