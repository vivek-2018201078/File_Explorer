//
// Created by vivek on 31/8/18.
//

#include "raw_input.h"
#include "global_variables.h"

void clrline() {
    printf("\033[2K");
}

void command_mode() {
    while(1) {
        int c = kbget();
        if(c == KEY_ESCAPE) {
            mode = 0;
            break;
        }
        else if(c == KEY_BACKSPACE || c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP || c == KEY_DOWN) {
            continue;
        } else {
            putchar(c);
        }
    }
    clrline();
    printf("\r");
    printf("------NORMAL MODE------");
    printf("\r");
    cursorupward(terminal_lines);
    cursordownward(cursor_line);

}
