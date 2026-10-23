#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <cstddef>
#include "Interfaces/IDisplayable.hpp"

class Book;

class Member : public IDisplayable {
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
    void GetInfo() const override;

    // Gestion des emprunts
    bool BorrowBook(Book& BookToBorrow);
    bool ReturnBook(Book& BookToReturn);

    // Verification des emprunts
    bool CanBorrow() const;
    std::size_t GetBorrowedCount() const;

    // Limite definie par chaque classe fille
    virtual std::size_t GetBorrowLimit() const = 0;

    // Type du membre défini par chaque classe fille
    virtual std::string GetMemberType() const = 0;

    // Recuperer l'identifiant du membre
    const std::string& GetId() const;

    static int TotalMembers();
};

#endif
