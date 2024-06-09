#include "Student.h"

Student::Student(const std::string& lastName, const std::string& firstName, const std::string& patronymic, int day, int month, int year, int admissionYear, const std::string& faculty, const std::string& department, const std::string& group, const std::string& recordBookNumber, const std::string& gender)
    : lastName(lastName), firstName(firstName), patronymic(patronymic), day(day), month(month), year(year), admissionYear(admissionYear), faculty(faculty), department(department), group(group), recordBookNumber(recordBookNumber), gender(gender) {}

std::string Student::GetLastName() const { return lastName; }
std::string Student::GetFirstName() const { return firstName; }
std::string Student::GetPatronymic() const { return patronymic; }
int Student::GetDay() const { return day; }
int Student::GetMonth() const { return month; }
int Student::GetYear() const { return year; }
int Student::GetAdmissionYear() const { return admissionYear; }
std::string Student::GetFaculty() const { return faculty; }
std::string Student::GetDepartment() const { return department; }
std::string Student::GetGroup() const { return group; }
std::string Student::GetRecordBookNumber() const { return recordBookNumber; }
std::string Student::GetGender() const { return gender; }

void Student::SetLastName(const std::string& lastName) { this->lastName = lastName; }
void Student::SetFirstName(const std::string& firstName) { this->firstName = firstName; }
void Student::SetPatronymic(const std::string& patronymic) { this->patronymic = patronymic; }
void Student::SetFaculty(const std::string& faculty) { this->faculty = faculty; }
void Student::SetDepartment(const std::string& department) { this->department = department; }
void Student::SetGroup(const std::string& group) { this->group = group; }
void Student::SetRecordBookNumber(const std::string& recordBookNumber) { this->recordBookNumber = recordBookNumber; }
void Student::SetGender(const std::string& gender) { this->gender = gender; }

bool Student::UpdateGrade(int semester, const std::string& subject, const std::string& newGrade) {
    if (grades.count(semester) && grades[semester].count(subject)) {
        grades[semester][subject] = newGrade;
        return true;
    }
    return false;
}

void Student::SetGrade(int semester, const std::string& subject, const std::string& grade) {
    grades[semester][subject] = grade;
}

const std::map<std::string, std::string>& Student::GetGrades(int semester) const {
    static const std::map<std::string, std::string> emptyGrades;
    auto it = grades.find(semester);
    return it != grades.end() ? it->second : emptyGrades;
}
