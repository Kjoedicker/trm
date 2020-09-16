#ifndef LOGISTICS
#define LOGISTICS

//does a /.trash file exist
enum state {IS_NULL, EXIST};

struct Logistics {
    char trash_folder_pwd[100];
    char trace_file_loc[100];
    enum state trash_folder_status;
    enum state trace_folder_status;
};

struct Logistics *InitLogistics();

#endif
