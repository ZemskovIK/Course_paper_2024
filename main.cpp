#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include "Menu.h"
#include "Database.h"

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� �������

void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // �������� ��������� �������
    structCursorInfo.dwSize = size; // �������� ������ �������
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void DisplayStudents(const Database& db) {
    system("CLS");
    const auto& students = db.GetStudents();
    for (const auto& student : students) {
        std::cout << "���: " << student.GetLastName() << " " << student.GetFirstName() << " " << student.GetPatronymic() << "\n";
        std::cout << "���� ��������: " << student.GetDay() << "." << student.GetMonth() << "." << student.GetYear() << "\n";
        std::cout << "��� �����������: " << student.GetAdmissionYear() << "\n";
        std::cout << "���������: " << student.GetFaculty() << "\n";
        std::cout << "�������: " << student.GetDepartment() << "\n";
        std::cout << "������: " << student.GetGroup() << "\n";
        std::cout << "����� �������� ������: " << student.GetRecordBookNumber() << "\n";
        std::cout << "���: " << student.GetGender() << "\n\n";
    }
    system("pause");
}

void AddStudent(Database& db) {
    system("CLS");
    std::string lastName, firstName, patronymic, faculty, department, group, recordBookNumber, gender;
    int day, month, year, admissionYear;

    std::cout << "������� �������: ";
    std::cin >> lastName;
    std::cout << "������� ���: ";
    std::cin >> firstName;
    std::cout << "������� ��������: ";
    std::cin >> patronymic;
    std::cout << "������� ���� ��������: ";
    std::cin >> day;
    std::cout << "������� ����� ��������: ";
    std::cin >> month;
    std::cout << "������� ��� ��������: ";
    std::cin >> year;
    std::cout << "������� ��� �����������: ";
    std::cin >> admissionYear;
    std::cout << "������� ���������: ";
    std::cin >> faculty;
    std::cout << "������� �������: ";
    std::cin >> department;
    std::cout << "������� ������: ";
    std::cin >> group;
    std::cout << "������� ����� �������� ������: ";
    std::cin >> recordBookNumber;
    std::cout << "������� ���: ";
    std::cin >> gender;

    Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);
    db.AddStudent(student);
    std::cout << "������� ��������.\n";
    system("pause");
}

void SaveDatabase(Database& db) {
    system("CLS");
    db.SaveToFile("students.txt");
    std::cout << "���� ������ ���������.\n";
    system("pause");
}

void LoadDatabase(Database& db) {
    db.LoadFromFile("students.txt");
    system("CLS");
    std::cout << "���� ������ ���������.\n";
    system("pause");
}

int main() {
    SetConsoleTitle(L"�������� ������ �� ��");
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("CLS");
    ConsoleCursorVisible(false, 100);

    Database db;
    std::vector<std::string> menuItems = { "������ ���������", "�������� ��������", "��������� ����", "��������� ����", "�����" };
    Menu menu(menuItems);

    while (true) {
        system("CLS");
        menu.Display();
        int choice = menu.HandleInput();

        switch (choice) {
        case 0:
            DisplayStudents(db);
            break;
        case 1:
            AddStudent(db);
            break;
        case 2:
            SaveDatabase(db);
            break;
        case 3:
            LoadDatabase(db);
            break;
        case 4:
            return 0;   
        }
    }

    return 0;
}
