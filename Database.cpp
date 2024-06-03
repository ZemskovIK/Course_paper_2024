#include "Database.h"
#include <iostream>

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
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file.\n";
    }
}

void Database::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        students.clear();
        std::string lastName, firstName, patronymic, faculty, department, group, recordBookNumber, gender;
        int day, month, year, admissionYear;
        while (file >> lastName >> firstName >> patronymic >> day >> month >> year >> admissionYear >> faculty >> department >> group >> recordBookNumber >> gender) {
            Student student(lastName, firstName, patronymic, day, month, year, admissionYear, faculty, department, group, recordBookNumber, gender);
            students.push_back(student);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file.\n";
    }
}

const std::vector<Student>& Database::GetStudents() const {
    return students;
}
