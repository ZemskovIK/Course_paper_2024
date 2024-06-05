#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include "Menu.h"
#include "Database.h"
#include "crypter.h"

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Crypter crypter;
    Database db;
    crypter.Decrypt();
    std::cout << "БД расшифрована!\n";
    system("pause");
    db.run();    
    crypter.Crypt();
    std::cout << "БД зашифрована!\n";

    return 0;
}
