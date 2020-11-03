#include "../header/main.h"

void 
deletefile(struct Argument *target_file)
{   
    int duplicateintrash = pathexists(target_file->destination);
    int filepathstatus   = pathexists(target_file->origin);

    if ( !duplicateintrash && filepathstatus)
    {
        rename(target_file->origin, target_file->destination);
        writetofile(target_file);
    } else {
        switch (filepathstatus)
        {
            case 0:
                printf("error - target file path does not exist");
                break;
            case 1:
                if (duplicateintrash) {

                    reextend(target_file);
                    deletefile(target_file);
                    return;
                }

                printf("file cannot be deleted\n");
                break;
        }
    }
}

void
listdir(struct Logistics *core_logistics, int size_details) 
{ 
    char *subfolder = "Trash/files\0";
    char target_folder[strlen(core_logistics->trash_folder) + strlen(subfolder)];
    sprintf(target_folder, "%s/%s", core_logistics->trash_folder, subfolder);

    struct dirent *directory_entry;
    struct stat file_stat;

    DIR *dp;
    dp = opendir (target_folder);

    // TODO(#28): currently shows files, enable folders to be shown as well
    if (dp != NULL)
    {
        while ((directory_entry = readdir(dp))) { 
            size_t filename_size = (strlen(target_folder) + strlen(directory_entry->d_name)) + 2;
            char *origin = extendpath(
                                    filename_size,
                                    target_folder,            
                                    SEPARATOR,
                                    directory_entry->d_name,
                                    KEEP_HEAD);

            stat(origin, &file_stat);
            
            // TODO(#22): Integrate dynamic formatting similar to gnu lib ls command
            if (size_details)
            {
                printf("%-8li %-25s\n", file_stat.st_size, directory_entry->d_name);
            } else {
                printf("%-15s", directory_entry->d_name);
            }    
        }
        printf("\n");
        closedir(dp);
    }
    else
        perror ("Couldn't open the directory");

    free(core_logistics);
}

// TODO(#24): .trashinfo should be deleted upon restoration
void 
restorefile(struct Argument *target_file)
{   
    struct restlogistics *logistics = initrestlogistics(target_file);

    if (access(logistics->file_loc, F_OK) == 0) {

        if (target_file->restore_path == NULL)
        {
            if (access(logistics->origin_pwd, F_OK) == 0) {
                char *restore_path = parseinfofile(logistics->origin_pwd);
                rename(logistics->file_loc, restore_path);
                free(restore_path);
            }
        } else {
            if (!access(target_file->restore_path, F_OK)){
                sprintf(target_file->restore_path, "%s%s%s", target_file->restore_path, "/", target_file->parsed_origin);
                rename(logistics->file_loc, target_file->restore_path);
            }            
        }
    } else {
        printf("file not found\n");
    }
    free(logistics->file_loc);
    free(logistics->origin_pwd); 
    free(logistics);
}
