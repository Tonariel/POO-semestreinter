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

    // Un emprunt associe un livre original a sa copie personnelle.
    // Le membre ne possede pas l'original.
    struct BorrowRecord {
        Book* original = nullptr;
        std::unique_ptr<Book> copy;
    };

    static int totalMembers_;

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

    // Gestion des emprunts
    bool BorrowBook(Book& BookToBorrow);
    bool ReturnBook(Book& BookToReturn);

    std::vector<BorrowRecord> BorrowedBooks;


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
