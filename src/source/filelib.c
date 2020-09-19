#include "../header/main.h"

void 
deletefile(struct Argument *target_file)
{   
    int duplicateintrash = pathexists(target_file->destination_pwd);
    int filepathstatus   = pathexists(target_file->file_path);

    if ( !duplicateintrash && filepathstatus)
    {
        rename(target_file->file_path, target_file->destination_pwd);
        writetofile(target_file->trace_file_loc, target_file->file_path);
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

void //(#17) has a limit of 90 files displayed in a directory
listdir(struct Logistics *core_logistics, int size_details) 
{ 
    char target_folder[strlen(core_logistics->trash_folder_pwd) + 1];
    strcpy(target_folder, core_logistics->trash_folder_pwd);

    struct stat file_stat;

    struct dirent *directory_entry;  

    DIR *directory_stream = opendir(target_folder);
    
    if (directory_stream)
    {
        //access the next dirent in the directory_stream, filtering out '.' ".." path directives
        while (((directory_entry = readdir(directory_stream)) != NULL) &&
                (!(cmpstrings(directory_entry->d_name, "."))) &&
                (!(cmpstrings(directory_entry->d_name, ".."))))
        {     

            size_t filename_size = (strlen(target_folder) + strlen(directory_entry->d_name)) + 2;
            char *file_path = extendpath(
                                    filename_size,
                                    target_folder,            
                                    SEPARATOR,
                                    directory_entry->d_name,
                                    KEEP_HEAD);

            if (access(file_path, F_OK) + 1) {
                switch (size_details) {
                    case VERBOSE:
                        stat(file_path, &file_stat);                                        
                        printf("%-25s %6u bytes\n", directory_entry->d_name, (unsigned int)file_stat.st_size);
                        break;
                    
                    case CONCISE:
                        printf("%s\n", directory_entry->d_name);
                        break;
                }

                free(file_path);
            }
        }
        closedir(directory_stream);   
    } else {
        fprintf(stderr, "%s", strerror(errno));
    }

    free(core_logistics);  
}
         
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

    size_t sizeof_trace_path = (strlen(target_file->logistics->trace_file_loc) + strlen(target_file->parsed_file_path) + 2);
    char *trace_file_path = extendpath(
        sizeof_trace_path,
        target_file->logistics->trace_file_loc,
        "/.",
        target_file->parsed_file_path,
        KEEP_HEAD
    );

    //(#16) handle manual restore path input
    // char *restore_path = (restore_path == NULL) ? readfile(trace_file_path) : restore_path;
    char *restore_path = readfile(trace_file_path);
    printf("restore_path = %s\n", restore_path); 

    if (access(trace_file_path, F_OK) == 0) {
        rename(file_loc, restore_path);
    }

    free(restore_path);
    free(file_loc);
    free(trace_file_path); 
}