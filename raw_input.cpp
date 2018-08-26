//
// Created by vivek on 25/8/18.
//
#include "global_variables.h"
#include "raw_input.h"

int getch(void)
{
    int c = 0;

    tcgetattr(0, &initial_settings);
    memcpy(&new_settings, &initial_settings, sizeof(new_settings));
    new_settings.c_lflag &= ~(ICANON | ECHO);
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    c = getchar();
    tcsetattr(0, TCSANOW, &initial_settings);
    return c;
}

int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &initial_settings);
    memcpy(&new_settings, &initial_settings, sizeof(new_settings));
    new_settings.c_lflag &= ~(ICANON | ECHO);
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
    c = getchar();
    tcsetattr(0, TCSANOW, &initial_settings);
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

int kbesc(void)
{
    int c;

    if (!kbhit()) return KEY_ESCAPE;
    c = getch();
    if (c == '[') {
        switch (getch()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_LEFT;
                break;
            case 'D':
                c = KEY_RIGHT;
                break;
            default:
                c = 0;
                break;
        }
    } else {
        c = 0;
    }
    if (c == 0) while (kbhit()) getch();
    return c;
}

int kbget(void)
{
    int c;

    c = getch();
    if(c == 127) {
        return c;

    }
    return (c == KEY_ESCAPE) ? kbesc() : c;
}

