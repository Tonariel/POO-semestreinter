#include "Members/Member.hpp"
#include "Book.hpp"

#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>

int Member::totalMembers_ = 0;

// ==========================================
// CONSTRUCTEUR
// ==========================================

Member::Member(std::string Name,
               std::string Surname,
               std::string Id)
    : Name_(std::move(Name)),
      Surname_(std::move(Surname)),
      ID_unique(std::move(Id))
{
    totalMembers_++;

    std::cout << "+ Construct Member : "
              << Name_ << " " << Surname_
              << std::endl;
}

// ==========================================
// DESTRUCTEUR
// ==========================================

Member::~Member()
{
    // Restaurer les originaux encore empruntes.
    // Les originaux doivent toujours etre vivants ici.
    for (auto& emprunt : BorrowedBooks) {
        if (emprunt.original != nullptr &&
            emprunt.original->BorrowedBy() == ID_unique) {

            emprunt.original->setBorrowedBy("");
            emprunt.original->setStatus(Bookstatus::Available);
        }
    }

    // Liberation automatique des copies
    BorrowedBooks.clear();

    totalMembers_--;

    std::cout << "- Destruct Member : "
              << Name_ << " " << Surname_
              << std::endl;
}

// ==========================================
// AFFICHAGE DES INFORMATIONS
// ==========================================

void Member::GetInfo() const
{
    std::cout << "Type : "
              << GetMemberType() << std::endl;

    std::cout << "Nom : "
              << Name_ << std::endl;

    std::cout << "Prenom : "
              << Surname_ << std::endl;

    std::cout << "Identifiant : "
              << ID_unique << std::endl;

    std::cout << "Emprunts : "
              << GetBorrowedCount()
              << " / "
              << GetBorrowLimit()
              << std::endl;
}

void Members::AddBorrowedBook(Book* book)
{
    if (book != nullptr) {
        BorrowRecord record;
        record.original = book;
        record.copy = std::make_unique<Book>(*book);

        BorrowedBooks.push_back(std::move(record));
    }
}


// ==========================================
// VERIFICATION DE LA LIMITE D'EMPRUNT
// ==========================================

bool Member::CanBorrow() const
{
    return GetBorrowedCount() < GetBorrowLimit();
}

// ==========================================
// NOMBRE D'EMPRUNTS
// ==========================================

std::size_t Member::GetBorrowedCount() const
{
    return BorrowedBooks.size();
}

// ==========================================
// EMPRUNTER UN LIVRE
// ==========================================



// ==========================================
// IDENTIFIANT DU MEMBRE
// ==========================================

const std::string& Member::GetId() const
{
    return ID_unique;
}

// ==========================================
// COMPTEUR GLOBAL
// ==========================================

int Member::TotalMembers()
{
    return totalMembers_;
}
