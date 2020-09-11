#include "../header/main.h"



void ListDir(char *target_folder, int size_details) 
{ 
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
            //because files in .trash are nested in a self named folder we need to append for that depth for the full pwd     
            size_t filename_size = (strlen(target_folder) + (strlen(directory_entry->d_name) * 2)) + 2;
            char *file_path = concat(filename_size,
                                       concat(filename_size - strlen(directory_entry->d_name), 
                                                target_folder,
                                                SEPARATOR,                                                                                            
                                                directory_entry->d_name,
                                                KEEP_HEAD),
                                       SEPARATOR,
                                       directory_entry->d_name,
                                       FREE_HEAD);
            
            if (access(file_path, F_OK) + 1)
            {
                switch (size_details)
                {
                    case VERBOSE:
                        stat(file_path, &file_stat);

                        printf("%-25s %6u bytes\n", directory_entry->d_name, (unsigned int)file_stat.st_size);
                        break;
                    
                    case CONCISE:
                        printf("%s ", directory_entry->d_name);
                        break;
                }
            }

            free(file_path);   
        }

        closedir(directory_stream);     
    }

    else 
    {
        fprintf(stderr, "%s", strerror(errno));
    }
  
} 

void RestoreFile(struct Logistics *core_logistics, char *target_file, char *restore_path)
{
    //direct flow for restoring to original directory, or current/specified directory.
    


}


