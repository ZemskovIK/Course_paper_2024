#include "Database.h"
#include "Menu.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <windows.h>
#include <regex>
#include "Validator.h"
#include <limits>

Database::Database() {}

void Database::run() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = false;
    structCursorInfo.dwSize = 10;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    std::vector<std::string> menuItems = { "Показать студентов", "Доступные группы", "Добавить студента", "Загрузить базу данных", "Сохранить базу данных", "Выбрать студента", "Выполнить вариант 88", "Выход" };
    Menu menu(menuItems);
    while (true) {
        system("CLS");
        GoToXY(0, 0);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Белый цвет
        std::cout << "Курсовая работа по Языкам Программирования 1 курс, 2 семестр";

        GoToXY(0, 2);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Фиолетовый цвет
        std::cout << "Выполнил студент группы БИСО-01-23\nЗемсков Игорь";
        menu.Display();
        int choice = menu.HandleInput();

        switch (choice) {
        case 0:
            this->DisplayStudents();
            break;
        case 1:
            this->DisplayGroups();
            break;
        case 2:
            this->AddStudent();
            break;
        case 3:
            this->LoadFromFile("students.txt");
            break;
        case 4:
            this->SaveToFile("students.txt");
            break;
        case 5:
            this->SelectStudent();
            break;
        case 6:
            this->ExecutedTask();
            break;
        case 7:
            std::cout << std::endl << std::endl << std::endl;
            return;
        default:
            std::cerr << "Неверный выбор. Попробуйте снова.\n";
            break;
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

void Database::DisplayGroups() {
    system("CLS");
    std::map<std::string, std::vector<Student>> groups;
    for (const auto& student : students) {
        groups[student.GetGroup()].push_back(student);
    }

    for (const auto& [group, students] : groups) {
        std::cout << "Группа " << group << ":\n";
        for (const auto& student : students) {
            std::cout << student.GetLastName() << " " << student.GetFirstName() << " " << student.GetPatronymic() << "\n";
        }
        std::cout << std::endl;
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
    if (!Validator::IsValidDay(day)) {
        std::cerr << "Ошибка, попробуйте еще раз.\n";
        //system("CLS");
        std::cout << "Введите день рождения: ";
        std::cin >> day;
    }
    std::cout << "Введите месяц рождения: ";
    std::cin >> month;
    if (!Validator::IsValidMonth(month)) {
        std::cerr << "Ошибка, попробуйте еще раз.\n";
        std::cout << "Введите месяц рождения: ";
        std::cin >> month;
    }
    std::cout << "Введите год рождения: ";
    std::cin >> year;
    if (!Validator::IsValidYear(year)) {
        std::cerr << "Ошибка, попробуйте еще раз.\n";
        std::cout << "Введите год рождения: ";
        std::cin >> year;
    }
    std::cout << "Введите год поступления: ";
    std::cin >> admissionYear;
    if (!Validator::IsValidYear(year)) {
        std::cerr << "Ошибка, попробуйте еще раз.\n";
        std::cout << "Введите год поступления: ";
        std::cin >> year;
    }
    std::cout << "Введите факультет: ";
    std::cin >> faculty;
    if (!Validator::IsValidFacultyName(faculty)) {
        std::cerr << "Неверный формат факультета.\n";
        system("CLS");
        std::cout << "Введите факультет: ";
        std::cin >> faculty;
    }
    std::cout << "Введите кафедру: ";
    std::cin >> department;
    std::cout << "Введите группу: ";
    std::cin >> group;
    if (!Validator::IsValidGroupNumber(group)) {
        std::cerr << "Неверный формат номера группы.\n";
        system("CLS");
        std::cout << "Введите группу в формате ХХХХ-ХХ-ХХ: ";
        std::cin >> group;
    }
    std::cout << "Введите номер зачетной книжки: ";
    std::cin >> recordBookNumber;
    if (!Validator::IsValidStudentID(recordBookNumber)) {
        std::cerr << "Неверный формат номера зачетной книжки.\n";
        system("CLS");
        std::cout << "Введите номер зачетной книжки в формате 23Б0ХХХ: ";
        std::cin >> recordBookNumber;
    }
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
    if (!Validator::IsValidStudentID(recordBookNumber)) {
        std::cerr << "Неверный формат номера зачетной книжки.\n";
        //system("CLS");
        std::cout << "Введите номер зачетной книжки в формате 23Б0ХХХ: ";
        std::cin >> recordBookNumber;
    }
    Student* student = this->GetStudentByRecordBookNumber(recordBookNumber);
    if (!student) {
        std::cout << "Студент с таким номером зачетной книжки не найден.\n";
        system("pause");
        return;
    }

    std::vector<std::string> subMenuItems = { "Просмотреть оценки", "Проставить оценку", "Изменить данные", "Изменить оценку", "Удалить студента", "Назад" };
    Menu subMenu(subMenuItems);

    bool running = true;
    while (running) {
        system("CLS");
        GoToXY(0, 0);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Фиолетовый цвет
        std::cout << "ФИО: " << student->GetLastName() << " " << student->GetFirstName() << " " << student->GetPatronymic() << "\nГруппа: " << student->GetGroup() << "\n";

        subMenu.Display();
        int subChoice = subMenu.HandleInput();

        switch (subChoice) {
        case 0: { // Просмотреть оценки
            system("CLS");
            std::cout << "Введите номер семестра: ";
            int semester;
            std::cin >> semester;
            try {
                const auto& grades = student->GetGrades(semester);
                for (const auto& [subject, grade] : grades) {
                    std::cout << subject << " " << grade << '\n';
                }
            }
            catch (const std::out_of_range&) {
                std::cout << "Оценки за данный семестр не найдены.\n";
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
            if (!Validator::IsValidSubjectName(subject)) {
                std::cerr << "Неверный формат названия предмета.\n";
                system("CLS");
                std::cin.ignore(80, '\n');
                std::getline(std::cin, subject);
            }
            std::cout << "Введите оценку: ";
            std::cin >> grade;

            student->SetGrade(semester, subject, grade);
            std::cout << "Оценка добавлена.\n";
            system("pause");
            break;
        }
        case 2: { // Изменить данные
            system("CLS");
            // Считываем данные, которые нужно изменить
            std::string newData;
            std::cout << "Выберите данные для изменения:\n1. Фамилия\n2. Имя\n3. Отчество\n4. Факультет\n5. Кафедра\n6. Группа\n7. Номер зачетной книжки\n8. Пол\n";
            int updateChoice;
            std::cin >> updateChoice;

            switch (updateChoice) {
            case 1:
                std::cout << "Введите новую фамилию: ";
                std::cin >> newData;
                student->SetLastName(newData);
                break;
            case 2:
                std::cout << "Введите новое имя: ";
                std::cin >> newData;
                student->SetFirstName(newData);
                break;
            case 3:
                std::cout << "Введите новое отчество: ";
                std::cin >> newData;
                student->SetPatronymic(newData);
                break;
            case 4:
                std::cout << "Введите новый факультет: ";
                std::cin >> newData;
                if (!Validator::IsValidFacultyName(newData)) {
                    std::cerr << "Неверный формат факультета.\n";
                    break;
                }
                student->SetFaculty(newData);
                break;
            case 5:
                std::cout << "Введите новую кафедру: ";
                std::cin >> newData;
                student->SetDepartment(newData);
                break;
            case 6:
                std::cout << "Введите новую группу: ";
                std::cin >> newData;
                if (!Validator::IsValidGroupNumber(newData)) {
                    std::cerr << "Неверный формат номера группы.\n";
                    break;
                }
                student->SetGroup(newData);
                break;
            case 7:
                std::cout << "Введите новый номер зачетной книжки: ";
                std::cin >> newData;
                student->SetRecordBookNumber(newData);
                break;
            case 8:
                std::cout << "Введите новый пол: ";
                std::cin >> newData;
                student->SetGender(newData);
                break;
            default:
                std::cerr << "Неверный выбор. Попробуйте снова.\n";
                break;
            }

            // Добавляем проверку данных с использованием Validator
            std::cout << "Данные успешно изменены.\n";
            system("pause");
            break;
        }
        case 3: { // Изменить оценку
            system("CLS");
            UpdateGrade(student);
            break;
        }
        case 4: { // Удалить студента
            system("CLS");
            if (this->DeleteStudent(recordBookNumber)) {
                std::cout << "Студент отчислен.\n";
                system("pause");
                running = false; // Возвращаемся в главное меню
            }
            else {
                std::cout << "Ошибка при удалении студента.\n";
                system("pause");
            }
            break;
        }
        case 5: // Назад
            running = false; // Возвращаемся в главное меню
            break;
        }
    }
}

void Database::UpdateStudentData(Student* student) {
    bool running = true;
    while (running) {
        system("CLS");
        std::vector<std::string> updateMenuItems = { "Изменить фамилию", "Изменить имя", "Изменить отчество", "Изменить факультет", "Изменить кафедру", "Изменить группу", "Изменить номер зачетной книжки", "Изменить пол", "Назад" };
        Menu updateMenu(updateMenuItems);
        updateMenu.Display();
        int choice = updateMenu.HandleInput();

        std::string newData;
        switch (choice) {
        case 0: // Изменить фамилию
            std::cout << "Введите новую фамилию: ";
            std::cin >> newData;
            student->SetLastName(newData);
            break;
        case 1: // Изменить имя
            std::cout << "Введите новое имя: ";
            std::cin >> newData;
            student->SetFirstName(newData);
            break;
        case 2: // Изменить отчество
            std::cout << "Введите новое отчество: ";
            std::cin >> newData;
            student->SetPatronymic(newData);
            break;
        case 3: // Изменить факультет
            std::cout << "Введите новый факультет: ";
            std::cin >> newData;
            if (!Validator::IsValidFacultyName(newData)) {
                std::cerr << "Неверный формат факультета.\n";
                break;
            }
            student->SetFaculty(newData);
            break;
        case 4: // Изменить кафедру
            std::cout << "Введите новую кафедру: ";
            std::cin >> newData;
            student->SetDepartment(newData);
            break;
        case 5: // Изменить группу
            std::cout << "Введите новую группу: ";
            std::cin >> newData;
            if (!Validator::IsValidGroupNumber(newData)) {
                std::cerr << "Неверный формат номера группы.\n";
                break;
            }
            student->SetGroup(newData);
            break;
        case 6: // Изменить номер зачетной книжки
            std::cout << "Введите новый номер зачетной книжки: ";
            std::cin >> newData;
            student->SetRecordBookNumber(newData);
            break;
        case 7: // Изменить пол
            std::cout << "Введите новый пол: ";
            std::cin >> newData;
            student->SetGender(newData);
            break;
        case 8: // Назад
            running = false;
            break;
        }
    }
}

void Database::UpdateGrade(Student* student) {
    system("CLS");
    int semester;
    std::string subject, newGrade;

    std::cout << "Введите номер семестра: ";
    std::cin >> semester;
    std::cout << "Введите предмет: ";
    std::cin.ignore(80, '\n');
    std::getline(std::cin, subject);
    if (!Validator::IsValidSubjectName(subject)) {
        std::cerr << "Неверный формат названия предмета.\n";
        system("CLS");
        std::cin.ignore(80, '\n');
        std::getline(std::cin, subject);
    }
    std::cout << "Введите новую оценку: ";
    std::cin >> newGrade;

    student->SetGrade(semester, subject, newGrade);
    std::cout << "Оценка изменена.\n";
    system("pause");
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
                    file << " " << semester;
                    for (const auto& grade : grades) {
                        file << " " << grade.first << " " << grade.second;
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
        if (students[i].GetYear() >= interval_1 && students[i].GetYear() <= interval_2) {
            for (int j = 0; j <= 9; j++) {
                for (const std::string& subject : std::vector<std::string>{ "Физика", "Линал", "История", "Матан" }) {
                    if (students[i].GetGrades(j).count(subject) > 0 && students[i].GetGrades(j).at(subject) == "3") {
                        check = false;
                        break;
                    }
                }
            }
        }
        else {
            check = false;
            std::cout << "Нет таких студентов в базе!\n";
            break;
        }
        if (check) {
            std::cout << students[i].GetLastName() << " " << students[i].GetFirstName() << " ";
            std::cout << students[i].GetPatronymic() << " " << students[i].GetGroup() << std::endl;
        }
    }
    system("pause");
}

//void Database::ExecutedTask() {
//    system("CLS");
//    int interval_1, interval_2, option;
//    std::cout << "Укажите интервал года рождения:\n";
//    std::cin >> interval_1 >> interval_2;
//
//    std::cout << "Выберите вариант для выполнения задания:\n"
//        << "1) нет ни одной 3\n"
//        << "2) нет ни одной 3 и 4\n"
//        << "3) нет ни одной 5\n";
//    std::cin >> option;
//    for (const auto& student : students) {
//        bool check = true;
//        if (student.GetYear() >= interval_1 && student.GetYear() <= interval_2) {
//            for (int semester = 0; semester <= 9; ++semester) {
//                const auto& grades = student.GetGrades(semester);
//                for (const auto& [subject, grade] : grades) {
//                    if ((option == 1 && grade == "3") ||
//                        (option == 2 && (grade == "3" || grade == "4")) ||
//                        (option == 3 && grade == "5")) {
//                        check = false;
//                        break;
//                    }
//                }
//            }
//        }
//        else {
//            check = false;
//            std::cout << "Нет таких студентов в базе!\n";
//            break;
//        }
//        if (check) {
//            std::cout << student.GetLastName() << " " << student.GetFirstName() << " ";
//            std::cout << student.GetPatronymic() << " " << student.GetGroup() << std::endl;
//        }
//    }
//    system("pause");
//}

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
