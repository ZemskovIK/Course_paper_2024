#include "Student.h"
#include <algorithm>

const std::unordered_map<std::string, std::string> Student::emptyGrades = {};

Student::Student(const std::string& lastName, const std::string& firstName, const std::string& patronymic, int day, int month, int year, int admissionYear, const std::string& faculty, const std::string& department, const std::string& group, const std::string& recordBookNumber, const std::string& gender)
    : lastName(lastName), firstName(firstName), patronymic(patronymic), day(day), month(month), year(year), admissionYear(admissionYear), faculty(faculty), department(department), group(group), recordBookNumber(recordBookNumber), gender(gender) {}

const std::string& Student::GetLastName() const {
    return lastName;
}

const std::string& Student::GetFirstName() const {
    return firstName;
}

const std::string& Student::GetPatronymic() const {
    return patronymic;
}

int Student::GetDay() const {
    return day;
}

int Student::GetMonth() const {
    return month;
}

int Student::GetYear() const {
    return year;
}

int Student::GetAdmissionYear() const {
    return admissionYear;
}

const std::string& Student::GetFaculty() const {
    return faculty;
}

const std::string& Student::GetDepartment() const {
    return department;
}

const std::string& Student::GetGroup() const {
    return group;
}

const std::string& Student::GetRecordBookNumber() const {
    return recordBookNumber;
}

const std::string& Student::GetGender() const {
    return gender;
}

const std::unordered_map<std::string, std::string>& Student::GetGrades(int semester) const {
    auto it = grades.find(semester);
    return it != grades.end() ? it->second : emptyGrades;
}

void Student::SetGrade(int semester, const std::string& subject, const std::string& grade) {
    grades[semester][subject] = grade;
}

void Student::UpdateData(const std::string& lastName, const std::string& firstName, const std::string& patronymic, int day, int month, int year, int admissionYear, const std::string& faculty, const std::string& department, const std::string& group, const std::string& gender) {
    this->lastName = lastName;
    this->firstName = firstName;
    this->patronymic = patronymic;
    this->day = day;
    this->month = month;
    this->year = year;
    this->admissionYear = admissionYear;
    this->faculty = faculty;
    this->department = department;
    this->group = group;
    this->gender = gender;
}
