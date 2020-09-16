#include "../header/main.h"
 
struct Logistics*
initlogistics()
{
    struct Logistics *core_logistics = malloc(sizeof(struct Logistics));
    
    char *trash_folder_pwd  = getenv("TRASH_FOLDER");
    strcpy(core_logistics->trash_folder_pwd, trash_folder_pwd);

    sprintf(core_logistics->trace_file_loc, "%s%s", core_logistics->trash_folder_pwd, "/.trace");

    core_logistics->trash_folder_status = (access(core_logistics->trash_folder_pwd, F_OK) == 0)                              
                                ? EXIST
                                : IS_NULL;

    core_logistics->trace_folder_status = (access(core_logistics->trace_file_loc, F_OK) == 0) 
                                ? EXIST
                                : IS_NULL;

    inittrashfolders(core_logistics);
    
    return core_logistics;
}

void 
inittrashfolders(struct Logistics *core_logistics) 
{
    if (!core_logistics->trash_folder_status &&
        !core_logistics->trace_folder_status) { 
    
        if (!core_logistics->trash_folder_status) {
            createfolder(core_logistics->trash_folder_pwd);
        }

        if (!core_logistics->trace_folder_status) {
            createfolder(core_logistics->trace_file_loc);
        }

    } else {
        return;
    }
}