#ifndef LOGISTICS
#define LOGISTICS

#include "main.h"

struct Logistics {
    char trash_folder[MAX_SIZE];
    char trash_files[MAX_SIZE];
    char trash_info[MAX_SIZE];
    int trash_folder_status;
    int files_folder_status;
    int info_folder_status;
};

enum {IS_NULL, EXIST};
struct Logistics *initlogistics();

#endif
