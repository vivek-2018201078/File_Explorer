//
// Created by vivek on 24/8/18.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
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

int main()
{
    clrscrn();
    int no_of_entries;
    int c;
    vector<file_detail> file_details;
    //char* directory = "./temp";
    file_details = list_directory(curr_dir);
    no_of_entries = file_details.size();
    //cout << file_details.size() <<"\n";
    printf("\033[%dA", no_of_entries);


    while(1) {
        //     tcsetattr(0, TCSANOW, &new_settings);

        c = kbget();

        if (c == KEY_UP && cursor_pos > 0) {
            cursorupward(1);
            cursor_pos--;
        }
        else if(c == KEY_DOWN && cursor_pos < no_of_entries - 1) {
            cursordownward(1);
            cursor_pos++;
        }
        else if(c == KEY_ENTER) {
            //tcsetattr (STDIN_FILENO, TCSAFLUSH, &initial_settings);
            char new_directory[MAX];
            strcpy(new_directory, curr_dir);
            strcat(new_directory, "/");
            strcat(new_directory, file_details[cursor_pos].name);
            curr_dir = new_directory;
            clrscrn();
            file_details = list_directory(curr_dir);
            no_of_entries = file_details.size();
            //cout << file_details.size() <<"\n";
            printf("\033[%dA", no_of_entries);
            cursor_pos = 0;
            continue;

        }

    }
    return 0;
}