//
// Created by vivek on 24/8/18.
//

#include <string.h>
#include <string>
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
#include "global_variables.h"
using namespace std;

#ifndef OS_ASSIGNMENT_LIST_DIRECTORY_H

vector<file_detail> list_directory(char*);

void list(vector<file_detail>);

#define OS_ASSIGNMENT_LIST_DIRECTORY_H

#endif //OS_ASSIGNMENT_LIST_DIRECTORY_H
