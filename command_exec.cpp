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
#include <fstream>
#include <dirent.h>
#include "file_copy.h"
#include "copy_dir.h"
#include "delete_dir.h"
#include "list_directory.h"


using namespace std;

int command_exec(char* command_input) {
    //int index1 = 0;
    char *token;
    char *input = command_input;
    if (backspace_pressed == 1)
        input++;
    backspace_pressed = 0;
    vector<char *> all_tokens;
    int length = strlen(command_input);
    if (length == 0) {
        return 0;
    }
    while ((token = strtok_r(input, " ", &input)))
        all_tokens.push_back(token);


    if (strcmp(all_tokens[0], "create_file") == 0) {
        if (all_tokens.size() != 3) {
            return 0;
        } else {
            mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
            char filepath[1000];
            strcpy(filepath, home_dir);
            strcat(filepath, "/");
            if (all_tokens[2][0] == '~') {
                (all_tokens[2])++;
                (all_tokens[2])++;
            }
            strcpy(filepath, all_tokens[2]);
            strcat(filepath, "/");
            strcat(filepath, all_tokens[1]);
            int fd = creat(filepath, mode);
            if (fd == -1)
                return 0;
            else
                return 1;
        }
    }

    if (strcmp(all_tokens[0], "create_dir") == 0) {
        if (all_tokens.size() != 3) {
            return 0;
        } else {
            mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
            char filepath[1000];
            strcpy(filepath, home_dir);
            strcat(filepath, "/");
            if (all_tokens[2][0] == '~') {
                (all_tokens[2])++;
                (all_tokens[2])++;
            }
            strcat(filepath, all_tokens[2]);
            strcat(filepath, "/");
            strcat(filepath, all_tokens[1]);
            printf(" %s ", filepath);
            int fd = mkdir(filepath, mode);
            if (fd == -1)
                return 0;
            else
                return 1;
        }
    }

    if (strcmp(all_tokens[0], "rename") == 0) {
        if (all_tokens.size() != 3) {
            return 0;
        } else {
            char rename_to[1000];
            char rename_from[1000];
            strcpy(rename_to, curr_dir);
            strcat(rename_to, "/");
            strcat(rename_to, all_tokens[2]);

            strcpy(rename_from, curr_dir);
            strcat(rename_from, "/");
            strcat(rename_from, all_tokens[1]);

            int ans = rename(rename_from, rename_to);
            if (!ans)
                return 1;
            else
                return 0;
        }
    }

    if (strcmp(all_tokens[0], "delete_file") == 0) {
        if (all_tokens.size() != 2) {
            return 0;
        } else {
            char to_delete[1000];
            //strcpy(to_delete, absolute_home_path);
            //strcat(to_delete, "/");
            strcpy(to_delete, home_dir);
            strcat(to_delete, "/");
            if (all_tokens[1][0] == '~') {
                all_tokens[1]++;
                all_tokens[1]++;
            }
            strcat(to_delete, all_tokens[1]);
            //printf("%s", to_delete);
            int ans = remove(to_delete);
            if (ans == 0)
                return 1;
            else
                return 0;
        }
    }

    if (strcmp(all_tokens[0], "delete_dir") == 0) {
        if (all_tokens.size() != 2)
            return 0;
        char dir_delete_path[1000];
        strcpy(dir_delete_path, home_dir);
        strcat(dir_delete_path, "/");
        if (all_tokens[1][0] == '~') {
            all_tokens[1]++;
            all_tokens[1]++;
        }
        strcat(dir_delete_path, all_tokens[1]);
        delete_dir(dir_delete_path);
        return 1;
    }


    if (strcmp(all_tokens[0], "move") == 0) {
        if (all_tokens.size() < 3) {
            return 0;
        } else {
            int i = 0;
            while (i < (all_tokens.size() - 2)) {
                char abs_file_name[1000];
                char directory_name[1000];
                strcpy(abs_file_name, curr_dir);
                strcat(abs_file_name, "/");
                strcat(abs_file_name, all_tokens[i + 1]);

                strcpy(directory_name, home_dir);
                strcat(directory_name, "/");
                if (all_tokens[all_tokens.size() - 1][0] == '~') {
                    all_tokens[all_tokens.size() - 1]++;
                    all_tokens[all_tokens.size() - 1]++;
                }
                strcat(directory_name, all_tokens[all_tokens.size() - 1]);
                strcat(directory_name, "/");
                strcat(directory_name, all_tokens[i + 1]);
                struct stat details;
                stat(abs_file_name, &details);
                if (S_ISREG(details.st_mode)) {
                    file_copy(abs_file_name, directory_name);
                    //printf("%s", abs_file_name);
                    remove(abs_file_name);
                }


                if (S_ISDIR(details.st_mode)) {
                    char directory_name_passed[1000];
                    char copied_to[1000];
                    char dir_name[1000];
                    strcpy(dir_name, all_tokens[i + 1]);
                    strcpy(directory_name_passed, abs_file_name);
                    strcpy(copied_to, directory_name);
                    copy_dir(directory_name_passed, copied_to, dir_name);
                    delete_dir(directory_name_passed);
                }
                i++;

            }
            return 1;
        }
    }

    if (strcmp(all_tokens[0], "copy") == 0) {
        if (all_tokens.size() < 3) {
            return 0;
        } else {
            int i = 0;
            while (i < (all_tokens.size() - 2)) {
                char abs_file_name[1000];
                char directory_name[1000];
                strcpy(abs_file_name, curr_dir);
                strcat(abs_file_name, "/");
                strcat(abs_file_name, all_tokens[i + 1]);

                strcpy(directory_name, home_dir);
                strcat(directory_name, "/");
                if (all_tokens[all_tokens.size() - 1][0] == '~') {
                    all_tokens[all_tokens.size() - 1]++;
                    all_tokens[all_tokens.size() - 1]++;
                }
                strcat(directory_name, all_tokens[all_tokens.size() - 1]);
                strcat(directory_name, "/");
                strcat(directory_name, all_tokens[i + 1]);

                struct stat details;
                stat(abs_file_name, &details);
                if (S_ISREG(details.st_mode)) {
                    file_copy(abs_file_name, directory_name);
                }


                if (S_ISDIR(details.st_mode)) {
                    char directory_name_passed[1000];
                    char copied_to[1000];
                    char dir_name[1000];
                    strcpy(dir_name, all_tokens[i + 1]);
                    strcpy(directory_name_passed, abs_file_name);
                    strcpy(copied_to, directory_name);
                    copy_dir(directory_name_passed, copied_to, dir_name);
                }

                i++;
            }


            return 1;
        }

    }

    if (strcmp(all_tokens[0], "snapshot") == 0) {
        if (all_tokens.size() != 3) {
            return 0;
        } else {
            queue<char *> q;
            FILE *fp;
            fp = fopen(all_tokens[2], "w+");
            if (fp == NULL)
                printf("cant open file");
            char stat_path[1000];
            strcpy(stat_path, home_dir);
            strcat(stat_path, "/");
            strcat(stat_path, all_tokens[1]);
            q.push(stat_path);
            struct stat file_stat;
            while (!q.empty()) {
                fputs("\n", fp);
                fputs(q.front(), fp);
                fputs(":", fp);
                fputs("\n", fp);
                struct dirent **file_list;
                int no_of_entries;
                char scan_path[1000];
                strcpy(scan_path, q.front());
                q.pop();
                no_of_entries = scandir(scan_path, &file_list, NULL, alphasort);
                for (int i = 0; i < no_of_entries; i++) {
                    char arr[1000];
                    strcpy(arr, scan_path);
                    strcat(arr, "/");
                    strcat(arr, file_list[i]->d_name);

                    stat(arr, &file_stat);
                    if (S_ISDIR(file_stat.st_mode) && (strcmp(file_list[i]->d_name, ".") != 0) &&
                        (strcmp(file_list[i]->d_name, "..") != 0)) {
                        char dir[1000][1000];
                        strcpy(dir[i], arr);
                        q.push(dir[i]);
                    } else if (S_ISREG(file_stat.st_mode)) {
                        fputs(file_list[i]->d_name, fp);
                        fputs("\t", fp);
                    }
                }
            }
            fclose(fp);
            return 1;
        }
    }

/*    if (strcmp(all_tokens[0], "goto") == 0) {
        if (all_tokens.size() != 2)
            return 0;
        char path[1000];
        strcpy(path, ".");
        strcat(path, "/");
        if (all_tokens[1][0] == '/')
            all_tokens[1]++;
        strcat(path, all_tokens[1]);
        struct stat directory_stat;
        int a = stat(path, &directory_stat);
        if (a == -1)
            return 0;
        *//*curr_dir = path;
        return 2;*//*
        printf("\033c");
        right_file_index = terminal_lines - 4;
        int c;
        vector<file_detail> file_details;
        file_details = list_directory(path);
        left_st.push(curr_dir);
        no_of_entries = file_details.size();
        printf("\033[%dA", terminal_lines - cursor_line + 2);
        return 2;


        return 0;

    }*/
}
