#ifndef STUDENT_H
#define STUDENT_H

#include <string>

enum class Bookstatus{
    Borrowed,
    Available
};

struct Book {
    string title;
    string author;
    Bookstatus status = Bookstatus::Available;
    string BorrowedBy = "";
};
#endif