#ifndef BOOK_H
#define BOOK_H

#include <string>

enum class Bookstatus{
    Borrowed,
    Available
};

struct Book {
    std::string title;
    std::string author;
    Bookstatus status = Bookstatus::Available;
    std::string BorrowedBy = "";
};
#endif