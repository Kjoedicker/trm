#ifndef PROGRAM_ACTIONS
#define PROGRAM_ACTIONS

#include "main.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>


//execute based on the flags provided in the commandline
void ParseFlags(int argc, char *argv[]);

//filter out parameters provided on the commandline
void FilterParameters(int argc, char *argv[]);

#endif