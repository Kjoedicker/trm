#include "../header/main.h"

void 
parseflags(int argc, char *argv[])
{
    char *use_flag = argv[1]; 

    enum program_actions  {ORIGINAL_RESTORE, RESTORE, DELETE, VIEW_TRASH, VERBOSE_VIEW};
    enum action_verbosity {CONCISE, VERBOSE};
    
    char *flags[5][2] = {
        {"-r", "--ORIGINAL_RESTORE"},
        {"-R", "--RESTORE"},
        {"-d", "--DELETE"},
        {"-v", "--VIEW_TRASH"},
        {"-V", "--VERBOSE_VIEW"}
    };
     
    for (;;) {

        if (argc == 1) { 
            fprintf(stderr, "Error - no parameters provided\n");
            break;
        }

        if (cmpstrings(flags[ORIGINAL_RESTORE][CONCISE], use_flag) ||
            cmpstrings(flags[ORIGINAL_RESTORE][VERBOSE], use_flag) ){
                parsequeuedfiles(&restorefile, argv, 1, argc-1);
                break;        
        }

        if (cmpstrings(flags[RESTORE][CONCISE], use_flag) ||
            cmpstrings(flags[RESTORE][VERBOSE], use_flag) ){
                parserestorefile(argv[2], argv[3]);      
                break;
        }
        
        if (cmpstrings(flags[DELETE][CONCISE], use_flag) ||
            cmpstrings(flags[DELETE][VERBOSE], use_flag) ){
                parsequeuedfiles(&deletefile, argv, 1, argc-1);
                break;        
        }
        if (cmpstrings(flags[VIEW_TRASH][CONCISE], use_flag) ||
            cmpstrings(flags[VIEW_TRASH][VERBOSE], use_flag) ){
                listdir(initlogistics(), CONCISE);                
                break;   
        }

        if (cmpstrings(flags[VERBOSE_VIEW][CONCISE], use_flag) ||
            cmpstrings(flags[VERBOSE_VIEW][VERBOSE], use_flag) ){
                listdir(initlogistics(), VERBOSE);
                break;      
        }

        else {
            parsequeuedfiles(&deletefile, argv, 0, argc-1); 
            break;
        } 
    }
}
