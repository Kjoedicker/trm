#ifndef LOGISTICS
#define LOGISTICS
// TODO(#1): Test snitch
struct Logistics {
    char trash_folder_pwd[100];
    char trace_file_loc[100];
    int trash_folder_status;
    int trace_folder_status;
};

enum {IS_NULL, EXIST};
struct Logistics *initlogistics();

#endif
