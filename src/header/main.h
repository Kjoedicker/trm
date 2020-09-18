
#ifndef MAIN
#define MAIN

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


//actions to be performed
#include "filelib.h"

//controls the execution of the program based on the flags provided
#include "flowcontrol.h"

//for initializing essential folders during runtime. (.trash, .trace, .<deleted_folder>, etc.)
#include "initlib.h"

//implements the logistics struct which contains core information about the directory structures
#include "logistics.h"

//for all parsing purposes
#include "parselib.h"

//supplemental tools to help with logic and overall execution of various functions
#include "toollib.h"





#endif