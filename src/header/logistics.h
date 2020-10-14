#ifndef LOGISTICS
#define LOGISTICS
struct Logistics {
    char trash_folder[100];
    char trash_files[100];
    char trash_info[100];
    int trash_folder_status;
    int files_folder_status;
    int info_folder_status;
};
enum {IS_NULL, EXIST};
struct Logistics *initlogistics();
#endif
