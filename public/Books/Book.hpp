#ifndef BOOK_BASE_H
#define BOOK_BASE_H

#include <string>
#include <vector>
#include "Members/Member.hpp"
#include "Interfaces/IDisplayable.hpp"

enum class Bookstatus{
    Borrowed,
    Available,
    UnAvailable
};

enum class Bookstate{
    New,
    Good,
    Damaged
};

class Book : public IDisplayable{
private:
    std::string title_;
    std::string author_;
    Bookstatus status = Bookstatus::Available;
    std::vector<std::string> borrowedBy_;
    static int totalBooks_;

public:
    Book(std::string title, std::string author);
    virtual ~Book();
    virtual void GetInfo() const override = 0;
    virtual Book* Clone() const = 0;
    void Destroy_Clone(Book *Copy);
    Book(const Book& other);
    Bookstatus Status() const;
    int BorrowedBy_Size();
    void BorrowedBy() const;
    std::string title() const;
    std::string author() const;
    virtual bool SpecialTest (Book* BooktoBorrow, Member* Membre);
    virtual bool DeleteSpecialTest(Book* BooktoReturn, Member* Membre);
    static bool BorrowBook (Member* Membre, Book* BooktoBorrow);
    static bool ReturnBook (Member* Membre, Book*BooktoReturn);
    void setStatus(Bookstatus newStatus);
    void AddBorrowedBy(Member* newBorrower);
    void DeleteBorrowedBy(Member* oldBorrower);
    static int totalBooks();
};

#endif
