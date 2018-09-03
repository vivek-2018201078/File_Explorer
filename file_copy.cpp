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
