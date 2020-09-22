
#ifndef MAIN
#define MAIN

#include <stdlib.h>
#include <stdio.h>
// #include <unistd.h>
#include <string.h>
#include <sys/stat.h>


//implements the logistics struct which contains core information about the directory structures
#include "logistics.h"

//for all parsing purposes
#include "parselib.h"

//actions to be performed
#include "filelib.h"

//supplemental tools to help with logic and overall execution of various functions
#include "toollib.h"

//for initializing essential folders during runtime. (.trash, .trace, .<deleted_folder>, etc.)
#include "initlib.h"

//controls the execution of the program based on the flags provided
#include "flowcontrol.h"


#endif