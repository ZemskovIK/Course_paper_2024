#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

// ���������� ����������� �����������
extern HANDLE hStdOut;

// �������� �������
void ConsoleCursorVisible(bool visible, short size = 10);
void GoToXY(short x, short y);

#endif // CONSOLE_UTILS_H
