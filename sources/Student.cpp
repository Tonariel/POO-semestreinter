
#include "Student.hpp"
#include <algorithm>

using namespace std;

Student::Student(std::string Name, std::string Surname, std::string Id)
    : Name_{Name}, Surname_{Surname}, ID_unique(Id) {}


void Student::GetInfo() const {
    std::cout << "Recherche d'info sur " << Name_ << "..."
              << "\nName : " << Name_
              << "\nSurname : " << Surname_
              << "\nId : " << ID_unique
              << "\nCanBorrow : " << (CanBorrow_ ? "Oui" : "Non")
              << "\nLivres empruntes :" << std::endl;

    for (size_t i = 0; i < BorrowedBooks.size(); i++) {
        std::cout << BorrowedBooks[i] << std::endl;
    }
}


bool Student::BorrowBook(Book& BookToBorrow) {

    if (CanBorrow_ == false) {
        std::cout << Name_
                  << " a atteint sa limite de livres, impossible d'emprunter "
                  << BookToBorrow.title() << std::endl;
        return false;
    }

    if (BookToBorrow.Status() == Bookstatus::Borrowed) {
        std::cout << Name_
                  << " ne peut pas emprunter le livre "
                  << BookToBorrow.title()
                  << ", le livre est deja emprunte par "
                  << BookToBorrow.BorrowedBy() << std::endl;
        return false;
    }

    BorrowedBooks.push_back(BookToBorrow.title());

    BookToBorrow.setStatus(Bookstatus::Borrowed);
    BookToBorrow.setBorrowedBy(Name_);

    std::cout << Name_
              << " a emprunte le livre "
              << BookToBorrow.title() << std::endl;

    if (BorrowedBooks.size() >= 5) {
        CanBorrow_ = false;
        std::cout << Name_
                  << " a atteint sa limite 5/5 emprunts"
                  << std::endl;
    }

    return true;
}


bool Student::ReturnBook(Book& BookToReturn) {

    auto it = std::find(
        BorrowedBooks.begin(),
        BorrowedBooks.end(),
        BookToReturn.title()
    );

    if (it == BorrowedBooks.end() ||
        BookToReturn.Status() != Bookstatus::Borrowed ||
        BookToReturn.BorrowedBy() != Name_) {

        std::cout << Name_
                  << " ne peut pas rendre le livre "
                  << BookToReturn.title()
                  << " car il ne l'a pas emprunte."
                  << std::endl;
        return false;
    }

    BorrowedBooks.erase(it);

    BookToReturn.setStatus(Bookstatus::Available);
    BookToReturn.setBorrowedBy("");

    if (BorrowedBooks.size() < 5) {
        CanBorrow_ = true;
    }

    std::cout << Name_
              << " a rendu le livre "
              << BookToReturn.title() << std::endl;

    return true;
}
