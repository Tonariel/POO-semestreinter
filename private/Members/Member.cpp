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

void AddBorrowedBook(Book* book)
{
    
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

bool Member::BorrowBook(Book& BookToBorrow)
{
    // ETAPE 1 : Verifier la limite du membre
    if (!CanBorrow()) {
        std::cout << "Emprunt refuse : limite atteinte"
                  << std::endl;
        return false;
    }

    // ETAPE 2 : Verifier la disponibilite du livre
    if (BookToBorrow.Status() != Bookstatus::Available) {
        std::cout << "Emprunt refuse : livre indisponible"
                  << std::endl;
        return false;
    }

    // ETAPE 3 : Creer une copie polymorphe
    std::unique_ptr<Book> copie(BookToBorrow.Clone());

    if (copie == nullptr) {
        std::cout << "Emprunt refuse : copie impossible"
                  << std::endl;
        return false;
    }

    // ETAPE 4 : Enregistrer la copie
    BorrowedBooks.push_back({
        &BookToBorrow,
        std::move(copie)
    });

    // ETAPE 5 : Enregistrer l'identifiant de l'emprunteur
    try {
        BookToBorrow.setBorrowedBy(ID_unique);
    }
    catch (...) {
        // Annuler l'ajout en cas d'echec
        BorrowedBooks.pop_back();
        throw;
    }

    // ETAPE 6 : Mettre a jour le statut du livre
    BookToBorrow.setStatus(Bookstatus::Borrowed);

    std::cout << "Emprunt valide : "
              << BookToBorrow.title()
              << " par "
              << ID_unique
              << std::endl;

    return true;
}

// ==========================================
// RETOURNER UN LIVRE
// ==========================================

bool Member::ReturnBook(Book& BookToReturn)
{
    // ETAPE 1 : Rechercher l'original
    auto it = std::find_if(
        BorrowedBooks.begin(),
        BorrowedBooks.end(),
        [&BookToReturn](const BorrowRecord& emprunt) {
            return emprunt.original == &BookToReturn;
        }
    );

    // ETAPE 2 : Verifier que le membre l'a emprunte
    if (it == BorrowedBooks.end()) {
        std::cout << "Retour refuse : livre non emprunte"
                  << std::endl;
        return false;
    }

    // ETAPE 3 : Verifier la coherence du statut
    if (BookToReturn.Status() != Bookstatus::Borrowed ||
        BookToReturn.BorrowedBy() != ID_unique) {

        std::cout << "Retour refuse : etat incoherent"
                  << std::endl;
        return false;
    }

    // ETAPE 4 : Liberer le livre original
    BookToReturn.setBorrowedBy("");
    BookToReturn.setStatus(Bookstatus::Available);

    // ETAPE 5 : Supprimer l'enregistrement
    // La copie est automatiquement detruite.
    BorrowedBooks.erase(it);

    std::cout << "Retour valide : "
              << BookToReturn.title()
              << " par "
              << ID_unique
              << std::endl;

    return true;
}

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
