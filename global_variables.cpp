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
int left_key_access = 0;
int right_key_access = 0;
const int total_no_of_possible_lines = 34;
int left_file_index = 0;
int right_file_index = 34;
int no_of_entries = 0;
int mode = 0;
int terminal_lines;
int terminal_col;
int cursor_line = 0;

