//
// Created by vivek on 31/8/18.
//
#include "command_exec.h"
#include <string.h>
#include <cstring>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include "global_variables.h"

/*#define COPY            "copy"
#define MOVE            "move"
#define RENAME          "rename"
#define CREATE_FILE     "create_file"
#define CREATE_DIR      "create_dir"
#def*/


int command_exec(char* command_input) {
    int index = 0;
    char* token;
    char* input = command_input;
    //printf("%s", command_input);
    vector<char*> all_tokens;
    int length = strlen(command_input);
    while((token = strtok_r(input, " ", &input)))
        all_tokens.push_back(token);
    //printf(" %s %s %s", all_tokens[0]);
    if(strcmp(all_tokens[0], "create_file") == 0) {
        //printf(" here");
        if(all_tokens.size() != 3) {
            return 0;
        }
        else {
            mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
            char filepath[1000];
            //strcpy(filepath, absolute_home_path);
            //strcat(filepath,"/");
            strcpy(filepath, curr_dir);
            strcat(filepath,"/");
            if(all_tokens[2][0] == '~') {
                (all_tokens[2])++;
                (all_tokens[2])++;
            }
            strcpy(filepath,all_tokens[2]);
            strcat(filepath,"/");
            strcat(filepath, all_tokens[1]);
            //printf("%s", filepath);
            int fd = creat(filepath, mode);
            if(fd == -1)
                return 0;
            else
                return 1;
            //printf(" fd = %d", fd);
            return 1;
        }
    }

    if(strcmp(all_tokens[0], "create_dir") == 0) {
        if(all_tokens.size() != 3) {
            return 0;
        }
        else {
            mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ;
            char filepath[1000];
            //strcpy(filepath, absolute_home_path);
            //strcat(filepath,"/");
            strcpy(filepath, curr_dir);
            strcat(filepath,"/");
            if(all_tokens[2][0] == '~') {
                (all_tokens[2])++;
                (all_tokens[2])++;
            }
            strcat(filepath,all_tokens[2]);
            strcat(filepath,"/");
            strcat(filepath, all_tokens[1]);
            //printf("%s", filepath);
            int fd = mkdir(filepath, mode);
            if(fd == -1)
                return 0;
            else
                return 1;
            //printf(" fd = %d", fd);
            return 1;
        }
    }

    if(strcmp(all_tokens[0], "rename") == 0) {
        if(all_tokens.size() != 3) {
            return 0;
        }
        else {
            char rename_to[1000];
            char rename_from[1000];
            strcpy(rename_to, curr_dir);
            strcat(rename_to, "/");
            strcat(rename_to, all_tokens[2]);

            strcpy(rename_from, curr_dir);
            strcat(rename_from, "/");
            strcat(rename_from, all_tokens[1]);

            int ans = rename(rename_from, rename_to);
            if(!ans)
                return 1;
            else
                return 0;
        }
    }
   return 0;

}
