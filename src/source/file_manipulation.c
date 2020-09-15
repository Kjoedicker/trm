#include "../header/main.h"

void DeleteFile(struct Argument *target_file)
{   

    //only files that being deleted should need to worrry about having a trace_file_loc
    char *separator = "/.\0";
    size_t trace_file_loc_size = (strlen(target_file->logistics->trace_file_loc) + 
                                    strlen(separator) + 
                                    strlen(target_file->parsed_file_path));

    target_file->trace_file_loc = concat(trace_file_loc_size, target_file->logistics->trace_file_loc, separator, target_file->parsed_file_path, KEEP_HEAD);

    printf("%s", target_file->trace_file_loc);

    //the file needs to exist, and the destination needs to not already exist, until we make that feature.
    if (!(access(target_file->destination_pwd, F_OK) == 0) ||
         (access(target_file->file_path, F_OK))      == 0)
    {
        rename(target_file->file_path, target_file->destination_pwd);
        InitTraceFile(target_file->trace_file_loc, target_file->file_path);
    }

    else {
        //(#3) what if multiple files with the same name exist?
        printf("file cannot be deleted\n");
    }

    free(target_file->trace_file_loc);
}

void ListDir(struct Logistics *core_logistics, int size_details) 
{ 

    char target_folder[strlen(core_logistics->trash_pwd) + 1];
    strcpy(target_folder, core_logistics->trash_pwd);

    struct stat file_stat;

    //readdir() will access directory_stream returning a pointer to a entry to be accessed
    struct dirent *directory_entry;  

    //opendir returns a stream of files in the directory
    DIR *directory_stream = opendir(target_folder);
    
    if (directory_stream)
    {
        //access the next dirent in the directory_stream, filtering out '.' ".." path directives
        while (((directory_entry = readdir(directory_stream)) != NULL) &&
                (!(cmpstr(directory_entry->d_name, "."))) &&
                (!(cmpstr(directory_entry->d_name, ".."))) )
        {      
            // //because files in .trash are nested we need to append for that depth for the full pwd     
            size_t filename_size = (strlen(target_folder) + strlen(directory_entry->d_name)) + 2;
            char *file_path = concat(filename_size,
                                     target_folder,            
                                     SEPARATOR,
                                     directory_entry->d_name,
                                     KEEP_HEAD);

            
            if (access(file_path, F_OK) + 1)
            {
                switch (size_details)
                {
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
    }

    else 
    {
        fprintf(stderr, "%s", strerror(errno));
    }

    free(core_logistics);  
}

char *read_message(char *file_path)
{
    FILE *fp;
    char *buff = malloc(sizeof(char) * 100);

    fp = fopen(file_path, "r");
    
    fgets(buff, 100, (FILE*)fp);

    fclose(fp);
    return buff;
}

         
//(#9) what if we want to restore multiple files?
//(#6) what if restore_path wants to just target a directory without having to specify the name of the file when it goes there. /home/usr/file_name vs /home/usr
void RestoreFile(struct Argument *target_file)
{   
    // (#7) implement GetSize function for these size specifiers
    size_t sizeof_trash_path = (strlen(target_file->logistics->trash_pwd) + strlen(target_file->parsed_file_path) + 2);
    char *file_loc = concat(sizeof_trash_path,
                            target_file->logistics->trash_pwd,
                            "/",
                            target_file->parsed_file_path,
                            KEEP_HEAD);


    size_t sizeof_trace_path = (strlen(target_file->logistics->trace_file_loc) + strlen(target_file->parsed_file_path) + 2);
    char *trace_file_path = concat(sizeof_trace_path,
                                   target_file->logistics->trace_file_loc,
                                   "/.",
                                   target_file->parsed_file_path,
                                   KEEP_HEAD);

    // char *restore_path = (restore_path == NULL) ? read_message(trace_file_path) : restore_path;
    char *restore_path = read_message(trace_file_path);
    printf("restore_path = %s\n", restore_path); 

    if (access(trace_file_path, F_OK) == 0)
    {
        rename(file_loc, restore_path);
    }

    free(restore_path);
    free(file_loc);
    free(trace_file_path); 
}


