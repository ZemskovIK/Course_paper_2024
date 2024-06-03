#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include <vector>
#include <fstream>

class Database {
private:
    std::vector<Student> students;

public:
    Database();
    void AddStudent(const Student& student);
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);
    const std::vector<Student>& GetStudents() const;
};

#endif
