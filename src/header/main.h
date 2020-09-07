
#ifndef MAIN
#define MAIN

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "logistics.h"

// enum trash_state {TRASH_NULL, TRASH_EXIST};

// struct Logistics {
//     char trash_pwd[100];
//     enum trash_state status;
// };

// struct Logistics *InitLogistics();

//transform data
#include "file_manipulation.h"
#include "str_manipulation.h"

//create data 
#include "data_initializers.h"

//act according to data
#include "program_actions.h"

#define DATA_SIZE 1000

#define FILE_PERMISSIONS 0755
#define TRASH_DIRECTORY "/home/keifer/.trash/"

#endif