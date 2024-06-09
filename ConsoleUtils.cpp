#include "ConsoleUtils.h"

// Определение глобального дескриптора
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Определение функции для изменения видимости курсора
void ConsoleCursorVisible(bool visible, short size) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = visible;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
}

// Определение функции для установки положения курсора
void GoToXY(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(hStdOut, pos);
}
