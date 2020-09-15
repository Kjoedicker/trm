
#ifndef MAIN
#define MAIN

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


//implements the logisitcs struct which contains core information about the directory structures
#include "Logistics.h"

//for all parsing purposes
#include "ParseLib.h"

//actions to be performed
#include "FileLib.h"

//supplemental tools to help with logic and overall execution of various functions
#include "ToolLib.h"

//for initializing essential folders during runtime. (.trash, .trace, .<deleted_folder>, etc.)
#include "InitLib.h"

//controls the execution of the program based on the flags provided
#include "FlowControl.h"

// #define DATA_SIZE 1000

// #define FILE_PERMISSIONS 0755
// #define TRASH_DIRECTORY "/home/keifer/.trash/"

#endif