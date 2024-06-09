#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>
#include <vector>

class Student {
public:
    Student(const std::string& lastName, const std::string& firstName, const std::string& patronymic, int day, int month, int year, int admissionYear, const std::string& faculty, const std::string& department, const std::string& group, const std::string& recordBookNumber, const std::string& gender);

    // Методы доступа
    std::string GetLastName() const;
    std::string GetFirstName() const;
    std::string GetPatronymic() const;
    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    int GetAdmissionYear() const;
    std::string GetFaculty() const;
    std::string GetDepartment() const;
    std::string GetGroup() const;
    std::string GetRecordBookNumber() const;
    std::string GetGender() const;

    // Методы изменения данных
    void SetLastName(const std::string& lastName);
    void SetFirstName(const std::string& firstName);
    void SetPatronymic(const std::string& patronymic);
    void SetFaculty(const std::string& faculty);
    void SetDepartment(const std::string& department);
    void SetGroup(const std::string& group);
    void SetRecordBookNumber(const std::string& recordBookNumber);
    void SetGender(const std::string& gender);
    bool UpdateGrade(int semester, const std::string& subject, const std::string& newGrade);

    // Методы для работы с оценками
    void SetGrade(int semester, const std::string& subject, const std::string& grade);
    const std::map<std::string, std::string>& GetGrades(int semester) const;
    //const std::map<int, std::map<std::string, std::string>>& GetGrades() const;

private:
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    int day;
    int month;
    int year;
    int admissionYear;
    std::string faculty;
    std::string department;
    std::string group;
    std::string recordBookNumber;
    std::string gender;
    std::map<int, std::map<std::string, std::string>> grades; // Оценки студента по семестрам и предметам
};

#endif // STUDENT_H
