#include "../header/main.h"

void 
deletefile(struct Argument *target_file)
{   
    if (target_file->restore_path == NULL) {
        target_file->restore_path = malloc(sizeof(char) * strlen(target_file->file_path));
        strcpy(target_file->restore_path, target_file->file_path);
    }

    int duplicateintrash = pathexists(target_file->destination_pwd);
    int filepathstatus   = pathexists(target_file->file_path);
    
    if ( !duplicateintrash && filepathstatus)
    {
        rename(target_file->file_path, target_file->destination_pwd);
        writetofile(target_file->trace_file_loc, target_file->restore_path);
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

    free(target_file->trace_file_loc);
}

void
listdir(struct Logistics *core_logistics, int size_details) 
{ 
    char target_folder[strlen(core_logistics->trash_folder_pwd) + 1];
    strcpy(target_folder, core_logistics->trash_folder_pwd);

    struct dirent *directory_entry;
    struct stat file_stat;

    DIR *dp;
    dp = opendir (target_folder);

    if (dp != NULL)
    {
        while ((directory_entry = readdir(dp))) { 
            size_t filename_size = (strlen(target_folder) + strlen(directory_entry->d_name)) + 2;
            char *file_path = extendpath(
                                    filename_size,
                                    target_folder,            
                                    SEPARATOR,
                                    directory_entry->d_name,
                                    KEEP_HEAD);

            stat(file_path, &file_stat);
            printf("%s -> %li\n", directory_entry->d_name, file_stat.st_size);
        }
        closedir(dp);
    }
    else
        perror ("Couldn't open the directory");

    free(core_logistics);
}
         
// TODO(#15): segfault occurs when restore is acted upon a file that doesn't exist
void 
restorefile(struct Argument *target_file)
{   
    size_t sizeof_trash_path = (strlen(target_file->logistics->trash_folder_pwd) + strlen(target_file->parsed_file_path) + 2);
    char *file_loc = extendpath(
        sizeof_trash_path,
        target_file->logistics->trash_folder_pwd,
        "/",
        target_file->parsed_file_path,
        KEEP_HEAD
    );

    if (access(file_loc, F_OK) == 0) {

        size_t sizeof_trace_path = (strlen(target_file->logistics->trace_file_loc) + strlen(target_file->parsed_file_path) + 2);
        char *trace_file_path = extendpath(
            sizeof_trace_path,
            target_file->logistics->trace_file_loc,
            "/.",
            target_file->parsed_file_path,
            KEEP_HEAD
        );

        if (target_file->restore_path == NULL)
        {
            char *restore_path = readfile(trace_file_path);
            rename(file_loc, restore_path);

            if (access(trace_file_path, F_OK) == 0) {
                rename(file_loc, restore_path);
            }

            free(restore_path);
        } else {
            if (!access(target_file->restore_path, F_OK)){
                sprintf(target_file->restore_path, "%s%s%s", target_file->restore_path, "/", target_file->parsed_file_path);
                rename(file_loc, target_file->restore_path);
            }            
        }

        free(file_loc);
        free(trace_file_path); 
    } else {
        printf("file not found\n");
    }
}
