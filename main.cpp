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

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли

void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // изменяем видимость курсора
    structCursorInfo.dwSize = size; // изменяем размер курсора
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void DisplayStudents(const Database& db) {
    system("CLS");
    const auto& students = db.GetStudents();
    for (const auto& student : students) {
        std::cout << "ФИО: " << student.GetLastName() << " " << student.GetFirstName() << " " << student.GetPatronymic() << "\n";
        std::cout << "Дата рождения: " << student.GetDay() << "." << student.GetMonth() << "." << student.GetYear() << "\n";
        std::cout << "Год поступления: " << student.GetAdmissionYear() << "\n";
        std::cout << "Факультет: " << student.GetFaculty() << "\n";
        std::cout << "Кафедра: " << student.GetDepartment() << "\n";
        std::cout << "Группа: " << student.GetGroup() << "\n";
        std::cout << "Номер зачетной книжки: " << student.GetRecordBookNumber() << "\n";
        std::cout << "Пол: " << student.GetGender() << "\n\n";
    }
    system("pause");
}

void AddStudent(Database& db) {
    system("CLS");
    std::string lastName, firstName, patronymic, faculty, department, group, recordBookNumber, gender;
    int day, month, year, admissionYear;

    std::cout << "Введите фамилию: ";
    std::cin >> lastName;
    std::cout << "Введите имя: ";
    std::cin >> firstName;
    std::cout << "Введите отчество: ";
    std::cin >> patronymic;
    std::cout << "Введите день рождения: ";
    std::cin >> day;
    std::cout << "Введите месяц рождения: ";
    std::cin >> month;
    std::cout << "Введите год рождения: ";
    std::cin >> year;
    std::cout << "Введите год поступления: ";
    std::cin >> admissionYear;
    std::cout << "Введите факультет: ";
    std::cin >> faculty;
    std::cout << "Введите кафедру: ";
    std::cin >> department;
    std::cout << "Введите группу: ";
    std::cin >> group;
    std::cout << "Введите номер зачетной книжки: ";
    std::cin >> recordBookNumber;
    std::cout << "Введите пол: ";
    std::cin >> gender;

    Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);
    db.AddStudent(student);
    std::cout << "Студент добавлен.\n";
    system("pause");
}

void SaveDatabase(Database& db) {
    system("CLS");
    db.SaveToFile("students.txt");
    std::cout << "База данных сохранена.\n";
    system("pause");
}

void LoadDatabase(Database& db) {
    db.LoadFromFile("students.txt");
    system("CLS");
    std::cout << "База данных загружена.\n";
    system("pause");
}

int main() {
    SetConsoleTitle(L"Курсовая работа по ЯП");
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("CLS");
    ConsoleCursorVisible(false, 100);

    Database db;
    std::vector<std::string> menuItems = { "Список студентов", "Добавить студента", "Сохранить базу", "Загрузить базу", "Выход" };
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
