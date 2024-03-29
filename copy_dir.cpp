//
// Created by vivek on 2/9/18.
////  ROLL NO. - 2018201078
////  NAME - VIVEK PATARE

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

void copy_dir(char* directory_path , char* destination, char* dirname) {

    mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
    int fd = mkdir(destination, mode);
    struct dirent **file_list;
    int no_of_entries;
    no_of_entries = scandir(directory_path, &file_list, NULL, alphasort);
    for (int i = 0; i < no_of_entries; i++) {
        if (strcmp(file_list[i]->d_name, ".") == 0 || strcmp(file_list[i]->d_name, "..") == 0) {
            continue;
        }
        char file_inside_dir[1000];
        strcpy(file_inside_dir, directory_path);
        strcat(file_inside_dir, "/");
        strcat(file_inside_dir, file_list[i]->d_name);
        struct stat file_detail;
        stat(file_inside_dir, &file_detail);
        if(S_ISDIR(file_detail.st_mode)) {
            char dest2[1000];
            strcpy(dest2, destination);
            strcat(dest2, "/");
            strcat(dest2, file_list[i]->d_name);
            copy_dir(file_inside_dir, dest2, dirname);
        }
        else{
            char file2[1000];
            char dest2[1000];
            strcpy(dest2, destination);
            strcat(dest2, "/");
            strcat(dest2, file_list[i]->d_name);
            strcpy(file2, directory_path);
            strcat(file2, "/");
            strcat(file2, file_list[i]->d_name);
            file_copy(file2, dest2);
        }

    }
}