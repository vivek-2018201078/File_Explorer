//
// Created by vivek on 25/8/18.
//
#include <termios.h>
#include <string>
#include <string.h>
using namespace std;

#ifndef OS_ASSIGNMENT_GLOBAL_VARIABLES_H
#define OS_ASSIGNMENT_GLOBAL_VARIABLES_H

extern struct termios new_settings, initial_settings;
extern int cursor_pos;
extern char* curr_dir;
typedef struct file_detail_struc {
    char* name;
    int index;
    int isdir;
}file_detail;


#endif //OS_ASSIGNMENT_GLOBAL_VARIABLES_H
