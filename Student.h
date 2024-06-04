#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <unordered_map>

class Student {
public:
    Student(const std::string& lastName, const std::string& firstName, const std::string& patronymic, int day, int month, int year, int admissionYear, const std::string& faculty, const std::string& department, const std::string& group, const std::string& recordBookNumber, const std::string& gender);

    const std::string& GetLastName() const;
    const std::string& GetFirstName() const;
    const std::string& GetPatronymic() const;
    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    int GetAdmissionYear() const;
    const std::string& GetFaculty() const;
    const std::string& GetDepartment() const;
    const std::string& GetGroup() const;
    const std::string& GetRecordBookNumber() const;
    const std::string& GetGender() const;

    const std::unordered_map<std::string, std::string>& GetGrades(int semester) const;
    void SetGrade(int semester, const std::string& subject, const std::string& grade);
    void UpdateData(const std::string& lastName, const std::string& firstName, const std::string& patronymic, int day, int month, int year, int admissionYear, const std::string& faculty, const std::string& department, const std::string& group, const std::string& gender);

private:
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    int day, month, year;
    int admissionYear;
    std::string faculty;
    std::string department;
    std::string group;
    std::string recordBookNumber;
    std::string gender;
    static const std::unordered_map<std::string, std::string> emptyGrades;
public:
    std::unordered_map<int, std::unordered_map<std::string, std::string>> grades;
};

#endif // STUDENT_H
