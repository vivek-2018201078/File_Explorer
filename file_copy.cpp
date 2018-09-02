//
// Created by vivek on 2/9/18.
//
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


void file_copy(char* file_name, char* destination) {
    FILE* source;
    FILE* destin;
    int ch;
    /*char abs_file_name[1000];
    char directory_name[1000];
    strcpy(abs_file_name, curr_dir);
    strcat(abs_file_name, "/");
    strcat(abs_file_name, file_name);

    strcpy(directory_name, home_dir);
    strcat(directory_name,"/");
    if(destination[0] == '~') {
        destination++;
        destination++;
    }
    strcat(directory_name, destination);
    strcat(directory_name, "/");
    strcat(directory_name, file_name);*/

    printf(" %s %s ", file_name, destination);

    source = fopen(file_name, "r");
    if(source == NULL)
        printf(" source ");
    destin = fopen(destination, "w");
    if(destin == NULL)
        printf(" destin ");

    while( ( ch = fgetc(source)) != EOF )
        fputc(ch, destin);

    fclose(source);
    fclose(destin);
}
