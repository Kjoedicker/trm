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

    free(target_file->trash_info);
}

void
listdir(struct Logistics *core_logistics, int size_details) 
{ 
    char target_folder[strlen(core_logistics->trash_folder) + 1];
    strcpy(target_folder, core_logistics->trash_folder);

    struct dirent *directory_entry;
    struct stat file_stat;

    DIR *dp;
    dp = opendir (target_folder);

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

void 
restorefile(struct Argument *target_file)
{   
    size_t sizeof_trash_path = (strlen(target_file->logistics->trash_folder) + strlen(target_file->parsed_origin) + 2);
    char *file_loc = extendpath(
        sizeof_trash_path,
        target_file->logistics->trash_folder,
        "/",
        target_file->parsed_origin,
        KEEP_HEAD
    );

    if (access(file_loc, F_OK) == 0) {

        size_t sizeof_trace_path = (strlen(target_file->logistics->trash_info) + strlen(target_file->parsed_origin) + 2);
        char *trace_origin = extendpath(
            sizeof_trace_path,
            target_file->logistics->trash_info,
            "/",
            target_file->parsed_origin,
            KEEP_HEAD
        );

        if (target_file->restore_path == NULL)
        {
            char *restore_path = readfile(trace_origin);
            rename(file_loc, restore_path);

            if (access(trace_origin, F_OK) == 0) {
                rename(file_loc, restore_path);
            }

            free(restore_path);
        } else {
            if (!access(target_file->restore_path, F_OK)){
                sprintf(target_file->restore_path, "%s%s%s", target_file->restore_path, "/", target_file->parsed_origin);
                rename(file_loc, target_file->restore_path);
            }            
        }

        free(file_loc);
        free(trace_origin); 
    } else {
        printf("file not found\n");
    }
}
