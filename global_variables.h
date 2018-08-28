//
// Created by vivek on 25/8/18.
//
#include <termios.h>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

#ifndef OS_ASSIGNMENT_GLOBAL_VARIABLES_H
#define OS_ASSIGNMENT_GLOBAL_VARIABLES_H

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
extern char* home_dir;


#endif //OS_ASSIGNMENT_GLOBAL_VARIABLES_H
