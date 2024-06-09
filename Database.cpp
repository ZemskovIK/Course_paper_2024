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

    std::vector<std::string> menuItems = { "�������� ���������", "��������� ������", "�������� ��������", "��������� ���� ������", "��������� ���� ������", "������� ��������", "��������� ������� 88", "�����" };
    Menu menu(menuItems);
    while (true) {
        system("CLS");
        GoToXY(0, 0);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ����� ����
        std::cout << "�������� ������ �� ������ ���������������� 1 ����, 2 �������";

        GoToXY(0, 2);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ���������� ����
        std::cout << "�������� ������� ������ ����-01-23\n������� �����";
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
            std::cerr << "�������� �����. ���������� �����.\n";
            break;
        }
    }
}

void Database::DisplayStudents() {
    system("CLS");
    const auto& students = this->GetStudents();
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

void Database::DisplayGroups() {
    system("CLS");
    std::map<std::string, std::vector<Student>> groups;
    for (const auto& student : students) {
        groups[student.GetGroup()].push_back(student);
    }

    for (const auto& [group, students] : groups) {
        std::cout << "������ " << group << ":\n";
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

    std::cout << "������� �������: ";
    std::cin >> lastName;
    std::cout << "������� ���: ";
    std::cin >> firstName;
    std::cout << "������� ��������: ";
    std::cin >> patronymic;
    std::cout << "������� ���� ��������: ";
    std::cin >> day;
    if (!Validator::IsValidDay(day)) {
        std::cerr << "������, ���������� ��� ���.\n";
        //system("CLS");
        std::cout << "������� ���� ��������: ";
        std::cin >> day;
    }
    std::cout << "������� ����� ��������: ";
    std::cin >> month;
    if (!Validator::IsValidMonth(month)) {
        std::cerr << "������, ���������� ��� ���.\n";
        std::cout << "������� ����� ��������: ";
        std::cin >> month;
    }
    std::cout << "������� ��� ��������: ";
    std::cin >> year;
    if (!Validator::IsValidYear(year)) {
        std::cerr << "������, ���������� ��� ���.\n";
        std::cout << "������� ��� ��������: ";
        std::cin >> year;
    }
    std::cout << "������� ��� �����������: ";
    std::cin >> admissionYear;
    if (!Validator::IsValidYear(year)) {
        std::cerr << "������, ���������� ��� ���.\n";
        std::cout << "������� ��� �����������: ";
        std::cin >> year;
    }
    std::cout << "������� ���������: ";
    std::cin >> faculty;
    if (!Validator::IsValidFacultyName(faculty)) {
        std::cerr << "�������� ������ ����������.\n";
        system("CLS");
        std::cout << "������� ���������: ";
        std::cin >> faculty;
    }
    std::cout << "������� �������: ";
    std::cin >> department;
    std::cout << "������� ������: ";
    std::cin >> group;
    if (!Validator::IsValidGroupNumber(group)) {
        std::cerr << "�������� ������ ������ ������.\n";
        system("CLS");
        std::cout << "������� ������ � ������� ����-��-��: ";
        std::cin >> group;
    }
    std::cout << "������� ����� �������� ������: ";
    std::cin >> recordBookNumber;
    if (!Validator::IsValidStudentID(recordBookNumber)) {
        std::cerr << "�������� ������ ������ �������� ������.\n";
        system("CLS");
        std::cout << "������� ����� �������� ������ � ������� 23�0���: ";
        std::cin >> recordBookNumber;
    }
    std::cout << "������� ���: ";
    std::cin >> gender;

    Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);
    students.push_back(student);
    std::cout << "������� ��������.\n";
    system("pause");

}

void Database::SelectStudent() {
    system("CLS");
    const auto& students = this->GetStudents();
    if (students.empty()) {
        std::cout << "��� ��������� � ���� ������.\n";
        system("pause");
        return;
    }

    std::cout << "������� ����� �������� ������ ��������: ";
    std::string recordBookNumber;
    std::cin >> recordBookNumber;
    if (!Validator::IsValidStudentID(recordBookNumber)) {
        std::cerr << "�������� ������ ������ �������� ������.\n";
        //system("CLS");
        std::cout << "������� ����� �������� ������ � ������� 23�0���: ";
        std::cin >> recordBookNumber;
    }
    Student* student = this->GetStudentByRecordBookNumber(recordBookNumber);
    if (!student) {
        std::cout << "������� � ����� ������� �������� ������ �� ������.\n";
        system("pause");
        return;
    }

    std::vector<std::string> subMenuItems = { "����������� ������", "���������� ������", "�������� ������", "�������� ������", "������� ��������", "�����" };
    Menu subMenu(subMenuItems);

    bool running = true;
    while (running) {
        system("CLS");
        GoToXY(0, 0);
        SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ���������� ����
        std::cout << "���: " << student->GetLastName() << " " << student->GetFirstName() << " " << student->GetPatronymic() << "\n������: " << student->GetGroup() << "\n";

        subMenu.Display();
        int subChoice = subMenu.HandleInput();

        switch (subChoice) {
        case 0: { // ����������� ������
            system("CLS");
            std::cout << "������� ����� ��������: ";
            int semester;
            std::cin >> semester;
            try {
                const auto& grades = student->GetGrades(semester);
                for (const auto& [subject, grade] : grades) {
                    std::cout << subject << " " << grade << '\n';
                }
            }
            catch (const std::out_of_range&) {
                std::cout << "������ �� ������ ������� �� �������.\n";
            }
            system("pause");
            break;
        }
        case 1: { // ���������� ������
            system("CLS");
            int semester;
            std::string subject, grade;

            std::cout << "������� ����� ��������: ";
            std::cin >> semester;
            std::cout << "������� �������: ";
            std::cin.ignore(80, '\n');
            std::getline(std::cin, subject);
            if (!Validator::IsValidSubjectName(subject)) {
                std::cerr << "�������� ������ �������� ��������.\n";
                system("CLS");
                std::cin.ignore(80, '\n');
                std::getline(std::cin, subject);
            }
            std::cout << "������� ������: ";
            std::cin >> grade;

            student->SetGrade(semester, subject, grade);
            std::cout << "������ ���������.\n";
            system("pause");
            break;
        }
        case 2: { // �������� ������
            system("CLS");
            // ��������� ������, ������� ����� ��������
            std::string newData;
            std::cout << "�������� ������ ��� ���������:\n1. �������\n2. ���\n3. ��������\n4. ���������\n5. �������\n6. ������\n7. ����� �������� ������\n8. ���\n";
            int updateChoice;
            std::cin >> updateChoice;

            switch (updateChoice) {
            case 1:
                std::cout << "������� ����� �������: ";
                std::cin >> newData;
                student->SetLastName(newData);
                break;
            case 2:
                std::cout << "������� ����� ���: ";
                std::cin >> newData;
                student->SetFirstName(newData);
                break;
            case 3:
                std::cout << "������� ����� ��������: ";
                std::cin >> newData;
                student->SetPatronymic(newData);
                break;
            case 4:
                std::cout << "������� ����� ���������: ";
                std::cin >> newData;
                if (!Validator::IsValidFacultyName(newData)) {
                    std::cerr << "�������� ������ ����������.\n";
                    break;
                }
                student->SetFaculty(newData);
                break;
            case 5:
                std::cout << "������� ����� �������: ";
                std::cin >> newData;
                student->SetDepartment(newData);
                break;
            case 6:
                std::cout << "������� ����� ������: ";
                std::cin >> newData;
                if (!Validator::IsValidGroupNumber(newData)) {
                    std::cerr << "�������� ������ ������ ������.\n";
                    break;
                }
                student->SetGroup(newData);
                break;
            case 7:
                std::cout << "������� ����� ����� �������� ������: ";
                std::cin >> newData;
                student->SetRecordBookNumber(newData);
                break;
            case 8:
                std::cout << "������� ����� ���: ";
                std::cin >> newData;
                student->SetGender(newData);
                break;
            default:
                std::cerr << "�������� �����. ���������� �����.\n";
                break;
            }

            // ��������� �������� ������ � �������������� Validator
            std::cout << "������ ������� ��������.\n";
            system("pause");
            break;
        }
        case 3: { // �������� ������
            system("CLS");
            UpdateGrade(student);
            break;
        }
        case 4: { // ������� ��������
            system("CLS");
            if (this->DeleteStudent(recordBookNumber)) {
                std::cout << "������� ��������.\n";
                system("pause");
                running = false; // ������������ � ������� ����
            }
            else {
                std::cout << "������ ��� �������� ��������.\n";
                system("pause");
            }
            break;
        }
        case 5: // �����
            running = false; // ������������ � ������� ����
            break;
        }
    }
}

void Database::UpdateStudentData(Student* student) {
    bool running = true;
    while (running) {
        system("CLS");
        std::vector<std::string> updateMenuItems = { "�������� �������", "�������� ���", "�������� ��������", "�������� ���������", "�������� �������", "�������� ������", "�������� ����� �������� ������", "�������� ���", "�����" };
        Menu updateMenu(updateMenuItems);
        updateMenu.Display();
        int choice = updateMenu.HandleInput();

        std::string newData;
        switch (choice) {
        case 0: // �������� �������
            std::cout << "������� ����� �������: ";
            std::cin >> newData;
            student->SetLastName(newData);
            break;
        case 1: // �������� ���
            std::cout << "������� ����� ���: ";
            std::cin >> newData;
            student->SetFirstName(newData);
            break;
        case 2: // �������� ��������
            std::cout << "������� ����� ��������: ";
            std::cin >> newData;
            student->SetPatronymic(newData);
            break;
        case 3: // �������� ���������
            std::cout << "������� ����� ���������: ";
            std::cin >> newData;
            if (!Validator::IsValidFacultyName(newData)) {
                std::cerr << "�������� ������ ����������.\n";
                break;
            }
            student->SetFaculty(newData);
            break;
        case 4: // �������� �������
            std::cout << "������� ����� �������: ";
            std::cin >> newData;
            student->SetDepartment(newData);
            break;
        case 5: // �������� ������
            std::cout << "������� ����� ������: ";
            std::cin >> newData;
            if (!Validator::IsValidGroupNumber(newData)) {
                std::cerr << "�������� ������ ������ ������.\n";
                break;
            }
            student->SetGroup(newData);
            break;
        case 6: // �������� ����� �������� ������
            std::cout << "������� ����� ����� �������� ������: ";
            std::cin >> newData;
            student->SetRecordBookNumber(newData);
            break;
        case 7: // �������� ���
            std::cout << "������� ����� ���: ";
            std::cin >> newData;
            student->SetGender(newData);
            break;
        case 8: // �����
            running = false;
            break;
        }
    }
}

void Database::UpdateGrade(Student* student) {
    system("CLS");
    int semester;
    std::string subject, newGrade;

    std::cout << "������� ����� ��������: ";
    std::cin >> semester;
    std::cout << "������� �������: ";
    std::cin.ignore(80, '\n');
    std::getline(std::cin, subject);
    if (!Validator::IsValidSubjectName(subject)) {
        std::cerr << "�������� ������ �������� ��������.\n";
        system("CLS");
        std::cin.ignore(80, '\n');
        std::getline(std::cin, subject);
    }
    std::cout << "������� ����� ������: ";
    std::cin >> newGrade;

    student->SetGrade(semester, subject, newGrade);
    std::cout << "������ ��������.\n";
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
        std::cerr << "�� ������� ������� ���� ��� ������.\n";
    }
    system("CLS");
    std::cout << "���� ������ ���������.\n";
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
        std::cerr << "�� ������� ������� ���� ��� ������.\n";
    }
    system("CLS");
    std::cout << "���� ������ ���������.\n";
    system("pause");
}

void Database::ExecutedTask() {
    system("CLS");
    int interval_1, interval_2;
    std::cout << "������� �������� ���� ��������" << std::endl;
    std::cin >> interval_1 >> interval_2;
    for (int i = 0; i < this->students.size(); i++) {
        bool check = true;
        if (students[i].GetYear() >= interval_1 && students[i].GetYear() <= interval_2) {
            for (int j = 0; j <= 9; j++) {
                for (const std::string& subject : std::vector<std::string>{ "������", "�����", "�������", "�����" }) {
                    if (students[i].GetGrades(j).count(subject) > 0 && students[i].GetGrades(j).at(subject) == "3") {
                        check = false;
                        break;
                    }
                }
            }
        }
        else {
            check = false;
            std::cout << "��� ����� ��������� � ����!\n";
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
//    std::cout << "������� �������� ���� ��������:\n";
//    std::cin >> interval_1 >> interval_2;
//
//    std::cout << "�������� ������� ��� ���������� �������:\n"
//        << "1) ��� �� ����� 3\n"
//        << "2) ��� �� ����� 3 � 4\n"
//        << "3) ��� �� ����� 5\n";
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
//            std::cout << "��� ����� ��������� � ����!\n";
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
