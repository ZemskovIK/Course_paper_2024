#include "Database.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Database::Database() {}

void Database::AddStudent(const Student& student) {
    students.push_back(student);
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

            while (std::getline(file, line) && !line.empty()) {
                std::istringstream gradeStream(line);
                int semester;
                gradeStream >> semester;

                std::string gradePair;
                while (gradeStream >> gradePair) {
                    auto pos = gradePair.find(':');
                    std::string subject = gradePair.substr(0, pos);
                    std::string grade = gradePair.substr(pos + 1);
                    student.SetGrade(semester, subject, grade);
                }
            }
            students.push_back(student);
        }
        file.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для чтения.\n";
    }
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
