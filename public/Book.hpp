#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

enum class Bookstatus{
    Borrowed,
    Available
};

enum class Bookstate{
    New,
    Good,
    Damaged
};

class Book {
private:
    std::string title_;
    std::string author_;
    Bookstatus status = Bookstatus::Available;
    std::string borrowedBy_ = "";
    static int totalBooks_;

public:
    Book(std::string title, std::string author);
    ~Book();
    Book(const Book& other);
    Bookstatus Status() const;
    std::string BorrowedBy() const;
    std::string title() const;
    std::string author() const;
    void setStatus(Bookstatus newStatus);
    void setBorrowedBy(const std::string& newBorrower);
    static int totalBooks();
};



class EBook : public Book{
private:
    std::string downloadUrl_;
    int fileSize_;

public:
    EBook(std::string title, std::string author, std::string url, int size);
    std::string Url() const;
    int size() const;

};

class PhysicalBook : public Book{
private:
    std::string Localisation_;
    Bookstate state_;

public:
    PhysicalBook(std::string title, std::string author, std::string Localisation, std::string state);
};

class AudioBook : public Book{
private:
    int Duration_;
    std::string Narator_;
    std::string Langage_;

private:
    AudioBook(std::string title, std::string author, int Duration, std::string Narator, std::string Langage);
};

#endif


