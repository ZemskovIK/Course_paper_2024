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
//        std::cout << "���: " << student.GetLastName() << " " << student.GetFirstName() << " " << student.GetPatronymic() << "\n";
//        std::cout << "���� ��������: " << student.GetDay() << "." << student.GetMonth() << "." << student.GetYear() << "\n";
//        std::cout << "��� �����������: " << student.GetAdmissionYear() << "\n";
//        std::cout << "���������: " << student.GetFaculty() << "\n";
//        std::cout << "�������: " << student.GetDepartment() << "\n";
//        std::cout << "������: " << student.GetGroup() << "\n";
//        std::cout << "����� �������� ������: " << student.GetRecordBookNumber() << "\n";
//        std::cout << "���: " << student.GetGender() << "\n\n";
//    }
//    system("pause");
//}

//void AddStudent(Database& db) {
//    system("CLS");
//    std::string lastName, firstName, patronymic, faculty, department, group, recordBookNumber, gender;
//    int day, month, year, admissionYear;
//
//    std::cout << "������� �������: ";
//    std::cin >> lastName;
//    std::cout << "������� ���: ";
//    std::cin >> firstName;
//    std::cout << "������� ��������: ";
//    std::cin >> patronymic;
//    std::cout << "������� ���� ��������: ";
//    std::cin >> day;
//    std::cout << "������� ����� ��������: ";
//    std::cin >> month;
//    std::cout << "������� ��� ��������: ";
//    std::cin >> year;
//    std::cout << "������� ��� �����������: ";
//    std::cin >> admissionYear;
//    std::cout << "������� ���������: ";
//    std::cin >> faculty;
//    std::cout << "������� �������: ";
//    std::cin >> department;
//    std::cout << "������� ������: ";
//    std::cin >> group;
//    std::cout << "������� ����� �������� ������: ";
//    std::cin >> recordBookNumber;
//    std::cout << "������� ���: ";
//    std::cin >> gender;
//
//    Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);
//    db.AddStudent(student);
//    std::cout << "������� ��������.\n";
//    system("pause");
//}

//void SaveDatabase(Database& db) {
//    system("CLS");
//    db.SaveToFile("students.txt");
//    std::cout << "���� ������ ���������.\n";
//    system("pause");
//}

//void LoadDatabase(Database& db) {
//    system("CLS");
//    db.LoadFromFile("students.txt");
//    //system("CLS");
//    std::cout << "���� ������ ���������.\n";
//    system("pause");
//}

//void SelectStudent(Database& db) {
//    system("CLS");
//    const auto& students = db.GetStudents();
//    if (students.empty()) {
//        std::cout << "��� ��������� � ���� ������.\n";
//        system("pause");
//        return;
//    }
//
//    std::cout << "������� ����� �������� ������ ��������: ";
//    std::string recordBookNumber;
//    std::cin >> recordBookNumber;
//
//    Student* student = db.GetStudentByRecordBookNumber(recordBookNumber);
//    if (!student) {
//        std::cout << "������� � ����� ������� �������� ������ �� ������.\n";
//        system("pause");
//        return;
//    }
//
//    std::vector<std::string> subMenuItems = { "����������� ������", "���������� ������", "�������� ������", "������� ��������", "�����" };
//    Menu subMenu(subMenuItems);
//
//    while (true) {
//        system("CLS");
//        subMenu.Display();
//        int subChoice = subMenu.HandleInput();
//
//        switch (subChoice) {
//        case 0: { // ����������� ������
//            system("CLS");
//            for (int semester = 1; semester <= 9; ++semester) {
//                const auto& grades = student->GetGrades(semester);
//                if (!grades.empty()) {
//                    std::cout << "������� " << semester << ":\n";
//                    for (const auto& [subject, grade] : grades) {
//                        std::cout << subject << ": " << grade << "\n";
//                    }
//                    std::cout << "\n";
//                }
//            }
//            system("pause");
//            break;
//        }
//        case 1: { // ���������� ������
//            system("CLS");
//            int semester;
//            std::string subject, grade;
//
//            std::cout << "������� ����� ��������: ";
//            std::cin >> semester;
//            std::cout << "������� �������: ";
//            std::cin.ignore(80, '\n');
//            std::getline(std::cin, subject);
//            std::cout << "������� ������: ";
//            std::cin >> grade;
//
//            student->SetGrade(semester, subject, grade);
//            std::cout << "������ ���������.\n";
//            system("pause");
//            break;
//        }
//        case 2: { // �������� ������
//            system("CLS");
//            std::string lastName, firstName, patronymic, faculty, department, group, gender;
//            int day, month, year, admissionYear;
//
//            std::cout << "������� �������: ";
//            std::cin >> lastName;
//            std::cout << "������� ���: ";
//            std::cin >> firstName;
//            std::cout << "������� ��������: ";
//            std::cin >> patronymic;
//            std::cout << "������� ���� ��������: ";
//            std::cin >> day;
//            std::cout << "������� ����� ��������: ";
//            std::cin >> month;
//            std::cout << "������� ��� ��������: ";
//            std::cin >> year;
//            std::cout << "������� ��� �����������: ";
//            std::cin >> admissionYear;
//            std::cout << "������� ���������: ";
//            std::cin >> faculty;
//            std::cout << "������� �������: ";
//            std::cin >> department;
//            std::cout << "������� ������: ";
//            std::cin >> group;
//            std::cout << "������� ���: ";
//            std::cin >> gender;
//
//            student->UpdateData(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, gender);
//            std::cout << "������ �������� ���������.\n";
//            system("pause");
//            break;
//        }
//        case 3: { // ������� ��������
//            system("CLS");
//            if (db.DeleteStudent(recordBookNumber)) {
//                std::cout << "������� ������.\n";
//                system("pause");
//                return; // ������������ � ������� ����
//            }
//            else {
//                std::cout << "������ ��� �������� ��������.\n";
//                system("pause");
//            }
//            break;
//        }
//        case 4: // �����
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
