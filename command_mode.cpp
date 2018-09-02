//
// Created by vivek on 31/8/18.
//

#include "raw_input.h"
#include "global_variables.h"
#include "command_exec.h"
#include "list_directory.h"

#define MAX 1000

void clrline() {
    printf("\033[2K");
}


void command_mode() {

    char command_in[MAX];       //command is stored
    int ans;
    index1 = 0;
    command_in[index1] = '\0';
    while(1) {
        //printf("%d", index);
        int c = kbget();
        if(c == KEY_ESCAPE) {
            mode = 0;
            break;
        }
        if(c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP || c == KEY_DOWN) {
            continue;
        }
        if(c == 127) {
            backspace_pressed = 1;
            index1 = 0;
            command_in[index1] = '\0';
            //printf("%s ", command_in);
            clrline();
            printf("\r");
            printf(":");
        }
        if(c == KEY_ENTER) {
            char passed[1000];
            //printf("here");
            strcpy(passed, command_in);
            //printf("%s", passed);
            ans = command_exec(passed);

            if(ans == 1) {
                clrline();
                //printf(":");
                printf("\r");
                //printf(":");
                printf("(command executed):");
                index1 = 0;
            }
            else if(ans == 0){
                clrline();
                printf("\r");
                printf("(wrong command or path type again):");
                index1 = 0;
            }
            else if(ans == 2) {
                mode = 0;
                break;
            }
        }
        else {
            putchar(c);
            command_in[index1] = c;
            index1++;
            command_in[index1] = '\0';
        }

    }
    printf("\033c");
    vector<file_detail>file_names;
    file_names = list_directory(curr_dir);
    if(ans == 2)
        left_st.push(curr_dir);
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


}
