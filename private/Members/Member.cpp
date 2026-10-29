#include "Members/Member.hpp"
#include "Book.hpp"

#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>

int Member::totalMembers_ = 0;

//Constructeur
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

//Destructeur
Member::~Member()
{
    std::cout << "- Destruct Member : "
              << Name_ << " " << Surname_
              << std::endl;

    for (Book* book : BorrowedBooks) {
        delete book;
    }
    BorrowedBooks.clear();
}

//Affichage des informations du membre
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

void Member::AddBorrowedBook(Book* book)
{
    if (book != nullptr) {
        BorrowedBooks.Add book;
    }
}



//Verification de la capacite d'emprunt
bool Member::CanBorrow() const
{
    return GetBorrowedCount() < GetBorrowLimit();
}

// Retourne le nom du membre (pour StudentMember)
string Member::ReturnName() const
{
    return Name_;
}

//Nombre de livres actuellement empruntes
std::size_t Member::GetBorrowedCount() const
{
    return BorrowedBooks.size();
}

//Identifiant unique du membre
const std::string& Member::GetId() const
{
    return ID_unique;
}

//Compteur global de membres
int Member::TotalMembers()
{
    return totalMembers_;
}

// Recuperer un livre original a partir de son titre et de son auteur
Book* Member::GetReleasedBook(const std::string& title, const std::string& author)
{
    auto it = std::find_if(BorrowedBooks.begin(), BorrowedBooks.end(),
                           [&title, &author](const Book* book) {
                               return book->title() == title && book->author() == author;
                           });

    if (it != BorrowedBooks.end()) {
        Book* originalBook = *it;
        BorrowedBooks.erase(it);
        return originalBook;
    }

    return nullptr; // Livre non trouve
}