
#include "Library.hpp"

#include <iostream>
#include <utility>

using namespace std;


// ==========================================
// GESTION DES LIVRES (ancienne version)
// ==========================================

// Ajouter un livre dans la bibliotheque
Book* Library::AddBook(const std::string& title,
                       const std::string& author)
{
    Book* newBook = new Book(title, author);

    try {
        Catalog.push_back(newBook);
    }
    catch (...) {
        delete newBook;
        throw;
    }

    return newBook;
}


// Rechercher un livre par son titre
Book* Library::FindBook(const std::string& title) const
{
    for (Book* book : Catalog) {
        if (book->title() == title) {
            return book;
        }
    }

    return nullptr;
}


// Afficher le catalogue des livres
void Library::DisplayCatalog() const
{
    cout << "\n=== Catalogue de la bibliotheque ==="
         << endl;

    for (Book* book : Catalog) {
        cout << book->title()
             << " par " << book->author()
             << " : ";

        if (book->Status() == Bookstatus::Available) {
            cout << "Disponible";
        }
        else {
            cout << "Emprunte";
        }

        cout << endl;
    }
}


// Nombre de livres
std::size_t Library::Size() const
{
    return Catalog.size();
}


// Liberer les livres du catalogue
void Library::ClearCatalog() noexcept
{
    for (Book* book : Catalog) {
        delete book;
    }

    Catalog.clear();
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


// Afficher les membres par polymorphisme
void Library::DisplayMembers() const
{
    cout << "\n=== Membres de la bibliotheque ==="
         << endl;

    for (std::size_t i = 0; i < members_.Size(); i++) {
        const Member* membre = members_.Get(i);

        if (membre != nullptr) {
            membre->GetInfo();
            cout << endl;
        }
    }
}

// Destructeur
Library::~Library()
{
    cout << "[Library] Destruction de la bibliotheque"
         << endl;

    // Les membres sont detruits avant les livres.
    members_ = ::Catalog<Member>{};

    ClearCatalog();
}


// Constructeur de deplacement
Library::Library(Library&& other) noexcept
    : members_(std::move(other.members_))
{
    Catalog.swap(other.Catalog);
}


// Operateur d'affectation par deplacement
Library& Library::operator=(Library&& other) noexcept
{
    if (this != &other) {

        // Liberer les anciens membres
        members_ = ::Catalog<Member>{};

        // Liberer les anciens livres
        ClearCatalog();

        // Recuperer les livres
        Catalog.swap(other.Catalog);

        // Recuperer les membres
        members_ = std::move(other.members_);
    }

    return *this;
}

// Recherche d'un membre par son identifiant   
Member* Library::FindMemberById(const std::string& id)
{
    for (std::size_t i = 0; i < members_.Size(); i++) {
        Member* membre = members_.Get(i);

        if (membre != nullptr && membre->GetId() == id) {
            return membre;
        }
    }

    return nullptr;
}

const Member* Library::FindMemberById(const std::string& id) const
{
    for (std::size_t i = 0; i < members_.Size(); i++) {
        const Member* membre = members_.Get(i);

        if (membre != nullptr && membre->GetId() == id) {
            return membre;
        }
    }

    return nullptr;
}
