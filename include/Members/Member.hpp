#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <cstddef>

class Book;

class Member {
private:
    std::string Name_;
    std::string Surname_;
    std::string ID_unique;

    // Copies personnelles des livres empruntes
    std::vector<Book*> BorrowedBooks;

    static int totalMembers_;

public:
    // Constructeur
    Member(std::string Name,
           std::string Surname,
           std::string Id);

    // Destructeur virtuel
    virtual ~Member();

    // Interdire la copie et le deplacement
    Member(const Member&) = delete;
    Member& operator=(const Member&) = delete;
    Member(Member&&) = delete;
    Member& operator=(Member&&) = delete;

    // Informations du membre
    virtual void GetInfo() const;

    // Gestion des emprunts
    bool BorrowBook(Book& BookToBorrow);
    bool ReturnBook(Book& BookToReturn);

    // Verification des emprunts
    bool CanBorrow() const;
    std::size_t GetBorrowedCount() const;

    // Limite definie par chaque classe fille
    virtual std::size_t GetBorrowLimit() const = 0;

    static int TotalMembers();
};

#endif
