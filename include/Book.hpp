#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

enum class Bookstatus{
    Borrowed,
    Available
};

class Book {
    std::string title_;
    std::string author_;
    Bookstatus status = Bookstatus::Available;
    std::string borrowedBy_ = "";
    static int totalBooks_;

public:
    Book(std::string title, std::string author);
    ~Book();
    Bookstatus Status() const;
    std::string BorrowedBy() const;
    std::string title() const;
    void setStatus(Bookstatus newStatus);
    void setBorrowedBy(const std::string& newBorrower);
};


#endif


