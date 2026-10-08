
#include "Library.hpp"
#include <iostream>
#include <utility>

using namespace std;


// ==================================================
// TACHE 3 : GESTION DU CATALOGUE
// ==================================================

// Ajouter un livre dans la bibliotheque
void Library::AddBook(const std::string& title,
                      const std::string& author) {

    Book* newBook = new Book(title, author);

    try {
        Catalog.push_back(newBook);
    }
    catch (...) {
        delete newBook;
        throw;
    }
}


// Rechercher un livre par son titre
Book* Library::FindBook(const std::string& title) const {

    for (Book* book : Catalog) {

        if (book->title() == title) {
            return book;
        }
    }

    return nullptr;
}


// Afficher le catalogue
void Library::DisplayCatalog() const {

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


// Retourner le nombre de livres
std::size_t Library::Size() const {
    return Catalog.size();
}


// Liberer la memoire du catalogue
void Library::ClearCatalog() noexcept {

    for (Book* book : Catalog) {
        delete book;
    }

    Catalog.clear();
}


// Destructeur
Library::~Library() {

    cout << "[Library] Destruction du catalogue ("
         << Catalog.size()
         << " livres)" << endl;

    ClearCatalog();
}


// ==================================================
// TACHE 4 : COPIE ET DEPLACEMENT DE LIBRARY
// ==================================================

// Constructeur par copie : copie profonde
Library::Library(const Library& other) {

    Catalog.reserve(other.Catalog.size());

    try {
        for (Book* book : other.Catalog) {
            Catalog.push_back(new Book(*book));
        }
    }
    catch (...) {
        ClearCatalog();
        throw;
    }
}


// Operateur d'affectation par copie
Library& Library::operator=(const Library& other) {

    if (this != &other) {

        Library temporary(other);

        Catalog.swap(temporary.Catalog);
    }

    return *this;
}


// Constructeur de deplacement
Library::Library(Library&& other) noexcept {

    Catalog.swap(other.Catalog);
}


// Operateur d'affectation par deplacement
Library& Library::operator=(Library&& other) noexcept {

    if (this != &other) {

        ClearCatalog();

        Catalog.swap(other.Catalog);
    }

    return *this;
}
