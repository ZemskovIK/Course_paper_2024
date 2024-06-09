#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

// ќбъ€вление глобального дескриптора
extern HANDLE hStdOut;

// ќписание функций
void ConsoleCursorVisible(bool visible, short size = 10);
void GoToXY(short x, short y);

#endif // CONSOLE_UTILS_H
