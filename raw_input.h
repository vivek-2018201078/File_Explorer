//
// Created by vivek on 25/8/18.
//
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))
#define cursorupward(x) printf("\033[%dA", (x))
#define cursordownward(x) printf("\033[%dB", (x))

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108
#define KEY_BACKSPACE 0X0008

int getch(void);
int kbhit(void);
int kbesc(void);
int kbget(void);

#ifndef OS_ASSIGNMENT_RAW_INPUT_H
#define OS_ASSIGNMENT_RAW_INPUT_H

#endif //OS_ASSIGNMENT_RAW_INPUT_H
