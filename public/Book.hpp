#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include "Members/Member.hpp"

enum class Bookstatus{
    Borrowed,
    Available
};

enum class Bookstate{
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
    virtual ~Book();
    virtual void Display() const;
    virtual Book* Clone()const ;
    void Destroy_Clone(Book *Copy);
    Book(const Book& other);
    Bookstatus Status() const;
    std::string BorrowedBy() const;
    std::string title() const;
    std::string author() const;
    static bool BorrowBook (Member* Membre, Book* BooktoBorrow);
    static bool ReturnBook (Member* Membre, Book*BooktoReturn);
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
    EBook(const EBook &other);
    EBook* Clone()const override;
    std::string Url() const;
    int size() const;
};

class PhysicalBook : public Book{
private:
    std::string Localisation_;
    Bookstate state_;

public:
    PhysicalBook(std::string title, std::string author, std::string Localisation, Bookstate state);
    PhysicalBook(const PhysicalBook &other);
    PhysicalBook *Clone()const;
    std::string Localisation() const;
    void SetState(Bookstate Newstate);
    Bookstate State() const;
};

class AudioBook : public Book{
private:
    int Duration_;
    std::string Narator_;
    std::string Langage_;

public:
    AudioBook(std::string title, std::string author, int Duration, std::string Narator, std::string Langage);
    AudioBook(const AudioBook&other);
    AudioBook* Clone ()const;
    int Duration() const;
    std::string Narator() const;
    std::string Langage() const;
};

#endif


