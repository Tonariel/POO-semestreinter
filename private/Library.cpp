
#include "Library.hpp"

#include <iostream>
#include <utility>

using namespace std;


// ==========================================
// GESTION DES LIVRES (ancienne version)
// ==========================================

// Ajouter un livre dans la bibliotheque
Book* Library::AddBook(std::unique_ptr<Book> book)
{
    if (book == nullptr) {
        return nullptr;
    }

    Book* addedBook = book.get();

    books_.Add(std::move(book));

    return addedBook;
}


// Recherche modifiable
Book* Library::FindBook(const std::string& title)
{
    for (std::size_t i = 0; i < books_.Size(); ++i) {
        Book* book = books_.Get(i);

        if (book != nullptr && book->title() == title) {
            return book;
        }
    }

    return nullptr;
}

// Recherche en lecture seule
const Book* Library::FindBook(const std::string& title) const
{
    for (std::size_t i = 0; i < books_.Size(); ++i) {
        const Book* book = books_.Get(i);

        if (book != nullptr && book->title() == title) {
            return book;
        }
    }

    return nullptr;
}

// Afficher le catalogue des livres
void Library::DisplayCatalog() const
{
    std::cout << "\n=== Catalogue des livres ===\n";

    for (std::size_t i = 0; i < books_.Size(); ++i) {
        const Book* book = books_.Get(i);

        if (book != nullptr) {
            book->Display();

            std::cout << " | "
                      << (book->Status() == Bookstatus::Available
                          ? "Disponible"
                          : "Emprunte")
                      << '\n';
        }
    }
}

std::size_t Library::Size() const
{
    return books_.Size();
}

Book* Library::GetBook(std::size_t index)
{
    return books_.Get(index);
}

const Book* Library::GetBook(std::size_t index) const
{
    return books_.Get(index);
}

// Ajouter un membre dans la bibliotheque
Member* Library::AddMember(std::unique_ptr<Member> member)
{
    // Refuser un pointeur nul
    if (member == nullptr) {
        return nullptr;
    }

    // Refuser un identifiant deja utilise
    if (FindMemberById(member->GetId()) != nullptr) {
        return nullptr;
    }

    // Ajouter le membre au catalogue
    Member* nouveauMembre = member.get();

    members_.Add(std::move(member));

    return nouveauMembre;
}

// Recuperer un membre par son indice
Member* Library::GetMember(std::size_t index)
{
    return members_.Get(index);
}


// Recuperer un membre en lecture seule
const Member* Library::GetMember(std::size_t index) const
{
    return members_.Get(index);
}


// Nombre de membres dans la bibliotheque
std::size_t Library::MemberCount() const
{
    return members_.Size();
}

// Afficher les informations de tous les membres
void Library::DisplayMembers() const
{
    cout << "\n=== Membres de la bibliotheque ==="
         << endl;

    DisplayGenericCatalog(members_);
}


// Destruction et déplacement de librar
Library::~Library()
{
    std::cout << "[Library] Destruction de la bibliotheque\n";
}

// Constructeur de deplacement
Library::Library(Library&& other) noexcept
    : books_(std::move(other.books_)),
      members_(std::move(other.members_))
{
}

// Operateur d'affectation par deplacement
Library& Library::operator=(Library&& other) noexcept
{
    if (this != &other) {
        members_ = std::move(other.members_);
        books_ = std::move(other.books_);
    }

    return *this;
}