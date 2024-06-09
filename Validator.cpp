#include "Validator.h"
#include <regex>

bool Validator::IsValidGroupNumber(const std::string& groupNumber) {
    std::regex pattern("^[A-ZР-п]{4}-\\d{2}-\\d{2}$");
    return std::regex_match(groupNumber, pattern);
}

bool Validator::IsValidFacultyName(const std::string& facultyName) {
    std::regex pattern("^[A-Za-zР-пр-џ]+$");
    return std::regex_match(facultyName, pattern);
}

bool Validator::IsValidSubjectName(const std::string& subjectName) {
    std::regex pattern("^[A-Za-zР-пр-џ ]+$");
    return std::regex_match(subjectName, pattern);
}

bool Validator::IsValidStudentID(const std::string& studentID) {
    std::regex pattern("^\\d{2}С0\\d{3}$");
    return std::regex_match(studentID, pattern);
}

bool Validator::IsValidGrade(int grade) {
    return grade >= 2 && grade <= 5;
}

bool Validator::IsValidDay(int day) {
    return day >= 1 && day <= 31;
}

bool Validator::IsValidMonth(int month) {
    return month >= 1 && month <= 12;
}

bool Validator::IsValidYear(int year) {
    std::regex pattern("^\\d{4}$");
    return std::regex_match(std::to_string(year), pattern);
}