#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Database {
public:
    Database();
    void run();
    void DisplayStudents();
    void AddStudent();
    void SelectStudent();
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);
    void ExecutedTask();
    const std::vector<Student>& GetStudents() const;
    Student* GetStudentByRecordBookNumber(const std::string& recordBookNumber);
    bool DeleteStudent(const std::string& recordBookNumber);

private:
    std::vector<Student> students;
};

#endif // DATABASE_H
