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
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <queue>

/*#define COPY            "copy"
#define MOVE            "move"
#define RENAME          "rename"
#define CREATE_FILE     "create_file"
#define CREATE_DIR      "create_dir"
#def*/

using namespace std;

int command_exec(char* command_input) {
    //int index1 = 0;
    char* token;
    char* input = command_input;
    //printf(" %s", command_input);
    vector<char*> all_tokens;
    int length = strlen(command_input);
    while((token = strtok_r(input, " ", &input)))
        all_tokens.push_back(token);


    //printf(" %s %s %s", all_tokens[0], all_tokens[1], all_tokens[2]);

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
            strcpy(filepath, home_dir);
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
            strcpy(filepath, home_dir);
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

    if(strcmp(all_tokens[0], "delete_file") == 0) {
        if(all_tokens.size() != 2) {
            return 0;
        }
        else {
            char to_delete[1000];
            strcpy(to_delete, absolute_home_path);
            strcat(to_delete, "/");
            strcat(to_delete, curr_dir);
            strcat(to_delete, "/");
            strcat(to_delete, all_tokens[1]);
            //printf("%s", to_delete);
            int ans = remove(to_delete);
            if (ans == 0)
                return 1;
            else
                return 0;
        }
    }

    /*if(strcmp(all_tokens[0], "copy") == 0) {


    }*/

    if(strcmp(all_tokens[0], "snapshot") == 0) {
        //printf("here1");
        if(all_tokens.size() != 3) {
            return 0;
        }
        else {
            //printf("here2");
            queue <char*> q;
            FILE *fp;
            fp = fopen(all_tokens[2], "w+");
            if(fp == NULL)
                printf("cant open file");
            char stat_path[1000];
            strcpy(stat_path, home_dir);
            strcat(stat_path, "/");
            strcat(stat_path, all_tokens[1]);
            q.push(stat_path);
            //printf("%s",q.front());
            struct stat file_stat;
            while(!q.empty()) {
                //printf("here");
                //printf("\nin while %s", q.front());
                fputs("\n", fp);
                fputs(q.front(), fp);
                fputs(":", fp);
                fputs("\n", fp);
                struct dirent **file_list;
                int no_of_entries;
                char scan_path[1000];
                strcpy(scan_path, q.front());
                //printf("\nfront =  %s ", q.front());
                q.pop();
                no_of_entries = scandir(scan_path, &file_list, NULL, alphasort);
                //printf(" entries =  %d\n", no_of_entries);
                for(int i = 0; i < no_of_entries; i++) {
                    char arr[1000];
                    strcpy(arr, scan_path);
                    //printf("%s ", scan_path);
                    //printf("x = %s\n", file_list[i]->d_name);
                    strcat(arr, "/");
                    strcat(arr, file_list[i]->d_name);

                    stat(arr, &file_stat);
                    if(S_ISDIR(file_stat.st_mode) && (strcmp(file_list[i]->d_name, ".") != 0) && (strcmp(file_list[i]->d_name, "..") != 0)) {
                        //printf("dir = %s\n", arr);
                        char dir[1000][1000];
                        strcpy(dir[i], arr);
                        //memset(dir, 0, 255);
                        //printf("\n dir = %s", dir);
                        q.push(dir[i]);
                        //printf("\n%s", q.front());
                    }
                    else if(S_ISREG(file_stat.st_mode)) {
                        //printf("file = %s\n", arr);
                        fputs(file_list[i]->d_name, fp);
                        fputs("\t", fp);
                    }
                }
            }
            fclose(fp);
            return 1;
        }
    }

   return 0;

}
