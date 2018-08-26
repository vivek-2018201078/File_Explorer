//
// Created by vivek on 25/8/18.
//
#include "global_variables.h"
#include <vector>

using namespace std;

struct termios new_settings, initial_settings;
int cursor_pos = 0;
char* curr_dir = ".";
int path_history_index = 0;
char* home_dir = ".";