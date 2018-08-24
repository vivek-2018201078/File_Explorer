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

using namespace std;

struct termios new_settings, initial_settings;

static int getch(void) {
    int c = 0;

    tcgetattr(0, &initial_settings);
    memcpy(&new_settings, &initial_settings, sizeof(new_settings));
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &new_settings);
    c = getchar();
    tcsetattr(0, TCSANOW, &initial_settings);
    return c;
}

int main()
{
    printf("\033c");
    int no_of_entries;
    string pathname = ".";
    no_of_entries =  list_directory(pathname);
    printf("\033[%dA", no_of_entries);

    int c, c2, c3;
    int cursor_pos = 0;
    while(1) {
        //     tcsetattr(0, TCSANOW, &new_settings);

        c = getch();
        if (c == 27) {
            c2 = getch();
            if(c2 == 91) {
                c3 = getch();
                if(c3 == 65 && cursor_pos > 0) {
                    printf("\033[%dA", (1));
                    cursor_pos--;
                    //tcsetattr(0, TCSANOW, &new_settings);
                }
                else if(c3 == 66 && cursor_pos < no_of_entries - 1) {
                    printf("\033[%dB", (1));
                    cursor_pos++;
                    //tcsetattr(0, TCSANOW, &new_settings);
                }

            }
        }

        else if(c =='q') {
            tcsetattr (STDIN_FILENO, TCSAFLUSH, &initial_settings);
            break;
        }

    }
    return 0;
}