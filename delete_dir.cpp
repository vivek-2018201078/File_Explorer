//
// Created by vivek on 3/9/18.
//
#include "delete_dir.h"
#include "command_exec.h"
#include <string.h>
#include <cstring>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include "global_variables.h"
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <queue>
#include <fstream>
#include <dirent.h>
#include "file_copy.h"

using namespace std;

void delete_dir(char* dir_path) {

    struct dirent **file_list;
    int no_of_items;
    no_of_items = scandir(dir_path, &file_list, NULL, alphasort);

    for(int i = 2; i < no_of_items; i++) {
        char file_iniside_dir[1000];
        strcpy(file_iniside_dir, dir_path);
        strcat(file_iniside_dir, "/");
        strcat(file_iniside_dir, file_list[i]->d_name);

        struct stat st;
        stat(file_iniside_dir, &st);
        if(S_ISDIR(st.st_mode)) {
            char to_send[1000];
            strcpy(to_send, dir_path);
            strcat(to_send, "/");
            strcat(to_send, file_list[i]->d_name);
            delete_dir(to_send);
        }
        else {
            int res = remove(file_iniside_dir);
        }

    }
    rmdir(dir_path);

}
