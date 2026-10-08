#ifndef BOOK_H
#define BOOK_H

#include <string>

enum class Bookstatus{
    Borrowed,
    Available
};

class Book {
    std::string title;
    std::string author;
    Bookstatus status = Bookstatus::Available;
    std::string BorrowedBy = "";

public:
    Book(std::string title, std::string author);
    Bookstatus Status();
    std::string BorrowedBy();
    std::string title();
};


#endif


