#include "ConsoleUtils.h"

// ����������� ����������� �����������
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// ����������� ������� ��� ��������� ��������� �������
void ConsoleCursorVisible(bool visible, short size) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = visible;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
}

// ����������� ������� ��� ��������� ��������� �������
void GoToXY(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(hStdOut, pos);
}
