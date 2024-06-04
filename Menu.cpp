#include "Menu.h"
#include <conio.h>
#include <iostream>

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13

Menu::Menu(const std::vector<std::string>& items) : items(items), activeItem(0) {
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void GoToXY(short x, short y) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void DrawBox(int x, int y, int width, int height) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    GoToXY(x, y); std::cout << "+"; // Верхний левый угол
    for (int i = 0; i < width - 2; ++i) std::cout << "-"; // Верхняя граница
    std::cout << "+"; // Верхний правый угол

    for (int i = 1; i < height - 1; ++i) {
        GoToXY(x, y + i); std::cout << "|"; // Левая граница
        GoToXY(x + width - 1, y + i); std::cout << "|"; // Правая граница
    }

    GoToXY(x, y + height - 1); std::cout << "+"; // Нижний левый угол
    for (int i = 0; i < width - 2; ++i) std::cout << "-"; // Нижняя граница
    std::cout << "+"; // Нижний правый угол
}

void Menu::Display() const {
    int x = 50, y = 10;
    int width = 25, height = static_cast<int>(items.size()) + 4;

    // Рисуем рамку
    DrawBox(x - 2, y - 2, width, height);

    // Заголовок меню
    GoToXY(x, y - 1);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << "      М Е Н Ю  ";

    // Отображение пунктов меню
    for (size_t i = 0; i < items.size(); ++i) {
        GoToXY(x, y + i);
        if (i == activeItem)
            SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else
            SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << items[i];
    }
}

int Menu::HandleInput() {
    while (true) {
        char ch = _getch();
        if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
        switch (ch) {
        case ESC:
            exit(0);
            break;
        case UP:
            if (activeItem > 0)
                --activeItem;
            else
                activeItem = static_cast<int>(items.size()) - 1;
            Display();
            break;
        case DOWN:
            if (activeItem < static_cast<int>(items.size()) - 1)
                ++activeItem;
            else
                activeItem = 0;
            Display();
            break;
        case ENTER:
            return activeItem;
        }
    }
}
