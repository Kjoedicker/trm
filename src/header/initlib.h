#ifndef INIT_ACTIONS
#define INIT_ACTIONS

#include "main.h"

struct Logistics *initlogistics();
void inittrashfolders(struct Logistics *core_logistics);

struct restlogistics {
    char *file_loc;
    char *origin_pwd;
};
struct restlogistics* initrestlogistics(struct Argument *target_file);

#endif