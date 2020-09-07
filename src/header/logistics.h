#ifndef LOGISTICS
#define LOGISTICS

//does a /.trash file exist
enum trash_state {TRASH_NULL, TRASH_EXIST};

struct Logistics {
    char trash_pwd[100];
    enum trash_state status;
};

struct Logistics *InitLogistics();

#endif
