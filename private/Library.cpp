#include "Library.hpp"
#include <iostream>

using namespace std;



// Ajouter un livre dans la bibliotheque
Book* Library::AddBook(const std::string &title,
                      const std::string &author) {

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
Book* Library::FindBook(const string& title) const {

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


// Nombre de livres dans le catalogue
size_t Library::Size() const {
    return Catalog.size();
}



// Supprimer tous les livres du catalogue
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



// Constructeur par copie
Library::Library(const Library& other) {

    Library temporary;
    temporary.Catalog.reserve(other.Catalog.size());

    for (Book* book : other.Catalog) {
        temporary.Catalog.push_back(new Book(*book));
    }

    Catalog.swap(temporary.Catalog);
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
