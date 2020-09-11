
#include "src/header/main.h"

struct Argument {
    char *argument;
    char *parsed_argument;
    int IsPath;
    char *current_pwd;
    char *destination_pwd;
};

//retun 0 : 1 if full path to a file 
int IsPath(char *argument)
{   
    int index = 0;
    for (; argument[index] != '\0'; index++)
    {
        if (argument[index] == '/')
        {
            return 1;
        }      
    }

    return 0;
}

// char *getPWD(char *argument)
// {

// }

char *ParseFilePath1(char *argument)
{   
    //copy over so we can work with a terminated string
    char *provided_path = malloc(sizeof(char) * 25);
    strcpy(provided_path, argument);

    char *parsed_name = malloc(sizeof(char) * 50);
    int index = 0;

    for (int pp_index = 0; provided_path[pp_index] != '\0'; pp_index++)
    {
        //skip this and restart index to write over parsed_name from the beginning
        if (provided_path[pp_index] == '/')
        {
            pp_index++;
            index = 0;
        }

        parsed_name[index++] = provided_path[pp_index];
    }

    //we write over parsed_name every '/', each write over varies in size so its important to mark the end.
    parsed_name[index] = '\0';

    free(provided_path);

    return parsed_name;
}

struct Argument *strip(char *argument)
{
    struct Argument *parsed_argument = malloc(sizeof(struct Argument));

    parsed_argument->argument = malloc(sizeof(char) * 25);
    strcpy(parsed_argument->argument, argument);

    parsed_argument->parsed_argument = ParseFilePath1(argument);
    parsed_argument->IsPath = IsPath(argument);

    return parsed_argument;

    // parsed_argument->current_pwd = getPWD(argument);
};


              
int main(int argc, char *argv[], char **envp)
{
    // ParseFlags(argc, argv);
    struct Argument *zero = strip(argv[1]);






    // char test = argv[1][0];
    // printf("%c", test);

    // ParseFlags(argc, argv);
    // struct Logistics *tmp = InitLogistics();

    // InitTrashFolder(tmp);

    // DeleteFile(tmp, "test1");

    // ViewTrash(tmp, CONCISE);

    // // char *test[] = {"test1", "test2", "test3", "test4", "test5"};  

    // // for (int i = 0; i < 5; i++)
    // // {
    // //     DeleteFile(tmp, test[i]);
    // //     // printf("%s", test[i]);
    // // }   
   
   
    // free(tmp);

    return 0;
}








