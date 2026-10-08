
#ifndef STUDENT_H
#define STUDENT_H

#include "Book.hpp"
#include <string>
#include <vector>
#include <iostream>

class Student {
    std::string Name_;
    std::string Surname_;
    const std::string ID_unique;
    std::vector<std::string> BorrowedBooks;
    bool CanBorrow_ = true;

public:
    Student(std::string Name, std::string Surname, std::string Id);

    void GetInfo() const;

    bool BorrowBook(Book& BookToBorrow);

    bool ReturnBook(Book& BookToReturn);
};

#endif
