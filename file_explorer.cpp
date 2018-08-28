//
// Created by vivek on 24/8/18.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
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

#define MAX 10000

using namespace std;

stack <char*> left_st;
stack <char*> right_st;

/*vector<file_detail> print_formatted_directory(string pathname) {
    printf("\033c");
    int no_of_entries;
    vector<file_detail> file_details;
    file_details =  list_directory(pathname);
    printf("\033[%dA", no_of_entries);
    return file_details;
}
*/
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
    clrscrn();
    int no_of_entries;
    int c;
    vector<file_detail> file_details;
    //char* directory = "./temp";
    file_details = list_directory(curr_dir);
    left_st.push(curr_dir);
    no_of_entries = file_details.size();
    //cout << file_details.size() <<"\n";
    printf("\033[%dA", no_of_entries + 1);


    while(1) {
        //     tcsetattr(0, TCSANOW, &new_settings);

        c = kbget();
        char* curr_push_left;
        char* curr_right_push;
        if (c == KEY_UP && cursor_pos > 0) {
            cursorupward(1);
            cursor_pos--;
        }
        else if(c == KEY_DOWN && cursor_pos < no_of_entries - 1) {
            cursordownward(1);
            cursor_pos++;
        } else if (c == KEY_ENTER) {
            char new_directory[MAX];
            if ((file_details[cursor_pos].isdir)) {
                //tcsetattr (STDIN_FILENO, TCSAFLUSH, &initial_settings);

                if (cursor_pos == 0) {
                    continue;
                }
                if (cursor_pos == 1) {
                    if (strcmp(home_dir, curr_dir) != 0) {
                        deleteEnd(curr_dir);
                        char *temp = (char *) malloc(strlen(curr_dir));
                        strcpy(temp, curr_dir);
                        left_st.push(temp);
                        curr_push_left = temp;
                    }
                } else {
                    strcpy(new_directory, curr_dir);
                    strcat(new_directory, "/");
                    strcat(new_directory, file_details[cursor_pos].name);
                    curr_dir = new_directory;
                    char *temp = (char *) malloc(strlen(curr_dir));
                    strcpy(temp, curr_dir);
                    left_st.push(temp);
                    curr_push_left = temp;
                }
                clrscrn();
                file_details = list_directory(curr_dir);
                //printf(" left push= %s", curr_push_left);
                no_of_entries = file_details.size();
                //printf("here");
                printf("\033[%dA", no_of_entries + 1);
                cursor_pos = 0;
                continue;

            }

            else {
                char fork_temp[MAX];
                strcpy(fork_temp, curr_dir);
                strcat(fork_temp, "/");
                strcat(fork_temp, file_details[cursor_pos].name);

                pid_t pid;
                pid = fork();
                if(pid == 0) {
                    execl("/usr/bin/xdg-open","xdg-open",fork_temp,(char*)0);
                    //deleteEnd(fork_temp);
                }
                else {
                    if (strcmp(home_dir, curr_dir) != 0) {
                        if(!left_key_access || !right_key_access)
                            deleteEnd(curr_dir);
                        //char *temp = (char *) malloc(strlen(curr_dir));
                        //strcpy(temp, curr_dir);
                        //left_st.push(temp);
                        //curr_push_left = temp;
                    }
                    clrscrn();
                    file_details = list_directory(curr_dir);
                    //printf(" left push= %s", curr_push_left);
                    no_of_entries = file_details.size();
                    //printf("here");
                    printf("\033[%dA", no_of_entries + 1);
                    printf("\033[%dB", cursor_pos);
                    //printf("\033[%dB", cursor_pos);
                    //cursor_pos = 0;
                    continue;

                }


                //deleteEnd(fork_temp);
            }
        } else if (c == KEY_RIGHT) {   //// THIS IS ACTUALLY LEFT CHECK LATER
            left_key_access = 1;
            if(curr_dir == home_dir)
                continue;
            if(!left_st.empty()) {
                //printf("here");
                right_st.push(left_st.top());
                curr_right_push = left_st.top();
                //if(strcmp(left_st.top(),home_dir) != 0)
                left_st.pop();
                if(!left_st.empty()) {
                    curr_dir = left_st.top();
                } else
                    curr_dir= home_dir;
                clrscrn();
                //printf("go to :%s\n", curr_dir);
                file_details = list_directory(curr_dir);
              //  printf(" right push in left key = %s", curr_right_push);
                no_of_entries = file_details.size();
                printf("\033[%dA", no_of_entries + 1);
                cursor_pos = 0;
                continue;
            }
        } else if (c == KEY_LEFT) {
            right_key_access = 1;
            int t = 0;
            char* top;
            if(!right_st.empty()) {
                left_st.push(right_st.top());
                if(!right_st.empty()) {
                    t = 1;
                    top = right_st.top();
                    curr_dir = right_st.top();
                }
                right_st.pop();
                clrscrn();
                //printf("go to :%s\n", curr_dir);
                file_details = list_directory(curr_dir);
                //printf(" right top %s", top);
                no_of_entries = file_details.size();
                printf("\033[%dA", no_of_entries + 1);
                cursor_pos = 0;
                continue;

            }
        } else if(c == 127) {
            if(strcmp(home_dir, curr_dir) != 0) {
                deleteEnd(curr_dir);
                char *temp = (char*)malloc(strlen(curr_dir));
                strcpy(temp, curr_dir);
                left_st.push(temp);
                curr_push_left = temp;
            }
            clrscrn();
            //printf("here");
            //printf("go to :%s\n", curr_dir);
            file_details = list_directory(curr_dir);
            //printf(" right top %s", top);
            no_of_entries = file_details.size();
            printf("\033[%dA", no_of_entries + 1);
            cursor_pos = 0;
            continue;
        }


    }
    return 0;
}