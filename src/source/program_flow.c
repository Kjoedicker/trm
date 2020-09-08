#include "../header/main.h"

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

        //no parameters == nothing to act on
        if (argc == 1) 
        { 
            fprintf(stderr, "Error - no parameters provided\n");
            break;
        }

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
                ParseQueuedFiles(core_logistics->trash_pwd, argv, argc-1);                
                break;        
        }
        
        if (cmpstr(flags[VIEW_TRASH][CONCISE], use_flag) ||
            cmpstr(flags[VIEW_TRASH][VERBOSE], use_flag) ){
                ListDir(core_logistics->trash_pwd, CONCISE);                
                break;   
        }

        if (cmpstr(flags[VERBOSE_VIEW][CONCISE], use_flag) ||
            cmpstr(flags[VERBOSE_VIEW][VERBOSE], use_flag) ){
                ListDir(core_logistics->trash_pwd, VERBOSE);
                break;      
        }

        //TRM by default should delete the arguments provided if no other flags are conditioned
        else {
            //parse files to delete
            ParseQueuedFiles(core_logistics->trash_pwd, argv, argc-1);
            break;
        } 

        // //making it this far is an error on the users part
        // fprintf(stderr, "%s invalid flag", use_flag);
        // break;

    }

    free(core_logistics);
}

