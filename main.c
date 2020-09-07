// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/stat.h>

// #define DATA_SIZE 1000

// #define FILE_PERMISSIONS 0755
// #define TRASH_DIRECTORY "/home/keifer/.trash/"

// /*

// ParseFlags(): DONE

// based on the parameters provided act according to

// -d --DELETE => DeleteFile()

// -r --RESTORE => RestoreFile() => specified location
// -R --ORIGINAL_RESTORE => RestoreFile() => original location

// DeleteFile():

// -d --DELETE

// check if the trash directory exists
//     -create one if not
//     -otherwise continue

// create a new folder within the trashs directory for the file to be deleted
//     -create file containing the current directory of the file

// RestoreFile()

// -o --ORIGINAl flag will restore the file to its origin spot

// otherwise; the file will be restored to the specified spot in the commandline arguments

    
// */


// int cmpstr(char *a, char *b);
// int cmpstr(char *a, char *b);

// void ParseFlags(int argc, char *argv[]);

// void DeleteFile();
// void RestoreFile();


// //does a /.trash file exist
// enum trash_state {TRASH_NULL, TRASH_EXIST};

// struct Logistics {
//     char trash_pwd[100];
//     enum trash_state status;
// };

// struct Logistics *InitLogistics();

// //multiple paths need to be made extensible, head + / + tail
// char * create_path(size_t allocation_size, char *head_pwd, char *tail_pwd)
// {
//     char *destination = malloc(sizeof (char) * (allocation_size + 2));
    
//     strcpy(destination, head_pwd);
//     strcat(destination, "/");
//     strcat(destination, tail_pwd);

//     return destination;
// }

// //writes a message to a file
// //in ~/.trash/deleted_file => creates a file containing pre deletion pwd for restoration
// void StoreTraceFile(char *location,  char *message)
// {
//     printf("%s\n", location);
//     // FILE *file_p;
//     // file_p = fopen(location, "w+");

//     // // fputs(message, file_p);

//     // fclose(file_p);
// }

// void DeleteFile(struct Logistics *core_logistics, char *target_file)
// {
//     char *pwd_path = getenv("PWD");

//     //concat for pwd, inorder  to find target_file currently 
//     size_t size_of_pwd = ( (strlen(pwd_path) + strlen(target_file) ) + 1);
//     char *target_file_location = create_path(size_of_pwd,
//                                              pwd_path,
//                                              target_file);

//     //concat for pwd, inorder to delete target_file later
//     size_t size_of_del_loc = ( strlen(core_logistics->trash_pwd) + (strlen(target_file) * 2) + 1);
//     char *delete_location = create_path(size_of_del_loc,
//                                         core_logistics->trash_pwd,
//                                         target_file);


    

//     //concat for pwd, inorder to store trace file with target_file
//     char *extension = "_trace.rtf\0";

//     size_t size_of_trace_loc = ( strlen(delete_location) + strlen(target_file) + strlen(extension) + 2);
//     char *trace_file_location = create_path(size_of_trace_loc,
//                                             delete_location,
//                                             target_file);

//           strcat(trace_file_location, extension);

//     //a directory is needed to store the target_file and the TraceFile containing the original pwd
//     // if ((access(delete_location, F_OK) == 0))
//     // {
//     //      if (!(mkdir(delete_location, 0755)))
//     //      {
//     //          printf("error - directory doesn't exist, and cannot be created");
//     //      }       
//     // }
    
//      int file_exists = mkdir(delete_location, 0755);
    
//     StoreTraceFile(trace_file_location, target_file_location);

//     //alternative, memory lost upon creation of this
//     delete_location = create_path(size_of_del_loc,
//                                   delete_location,
//                                   target_file);

//     //sponge
//     printf("%s\n", delete_location);  
//     printf("%s\n%s", target_file_location, delete_location);
//     rename(target_file_location, delete_location);

//     free(target_file_location);
//     free(delete_location);
//     free(trace_file_location);
// }



// //init a Logistics struct member containing a path to the trash folder, aswell as a indicator to if it currently exists 
// struct Logistics *InitLogistics()
// {
//     struct Logistics *core_logistics = malloc(sizeof(struct Logistics));
    
//     //trash is a constant, but the HOME env changes so we need to grab that pwd and concat it for later reference
//     char *home_path  = getenv("HOME"),
//          *trash_path = "/.trash";

//     strcpy(core_logistics->trash_pwd, home_path);
//     strcat(core_logistics->trash_pwd, trash_path);
    
//     //determines if we will attempt to create a trash folder
//     core_logistics->status = (access(core_logistics->trash_pwd, F_OK) == 0) 
//                                 ? TRASH_EXIST
//                                 : TRASH_NULL;

//     return core_logistics;
// }

// //create the trash folder if non existent
// void InitTrashFolder(struct Logistics *core_logistics)
// {
//     //if the trash folder exists nothing needs to be done
//     if (core_logistics->status) { return; }

//     int file_exists;
//     if ((file_exists = mkdir(core_logistics->trash_pwd, 0755)) == 0)
//     {
//         printf("%s - Created\n", core_logistics->trash_pwd);
//     }

//     else 
//     {
//         printf("Error upon creation\n");
//     }
// }


// int main(int argc, char *argv[], char **envp)
// {

//     struct Logistics *tmp = InitLogistics();

//     InitTrashFolder(tmp);

//     DeleteFile(tmp, "test1");

//     // char *test[] = {"test1", "test2", "test3", "test4", "test5"};  

//     // for (int i = 0; i < 5; i++)
//     // {
//     //     DeleteFile(tmp, test[i]);
//     //     // printf("%s", test[i]);
//     // }   

//     free(tmp);

//     return 0;
// }

// //its more important to know if strcmp is a 1 : 0; as opposed to the distance away from true, if false.
// int cmpstr(char *a, char *b)
// {
//     return (strcmp(a, b) == 0) ? 1 : 0;
// }

// //flags dictate the next function call on the target file
// void ParseFlags(int argc, char *argv[])
// {
//     //sponge
//     // printf("%s", argv[1]);

//     char *use_flag = argv[1]; 

//     enum program_actions  {RESTORE, ORIGINAL_RESTORE, DELETE};
//     enum action_verbosity {CONCISE, VERBOSE};
    
//     //3 dimensions, two pointers per dimension
//     char *flags[3][2] = {
//         {"-r", "--RESTORE"},
//         {"-R", "--ORIGINAL_RESTORE"},
//         {"-d", "--DELETE"}
//     };


//     //sponge
//     printf("%c", flags[RESTORE][CONCISE][0]);

//     struct Logistics *core_logistics = InitLogistics();

//     if (cmpstr(flags[RESTORE][CONCISE], use_flag) ||
//         cmpstr(flags[RESTORE][VERBOSE], use_flag) ){
//             printf("restore");
//         }
    
//     if (cmpstr(flags[ORIGINAL_RESTORE][CONCISE], use_flag) ||
//         cmpstr(flags[ORIGINAL_RESTORE][VERBOSE], use_flag) ){
//             printf("original_restore");
//         }
        
//     if (cmpstr(flags[DELETE][CONCISE], use_flag) ||
//         cmpstr(flags[DELETE][VERBOSE], use_flag) ){
//             DeleteFile(InitLogistics(), argv[2]);
//             printf("delete");
//         }
    
//     else 
//     {
//         printf("Null use flags specified\n");
//     }   

//     free(core_logistics); 
// }

#include "src/header/main.h"
              
int main(int argc, char *argv[], char **envp)
{
    DirectFlow(argc, argv);
    // char test = argv[1][0];
    // printf("%c", test);

    // ParseFlags(argc, argv);
    // struct Logistics *tmp = InitLogistics();

    // InitTrashFolder(tmp);

    // DeleteFile(tmp, "test1");

    // ViewTrash(tmp, CONCISE);

    // // char *test[] = {"test1", "test2", "test3", "test4", "test5"};  

    // // for (int i = 0; i < 5; i++)
    // // {
    // //     DeleteFile(tmp, test[i]);
    // //     // printf("%s", test[i]);
    // // }   
   
   
    // free(tmp);

    return 0;
}








