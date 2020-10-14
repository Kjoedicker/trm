#include "../header/main.h"
 
struct Logistics*
initlogistics()
{
    struct Logistics *core_logistics = malloc(sizeof(struct Logistics));
    
    char *trash_folder  = getenv("TRASH_FOLDER");

    strcpy(core_logistics->trash_folder, trash_folder);

    sprintf(core_logistics->trash_files, "%s%s", trash_folder, "/files");
    sprintf(core_logistics->trash_info, "%s%s", trash_folder, "/info");

    // printf("%s\n%s", core_logistics->trash_files, core_logistics->trash_info);
    
    core_logistics->trash_folder_status = (access(core_logistics->trash_folder, F_OK) == 0)                              
                                ? EXIST
                                : IS_NULL;

    core_logistics->files_folder_status = (access(core_logistics->trash_files, F_OK) == 0) 
                            ? EXIST
                            : IS_NULL;

    core_logistics->info_folder_status = (access(core_logistics->trash_info, F_OK) == 0) 
                                ? EXIST
                                : IS_NULL;

    inittrashfolders(core_logistics);
    
    return core_logistics;
}

void 
inittrashfolders(struct Logistics *core_logistics) 
{
    if (!core_logistics->trash_folder_status &&
        !core_logistics->files_folder_status &&
        !core_logistics->info_folder_status) { 
    
        if (!core_logistics->trash_folder_status) {
            createfolder(core_logistics->trash_folder);
        }

        if (!core_logistics->files_folder_status) {
            createfolder(core_logistics->trash_files);
        }

        if (!core_logistics->info_folder_status) {
            createfolder(core_logistics->trash_info);
        }

    } else {
        return;
    }
}