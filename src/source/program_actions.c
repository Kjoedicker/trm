#include "../header/main.h"


//based on the cli parameteres provided on runtime, act accordingly
void DirectFlow(int argc, char *argv[])
{
    switch(argc)
    {
        case 1:
            fprintf(stderr, "Error - no parameters provided\n");
            break;
        //(#1) -v will not work without additional parameters, problamatic
        case 2:
            if(!(stripcmp(argv, '-')))
            {
                struct Logistics *core_logistics = InitLogistics();
                DeleteFile(core_logistics->trash_pwd, argv[1]); 
                free(core_logistics);
                break;  
            }

            fprintf(stderr, "%s missing argument", argv[1]);
            break;

        default:
            ParseFlags(argc, argv);
            break;
    }
}

//flags dictate the next function call on the target file
void ParseFlags(int argc, char *argv[])
{
    struct Logistics *core_logistics = InitLogistics();

    char *use_flag = argv[1]; 

    enum program_actions  {RESTORE, ORIGINAL_RESTORE, DELETE, VIEW_TRASH, VERBOSE_VIEW};
    enum action_verbosity {CONCISE, VERBOSE};
    
    //3 dimensions, two pointers per dimension
    char *flags[5][2] = {
        {"-r", "--RESTORE"},
        {"-R", "--ORIGINAL_RESTORE"},
        {"-d", "--DELETE"},
        {"-v", "--VIEW_TRASH"},
        {"-V", "--VERBOSE_VIEW"}
    };

    //the option to break helps limit the numbers of checks we have to make each flag
    while (1) {

        if (cmpstr(flags[RESTORE][CONCISE], use_flag) ||
            cmpstr(flags[RESTORE][VERBOSE], use_flag) ){
                printf("restore");                
                break;        
        }

        if (cmpstr(flags[ORIGINAL_RESTORE][CONCISE], use_flag) ||
            cmpstr(flags[ORIGINAL_RESTORE][VERBOSE], use_flag) ){
                printf("original_restore");                
                break;
        }
        
        if (cmpstr(flags[DELETE][CONCISE], use_flag) ||
            cmpstr(flags[DELETE][VERBOSE], use_flag) ){
                DeleteFile(core_logistics->trash_pwd, argv[2]);                
                break;        
        }
        
        if (cmpstr(flags[VIEW_TRASH][CONCISE], use_flag) ||
            cmpstr(flags[VIEW_TRASH][VERBOSE], use_flag) ){
                ViewTrash(core_logistics, CONCISE);                
                break;   
        }

        if (cmpstr(flags[VERBOSE_VIEW][CONCISE], use_flag) ||
            cmpstr(flags[VERBOSE_VIEW][VERBOSE], use_flag) ){
                ViewTrash(core_logistics, VERBOSE);
                break;      
        }

        //making it this far is an error on the users part
        fprintf(stderr, "%s invalid flag", use_flag);
        break;

    }

    free(core_logistics);
}

int ViewTrash(struct Logistics *core_logistics, int view_size) 
{ 
    struct stat file_stat;

    //readdir() will access directory_stream returning a pointer to a entry to be accessed
    struct dirent *directory_entry;  

    //opendir returns a stream of files in the directory
    DIR *directory_stream = opendir(core_logistics->trash_pwd);

    if (directory_stream)
    {
        //access the next dirent in the directory_stream, filtering out '.' ".." path directives
        while (((directory_entry = readdir(directory_stream)) != NULL) &&
                (!(cmpstr(directory_entry->d_name, "."))) &&
                (!(cmpstr(directory_entry->d_name, ".."))) )
        {      
            //because files in .trash are nested in a self named folder we need to append for that depth for the full pwd     
            size_t filename_size = (strlen(core_logistics->trash_pwd) + (strlen(directory_entry->d_name) * 2)) + 2;
            char *file_path = cat_path(filename_size,
                                       cat_path(filename_size - strlen(directory_entry->d_name), 
                                                core_logistics->trash_pwd, 
                                                directory_entry->d_name,
                                                KEEP_HEAD),
                                       directory_entry->d_name,
                                       FREE_HEAD);
            
            if (access(file_path, F_OK) + 1)
            {
                switch (view_size)
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
  
    return 0; 
} 
