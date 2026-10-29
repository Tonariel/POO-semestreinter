#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <memory>
#include <cstddef>

#include "Interfaces/IDisplayable.hpp"

class Book;

class Member : public IDisplayable {
private:
    std::string Name_;
    std::string Surname_;
    std::string ID_unique;

    static int totalMembers_;

    std::vector<Book*> BorrowedBooks;


public:
    // Constructeur et destructeur
    Member(std::string Name,
           std::string Surname,
           std::string Id);

    virtual ~Member();

    // Copie et deplacement interdits
    Member(const Member&) = delete;
    Member& operator=(const Member&) = delete;
    Member(Member&&) = delete;
    Member& operator=(Member&&) = delete;

    // Affichage polymorphe
    void GetInfo() const override;
    void AddBorrowedBook(Book* book);


    // Verification de la capacite d'emprunt
    bool CanBorrow() const;
    std::size_t GetBorrowedCount() const;

    // Limite propre au type de membre
    virtual std::size_t GetBorrowLimit() const = 0;

    // Type du membre
    virtual std::string GetMemberType() const = 0;

    // Identifiant unique
    const std::string& GetId() const;

    // Compteur global
    static int TotalMembers();
};

#endif
