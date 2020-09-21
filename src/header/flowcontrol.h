#ifndef PROGRAM_ACTIONS
#define PROGRAM_ACTIONS

#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "main.h"

// TODO(#5): rewrite this in Rust
void parseflags(int argc, char *argv[]);

#endif