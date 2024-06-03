#include "Student.h"

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
