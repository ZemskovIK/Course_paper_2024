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

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

//void DisplayStudents(const Database& db) {
//    system("CLS");
//    const auto& students = db.GetStudents();
//    for (const auto& student : students) {
//        std::cout << "ФИО: " << student.GetLastName() << " " << student.GetFirstName() << " " << student.GetPatronymic() << "\n";
//        std::cout << "Дата рождения: " << student.GetDay() << "." << student.GetMonth() << "." << student.GetYear() << "\n";
//        std::cout << "Год поступления: " << student.GetAdmissionYear() << "\n";
//        std::cout << "Факультет: " << student.GetFaculty() << "\n";
//        std::cout << "Кафедра: " << student.GetDepartment() << "\n";
//        std::cout << "Группа: " << student.GetGroup() << "\n";
//        std::cout << "Номер зачетной книжки: " << student.GetRecordBookNumber() << "\n";
//        std::cout << "Пол: " << student.GetGender() << "\n\n";
//    }
//    system("pause");
//}

//void AddStudent(Database& db) {
//    system("CLS");
//    std::string lastName, firstName, patronymic, faculty, department, group, recordBookNumber, gender;
//    int day, month, year, admissionYear;
//
//    std::cout << "Введите фамилию: ";
//    std::cin >> lastName;
//    std::cout << "Введите имя: ";
//    std::cin >> firstName;
//    std::cout << "Введите отчество: ";
//    std::cin >> patronymic;
//    std::cout << "Введите день рождения: ";
//    std::cin >> day;
//    std::cout << "Введите месяц рождения: ";
//    std::cin >> month;
//    std::cout << "Введите год рождения: ";
//    std::cin >> year;
//    std::cout << "Введите год поступления: ";
//    std::cin >> admissionYear;
//    std::cout << "Введите факультет: ";
//    std::cin >> faculty;
//    std::cout << "Введите кафедру: ";
//    std::cin >> department;
//    std::cout << "Введите группу: ";
//    std::cin >> group;
//    std::cout << "Введите номер зачетной книжки: ";
//    std::cin >> recordBookNumber;
//    std::cout << "Введите пол: ";
//    std::cin >> gender;
//
//    Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);
//    db.AddStudent(student);
//    std::cout << "Студент добавлен.\n";
//    system("pause");
//}

//void SaveDatabase(Database& db) {
//    system("CLS");
//    db.SaveToFile("students.txt");
//    std::cout << "База данных сохранена.\n";
//    system("pause");
//}

//void LoadDatabase(Database& db) {
//    system("CLS");
//    db.LoadFromFile("students.txt");
//    //system("CLS");
//    std::cout << "База данных загружена.\n";
//    system("pause");
//}

//void SelectStudent(Database& db) {
//    system("CLS");
//    const auto& students = db.GetStudents();
//    if (students.empty()) {
//        std::cout << "Нет студентов в базе данных.\n";
//        system("pause");
//        return;
//    }
//
//    std::cout << "Введите номер зачетной книжки студента: ";
//    std::string recordBookNumber;
//    std::cin >> recordBookNumber;
//
//    Student* student = db.GetStudentByRecordBookNumber(recordBookNumber);
//    if (!student) {
//        std::cout << "Студент с таким номером зачетной книжки не найден.\n";
//        system("pause");
//        return;
//    }
//
//    std::vector<std::string> subMenuItems = { "Просмотреть оценки", "Проставить оценку", "Изменить данные", "Удалить студента", "Назад" };
//    Menu subMenu(subMenuItems);
//
//    while (true) {
//        system("CLS");
//        subMenu.Display();
//        int subChoice = subMenu.HandleInput();
//
//        switch (subChoice) {
//        case 0: { // Просмотреть оценки
//            system("CLS");
//            for (int semester = 1; semester <= 9; ++semester) {
//                const auto& grades = student->GetGrades(semester);
//                if (!grades.empty()) {
//                    std::cout << "Семестр " << semester << ":\n";
//                    for (const auto& [subject, grade] : grades) {
//                        std::cout << subject << ": " << grade << "\n";
//                    }
//                    std::cout << "\n";
//                }
//            }
//            system("pause");
//            break;
//        }
//        case 1: { // Проставить оценку
//            system("CLS");
//            int semester;
//            std::string subject, grade;
//
//            std::cout << "Введите номер семестра: ";
//            std::cin >> semester;
//            std::cout << "Введите предмет: ";
//            std::cin.ignore(80, '\n');
//            std::getline(std::cin, subject);
//            std::cout << "Введите оценку: ";
//            std::cin >> grade;
//
//            student->SetGrade(semester, subject, grade);
//            std::cout << "Оценка добавлена.\n";
//            system("pause");
//            break;
//        }
//        case 2: { // Изменить данные
//            system("CLS");
//            std::string lastName, firstName, patronymic, faculty, department, group, gender;
//            int day, month, year, admissionYear;
//
//            std::cout << "Введите фамилию: ";
//            std::cin >> lastName;
//            std::cout << "Введите имя: ";
//            std::cin >> firstName;
//            std::cout << "Введите отчество: ";
//            std::cin >> patronymic;
//            std::cout << "Введите день рождения: ";
//            std::cin >> day;
//            std::cout << "Введите месяц рождения: ";
//            std::cin >> month;
//            std::cout << "Введите год рождения: ";
//            std::cin >> year;
//            std::cout << "Введите год поступления: ";
//            std::cin >> admissionYear;
//            std::cout << "Введите факультет: ";
//            std::cin >> faculty;
//            std::cout << "Введите кафедру: ";
//            std::cin >> department;
//            std::cout << "Введите группу: ";
//            std::cin >> group;
//            std::cout << "Введите пол: ";
//            std::cin >> gender;
//
//            student->UpdateData(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, gender);
//            std::cout << "Данные студента обновлены.\n";
//            system("pause");
//            break;
//        }
//        case 3: { // Удалить студента
//            system("CLS");
//            if (db.DeleteStudent(recordBookNumber)) {
//                std::cout << "Студент удален.\n";
//                system("pause");
//                return; // Возвращаемся в главное меню
//            }
//            else {
//                std::cout << "Ошибка при удалении студента.\n";
//                system("pause");
//            }
//            break;
//        }
//        case 4: // Назад
//            run(db);
//        }
//    }
//}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Database db;
    db.run();
    

    return 0;
}
