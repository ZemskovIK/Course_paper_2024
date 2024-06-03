#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <windows.h>

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
