#include "../header/main.h"

void DeleteFile(struct Logistics *core_logistics, char *target_file)
{
    char *pwd_path = getenv("PWD");

    //concat for pwd, inorder  to find target_file currently 
    size_t size_of_pwd = ( (strlen(pwd_path) + strlen(target_file) ) + 1);
    char *target_file_location = cat_path(size_of_pwd,
                                             pwd_path,
                                             target_file, 
                                             KEEP_HEAD);

    
    if ((access(target_file_location, F_OK)) == 0)
    {
        //concat for pwd, inorder to delete target_file later
        size_t size_of_del_loc = ( strlen(core_logistics->trash_pwd) + (strlen(target_file) * 2) + 1);
        char *delete_location_subfolder = cat_path(size_of_del_loc,
                                            core_logistics->trash_pwd,
                                            target_file,
                                            KEEP_HEAD);

        //concat for pwd, inorder to store trace file with target_file
        char *extension = "_trace.rtf\0";

        size_t size_of_trace_loc = ( strlen(delete_location_subfolder) + strlen(target_file) + strlen(extension) + 2);
        char *trace_file_location = cat_path(size_of_trace_loc,
                                                delete_location_subfolder,
                                                target_file,
                                                KEEP_HEAD);

            strcat(trace_file_location, extension);

        //a directory is needed to store the target_file and the TraceFile containing the original pwd
        int file_exists;
        if (!((access(delete_location_subfolder, F_OK)) == 0))
        {
            file_exists = mkdir(delete_location_subfolder, 0755);  

            if (file_exists == 0)
            {
                InitTraceFile(trace_file_location, target_file_location);
            }

            else 
            {
                printf("Error, cannot create - %s", delete_location_subfolder);
            }  
        }

        //full pwd to where target_file will go on deletion
        char *delete_location = cat_path(size_of_del_loc,
                                delete_location_subfolder,
                                target_file,
                                KEEP_HEAD);
        

        //sponge
        // printf("%s\n", delete_location_subfolder);  
        // printf("%s\n%s", target_file_location, delete_location);

        //aka: move target_file_location -> delete_location_file
        rename(target_file_location, delete_location);

        free(target_file_location);
        free(delete_location);
        free(delete_location_subfolder);
        free(trace_file_location);
    }

    else
    {
        fprintf(stderr, "%s - non existant", target_file_location);
    }
}


