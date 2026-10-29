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
    totalMembers_++;
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
    totalMembers_--;
    std::cout << "- Destruct Member : "
              << Name_ << " " << Surname_
              << std::endl;
}


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

int Member::TotalMembers()
{
    return totalMembers_;
}

// Recuperer l'identifiant du membre
const std::string& Member::GetId() const
{
    return ID_unique;
}