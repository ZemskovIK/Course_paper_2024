#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <windows.h>

//HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

//void GoToXY(short x, short y) {
//    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hStdOut, { x, y });
//}

//void ConsoleCursorVisible(bool show, short size) {
//    CONSOLE_CURSOR_INFO structCursorInfo;
//    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
//    structCursorInfo.bVisible = show;
//    structCursorInfo.dwSize = size;
//    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
//}

class Menu {
private:
    std::vector<std::string> items;
    int activeItem;
    HANDLE hStdOut;

public:
    Menu(const std::vector<std::string>& items);
    void Display() const;
    int HandleInput();
};

#endif
