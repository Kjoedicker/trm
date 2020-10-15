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

struct restlogistics*
initrestlogistics(struct Argument *target_file) {
    struct restlogistics *logistics = malloc(sizeof(struct restlogistics));

    size_t sizeof_trash_path = (strlen(target_file->logistics->trash_files) + strlen(target_file->parsed_origin) + 2);
    
    logistics->file_loc = extendpath(
        sizeof_trash_path,
        target_file->logistics->trash_files,
        "/",
        target_file->parsed_origin,
        KEEP_HEAD
    );

    char ext[] = ".trashinfo";
    size_t sizeof_info_path = (
        strlen(target_file->logistics->trash_info) + 
        strlen(target_file->parsed_origin) + 
        strlen(ext) + 
        2
    );

    logistics->origin_pwd = extendpath(
        sizeof_info_path,
        target_file->logistics->trash_info,
        "/",
        target_file->parsed_origin,
        KEEP_HEAD
    );
    strcat(logistics->origin_pwd, ext);

    return logistics;
}
