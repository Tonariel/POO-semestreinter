#include "Members/Member.hpp"
#include "Book.hpp"

#include <iostream>
#include <utility>

int Member::totalMembers_ = 0;

// Constructeur
Member::Member(std::string Name,
               std::string Surname,
               std::string Id)
    : Name_(std::move(Name)),
      Surname_(std::move(Surname)),
      ID_unique(std::move(Id))
{
    std::cout << "+ Construct Member : "
              << Name_ << " " << Surname_
              << std::endl;
}

// Destructeur
Member::~Member()
{
    // Liberation des copies personnelles
    for (Book* book : BorrowedBooks) {
        delete book;
    }

    BorrowedBooks.clear();

    std::cout << "- Destruct Member : "
              << Name_ << " " << Surname_
              << std::endl;
}

// Afficher les informations du membre
void Member::GetInfo() const
{
    std::cout << "Nom : " << Name_ << std::endl;
    std::cout << "Prenom : " << Surname_ << std::endl;
    std::cout << "Identifiant : " << ID_unique << std::endl;

    std::cout << "Emprunts : "
              << GetBorrowedCount()
              << " / "
              << GetBorrowLimit()
              << std::endl;
}

// Verifier la possibilite d'emprunter
bool Member::CanBorrow() const
{
    return GetBorrowedCount() < GetBorrowLimit();
}

// Nombre de livres actuellement empruntes
std::size_t Member::GetBorrowedCount() const
{
    return BorrowedBooks.size();
}
