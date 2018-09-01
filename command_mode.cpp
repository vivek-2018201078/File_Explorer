//
// Created by vivek on 31/8/18.
//

#include "raw_input.h"
#include "global_variables.h"
#include "command_exec.h"
#define MAX 1000

void clrline() {
    printf("\033[2K");
}

void command_mode() {

    char command_in[MAX];       //command is stored
    int ans;
    index1 = 0;
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
            index1 = 0;
            command_in[index1] = '\0';
            clrline();
            printf("\r");
            printf(":");
        }
        if(c == KEY_ENTER) {
            char passed[1000];
            //printf("here");
            strcpy(passed, command_in);
            ans = command_exec(passed);
            if(ans == 1) {
                clrline();
                //printf(":");
                printf("\r");
                //printf(":");
                printf("(command executed):");
                //mode = 0;
                //break;
                //break;
                index1 = 0;
                //command_in[index] = '\0';
            }
            else if(ans == 0){
                clrline();
                printf("\r");
                //printf("%s", command_in);
                printf("(wrong command or path type again):");
                index1 = 0;
                //command_in[index] = '\0';
            }
            //printf("%d", ans);
        }
        else {
            putchar(c);
            command_in[index1] = c;
            index1++;
            command_in[index1] = '\0';
            //printf(" %s",command_in);
        }

    }
    clrline();
    //printf("%d", ans);
    //printf("%s", command_in);
    printf("\r");
    printf("------NORMAL MODE------");
    printf("\r");
    //printf("cursor line = %d", cursor_line);
    cursorupward(terminal_lines);
    if(cursor_line != 0)
        cursordownward(cursor_line);

}
