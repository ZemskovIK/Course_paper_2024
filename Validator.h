#pragma once
#include <string>

class Validator {
public:
    static bool IsValidGroupNumber(const std::string& groupNumber);
    static bool IsValidFacultyName(const std::string& facultyName);
    static bool IsValidSubjectName(const std::string& subjectName);
    static bool IsValidStudentID(const std::string& studentID);
    static bool IsValidGrade(int grade);
    static bool IsValidDay(int day);
    static bool IsValidMonth(int month);
    static bool IsValidYear(int year);
};