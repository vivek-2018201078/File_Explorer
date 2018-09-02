//
// Created by vivek on 25/8/18.
//
#include <termios.h>
#include <string>
#include <string.h>
#include <vector>
#include <sys/ioctl.h>
#include <stack>


using namespace std;

#ifndef OS_ASSIGNMENT_GLOBAL_VARIABLES_H
#define OS_ASSIGNMENT_GLOBAL_VARIABLES_H

extern const int total_no_of_possible_lines;
extern struct termios new_settings, initial_settings;
extern int cursor_pos;
extern char* curr_dir;
extern int left_key_access;
extern int right_key_access;
typedef struct file_detail_struc {
    char* name;
    int index;
    int isdir;
}file_detail;
extern int path_history_index;
extern int mode;                 //mode 0 = normal mode, mode 1 = command mode;
extern char* home_dir;
extern int left_file_index;      //start of scrolling file
extern int right_file_index;     //end of scrolling
extern int no_of_entries;
extern int terminal_lines;
extern int terminal_col;
extern int cursor_line;
extern char* absolute_home_path;
extern int index1;
extern stack <char*> left_st;
extern stack <char*> right_st;
extern int backspace_pressed;


#endif //OS_ASSIGNMENT_GLOBAL_VARIABLES_H
