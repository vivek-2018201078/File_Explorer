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
    int index = 0;             // index to monitor command line input
    int ans;
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
            index = 0;
            //command_in[index] = '\0';
            clrline();
            printf("\r");
            printf(":");
        }
        if(c == KEY_ENTER) {
            ans = command_exec(command_in);
            if(ans == 1) {
                clrline();
                //printf(":");
                printf("\r");
                //printf(":");
                printf("(command executed):");
                //mode = 0;
                //break;
                //break;
                index = 0;
                //command_in[index] = '\0';
            }
            else if(ans == 0){
                clrline();
                printf("\r");
                printf("(wrong command or path type again):");
                index = 0;
                //command_in[index] = '\0';
            }
            //printf("%d", ans);
        }
        else {
            putchar(c);
            command_in[index] = c;
            index++;
            command_in[index] = '\0';
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
