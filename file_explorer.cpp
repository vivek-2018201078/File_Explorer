//
// Created by vivek on 24/8/18.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include<stdio.h>
#include<string.h>
#include<termios.h>
#include <math.h>
#include "list_directory.h"
#include "global_variables.h"
#include "raw_input.h"
#include "command_mode.h"

#define MAX 10000

using namespace std;

stack <char*> left_st;
stack <char*> right_st;

void clrscrn() {
    printf("\033c");
}

void deleteEnd (char* myStr){

    printf ("%s\n", myStr);
    char *del = &myStr[strlen(myStr)];

    while (del > myStr && *del != '/')
        del--;

    if (*del== '/')
        *del= '\0';

    return;
}

int main()
{

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    terminal_lines = w.ws_row;
    terminal_col = w.ws_col;
    clrscrn();
    int c;
    vector<file_detail> file_details;
    file_details = list_directory(curr_dir);
    left_st.push(curr_dir);
    no_of_entries = file_details.size();
    printf("\033[%dA", terminal_lines - cursor_line + 2);


    while(1) {
        if (mode == 0) {
            c = kbget();

            if (c == KEY_ENTER) {
                char new_directory[MAX];
                if ((file_details[cursor_pos].isdir)) {
                    left_file_index = 0;
                    right_file_index = 34;
                    if (cursor_pos == 0) {
                        continue;
                    }
                    if (cursor_pos == 1) {
                        if (strcmp(home_dir, curr_dir) != 0) {
                            deleteEnd(curr_dir);
                            char *temp = (char *) malloc(strlen(curr_dir));
                            strcpy(temp, curr_dir);
                            left_st.push(temp);
                        }
                    } else {
                        strcpy(new_directory, curr_dir);
                        strcat(new_directory, "/");
                        strcat(new_directory, file_details[cursor_pos].name);
                        curr_dir = new_directory;
                        char *temp = (char *) malloc(strlen(curr_dir));
                        strcpy(temp, curr_dir);
                        left_st.push(temp);
                    }
                    clrscrn();
                    file_details = list_directory(curr_dir);
                    no_of_entries = file_details.size();
                    printf("\033[%dA", terminal_lines - cursor_line + 2);
                    cursor_pos = 0;
                    cursor_line = 0;
                    continue;

                } else {
                    char fork_temp[MAX];
                    strcpy(fork_temp, curr_dir);
                    strcat(fork_temp, "/");
                    strcat(fork_temp, file_details[cursor_pos].name);

                    pid_t pid;
                    pid = fork();


                    if (pid == 0) {
                        execl("/usr/bin/xdg-open", "xdg-open", fork_temp, (char *) 0);
                        exit(0);
                    }

                    if (left_key_access == 0 && right_key_access == 0)
                        deleteEnd(curr_dir);

                    clrscrn();
                    file_details = list_directory(curr_dir);
                    no_of_entries = file_details.size();
                    if (cursor_pos > 34) {
                        if (cursor_line == 34) {
                            printf("\033[%dA", terminal_lines - cursor_line + 1);
                        }
                        printf("\033[%dA", terminal_lines - 1);
                        printf("\033[%dB", cursor_line);
                    } else {
                        if (cursor_line == 0) {
                            printf("\033[%dA", terminal_lines - 1);
                        } else if (left_file_index > 0) {
                            printf("\033[%dA", no_of_entries + 2);
                            printf("\033[%dB", cursor_line);
                        } else {
                            printf("\033[%dA", terminal_lines - 1);
                            printf("\033[%dB", cursor_line);
                        }
                    }

                    continue;

                }



            } else if (c == KEY_RIGHT) {   //// THIS IS ACTUALLY LEFT CHECK LATER
                left_key_access = 1;
                left_file_index = 0;
                right_file_index = 34;
                if (curr_dir == home_dir)
                    continue;
                if (!left_st.empty()) {
                    right_st.push(left_st.top());
                    left_st.pop();
                    if (!left_st.empty()) {
                        curr_dir = left_st.top();
                    } else
                        curr_dir = home_dir;
                    clrscrn();
                    file_details = list_directory(curr_dir);
                    no_of_entries = file_details.size();
                    printf("\033[%dA", no_of_entries + 2);
                    cursor_pos = 0;
                    cursor_line = 0;
                    continue;
                }
            } else if (c == KEY_LEFT) {
                right_key_access = 1;
                left_file_index = 0;
                right_file_index = 34;
                if (!right_st.empty()) {
                    left_st.push(right_st.top());
                    if (!right_st.empty()) {
                        curr_dir = right_st.top();
                    }
                    right_st.pop();
                    clrscrn();
                    file_details = list_directory(curr_dir);
                    no_of_entries = file_details.size();
                    printf("\033[%dA", no_of_entries + 2);
                    cursor_pos = 0;
                    cursor_line = 0;
                    continue;

                }
            } else if (c == 127) {
                left_key_access = 1;
                left_file_index = 0;
                right_file_index = 34;
                if (strcmp(home_dir, curr_dir) != 0) {
                    deleteEnd(curr_dir);
                    char *temp = (char *) malloc(strlen(curr_dir));
                    strcpy(temp, curr_dir);
                    left_st.push(temp);
                }
                clrscrn();
                file_details = list_directory(curr_dir);
                no_of_entries = file_details.size();
                printf("\033[%dA", no_of_entries + 2);
                cursor_pos = 0;
                cursor_line = 0;
                continue;

                // KEY UP
            } else if (c == KEY_UP) {
                if (cursor_pos == 0) { ;
                } else if (cursor_pos > left_file_index) {
                    cursorupward(1);
                    cursor_pos--;
                    cursor_line--;
                } else {
                    left_file_index--;
                    right_file_index--;
                    clrscrn();
                    file_details = list_directory(curr_dir);
                    cursor_pos--;
                    printf("\033[%dA", terminal_lines - 1);

                }
            } else if (c == KEY_DOWN && cursor_pos < no_of_entries - 1) {
                if (cursor_line <= 33) {
                    cursordownward(1);
                    cursor_pos++;
                    cursor_line++;
                } else {
                    if (right_file_index < no_of_entries - 1) {
                        cursor_pos++;
                        left_file_index++;
                        right_file_index++;
                    }
                    clrscrn();
                    file_details = list_directory(curr_dir);
                    printf("\033[%dA", terminal_lines - cursor_line - 1);



                }
            } else if (c == 58) {
                mode = 1;
                cursordownward(terminal_lines - cursor_line);
                printf("\033[2K");
                printf(":");
                command_mode();

            }
        }
    else {

    }
    }
    return 0;
}