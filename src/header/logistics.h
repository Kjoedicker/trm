#ifndef LOGISTICS
#define LOGISTICS
struct Logistics {
    char trash_folder_pwd[100];
    char trace_file_loc[100];
    int trash_folder_status;
    int trace_folder_status;
};
// TODO(#11): test
enum {IS_NULL, EXIST};
struct Logistics *initlogistics();
#endif
