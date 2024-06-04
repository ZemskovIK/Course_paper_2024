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

    std::vector<std::string> menuItems = { "Показать студентов", "Добавить студента", "Загрузить базу данных", "Сохранить базу данных", "Выбрать студента", "Выполнить вариант 88", "Выход" };
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
            this->ExecutedTask();
            break;
        case 6:
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
                        std::cout << subject << ":" << grade << "\n";
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
                << student.GetGender() << " ";

            for (int semester = 1; semester <= 9; ++semester) {
                const auto& grades = student.GetGrades(semester);
                if (!grades.empty()) {
                    file << semester;
                    for (const auto& grade : grades) {
                        file << " " << grade.first << ":" << grade.second;
                    }
                }
            }
            file << "\n";
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
            for (int j = 0; j <= 9; j++) {
                int semester;
                std::string subject, mark;
                iss >> semester >> subject >> mark;
                student.SetGrade(semester, subject, mark);
            }
            
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

void Database::ExecutedTask() {
    system("CLS");
    int interval_1, interval_2;
    std::cout << "Укажите интервал года рождения" << std::endl;
    std::cin >> interval_1 >> interval_2;
    for (int i = 0; i < this->students.size(); i++) {
        bool check = true;
        if (students[i].GetYear() >= interval_1 and students[i].GetYear() <= interval_2) {
            for (int j = 0; j <= 9; j++) {
                for (std::string subject : std::vector<std::string>{"Физика", "Линал", "История", "Матан"}) {
                    if (students[i].grades[j][subject] == "3") {
                        check = false;
                        break;
                    }
                }
            }
        }
        if (check) {
            std::cout << students[i].GetLastName() << " " << students[i].GetFirstName() << " ";
            std::cout << students[i].GetPatronymic() << " " << students[i].GetGroup() << std::endl;
        }
    }
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
