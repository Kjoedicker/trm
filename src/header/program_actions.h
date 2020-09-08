#ifndef PROGRAM_ACTIONS
#define PROGRAM_ACTIONS

#include "main.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>


//direct based on data
void ParseFlags(int argc, char *argv[]);

//based on the cli parameteres provided on runtime, act accordingly
void DirectFlow(int argc, char *argv[]);

//view the contents of directory
void ListDir(char *target_folder, int view_size);
enum action_verbosity {CONCISE, VERBOSE};


#endif