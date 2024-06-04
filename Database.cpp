#include "Database.h"
#include "Menu.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Database::Database() {}

void Database::run() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = false;
    structCursorInfo.dwSize = 10;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    std::vector<std::string> menuItems = { "Показать студентов", "Добавить студента", "Загрузить базу данных", "Сохранить базу данных", "Выбрать студента", "Выход" };
    Menu menu(menuItems);
    while (true) {
        system("CLS");
        menu.Display();
        int choice = menu.HandleInput();

        switch (choice) {
        case 0:
            this->DisplayStudents();
            break;
        case 1:
            this->AddStudent();
            break;
        case 2:
            this->LoadFromFile("students.txt");
            break;
        case 3:
            this->SaveToFile("students.txt");
            break;
        case 4:
            this->SelectStudent();
            break;
        case 5:
            return;
        }
    }
}

void Database::DisplayStudents() {
    system("CLS");
    const auto& students = this->GetStudents();
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

void Database::AddStudent() {
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
    students.push_back(student);
    std::cout << "Студент добавлен.\n";
    system("pause");

}

void Database::SelectStudent() {
    system("CLS");
    const auto& students = this->GetStudents();
    if (students.empty()) {
        std::cout << "Нет студентов в базе данных.\n";
        system("pause");
        return;
    }

    std::cout << "Введите номер зачетной книжки студента: ";
    std::string recordBookNumber;
    std::cin >> recordBookNumber;

    Student* student = this->GetStudentByRecordBookNumber(recordBookNumber);
    if (!student) {
        std::cout << "Студент с таким номером зачетной книжки не найден.\n";
        system("pause");
        return;
    }

    std::vector<std::string> subMenuItems = { "Просмотреть оценки", "Проставить оценку", "Изменить данные", "Удалить студента", "Назад" };
    Menu subMenu(subMenuItems);

    while (true) {
        system("CLS");
        subMenu.Display();
        int subChoice = subMenu.HandleInput();

        switch (subChoice) {
        case 0: { // Просмотреть оценки
            system("CLS");
            for (int semester = 1; semester <= 9; ++semester) {
                const auto& grades = student->GetGrades(semester);
                if (!grades.empty()) {
                    std::cout << "Семестр " << semester << ":\n";
                    for (const auto& [subject, grade] : grades) {
                        std::cout << subject << ": " << grade << "\n";
                    }
                    std::cout << "\n";
                }
            }
            system("pause");
            break;
        }
        case 1: { // Проставить оценку
            system("CLS");
            int semester;
            std::string subject, grade;

            std::cout << "Введите номер семестра: ";
            std::cin >> semester;
            std::cout << "Введите предмет: ";
            std::cin.ignore(80, '\n');
            std::getline(std::cin, subject);
            std::cout << "Введите оценку: ";
            std::cin >> grade;

            student->SetGrade(semester, subject, grade);
            std::cout << "Оценка добавлена.\n";
            system("pause");
            break;
        }
        case 2: { // Изменить данные
            system("CLS");
            std::string lastName, firstName, patronymic, faculty, department, group, gender;
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
            std::cout << "Введите пол: ";
            std::cin >> gender;

            student->UpdateData(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, gender);
            std::cout << "Данные студента обновлены.\n";
            system("pause");
            break;
        }
        case 3: { // Удалить студента
            system("CLS");
            if (this->DeleteStudent(recordBookNumber)) {
                std::cout << "Студент отчислен.\n";
                system("pause");
                return; // Возвращаемся в главное меню
            }
            else {
                std::cout << "Ошибка при удалении студента.\n";
                system("pause");
            }
            break;
        }
        case 4: // Назад
            this->run();
        }
    }
}

void Database::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& student : students) {
            file << student.GetLastName() << " "
                << student.GetFirstName() << " "
                << student.GetPatronymic() << " "
                << student.GetDay() << " "
                << student.GetMonth() << " "
                << student.GetYear() << " "
                << student.GetAdmissionYear() << " "
                << student.GetFaculty() << " "
                << student.GetDepartment() << " "
                << student.GetGroup() << " "
                << student.GetRecordBookNumber() << " "
                << student.GetGender() << "\n";

            for (int semester = 1; semester <= 9; ++semester) {
                const auto& grades = student.GetGrades(semester);
                if (!grades.empty()) {
                    file << semester;
                    for (const auto& [subject, grade] : grades) {
                        file << " " << subject << ":" << grade;
                    }
                    file << "\n";
                }
            }
        }
        file.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для записи.\n";
    }
    system("CLS");
    std::cout << "База данных сохранена.\n";
    system("pause");
}

void Database::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        students.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string lastName, firstName, patronymic, faculty, department, group, recordBookNumber, gender;
            int day, month, year, admissionYear;

            iss >> lastName >> firstName >> patronymic >> day >> month >> year >> admissionYear >> faculty >> department >> group >> recordBookNumber >> gender;

            Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);

            /*std::string line2;
            while (std::getline(file, line2) && !line2.empty()) {
                std::istringstream gradeStream(line2);
                int semester;
                gradeStream >> semester;

                std::string gradePair;
                while (gradeStream >> gradePair) {
                    auto pos = gradePair.find(':');
                    std::string subject = gradePair.substr(0, pos);
                    std::string grade = gradePair.substr(pos + 1);
                    student.SetGrade(semester, subject, grade);
                }
            }*/
            students.push_back(student);
        }
        file.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения.\n";
    }
    system("CLS");
    std::cout << "База данных загружена.\n";
    system("pause");
}

const std::vector<Student>& Database::GetStudents() const {
    return students;
}

Student* Database::GetStudentByRecordBookNumber(const std::string& recordBookNumber) {
    auto it = std::find_if(students.begin(), students.end(), [&recordBookNumber](const Student& student) {
        return student.GetRecordBookNumber() == recordBookNumber;
        });

    return it != students.end() ? &(*it) : nullptr;
}

bool Database::DeleteStudent(const std::string& recordBookNumber) {
    auto it = std::remove_if(students.begin(), students.end(), [&recordBookNumber](const Student& student) {
        return student.GetRecordBookNumber() == recordBookNumber;
        });

    if (it != students.end()) {
        students.erase(it, students.end());
        return true;
    }
    return false;
}
