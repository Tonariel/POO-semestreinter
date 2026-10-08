
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.hpp"
#include <string>
#include <vector>
#include <cstddef>

class Library {
private:
    // La bibliotheque possede les livres du catalogue
    std::vector<Book*> Catalog;

    // Supprimer les livres du catalogue
    void ClearCatalog() noexcept;

public:
    // Constructeur par defaut
    Library() = default;

    // Destructeur
    ~Library();

    // Regle des cinq : copie
    Library(const Library& other);
    Library& operator=(const Library& other);

    // Regle des cinq : deplacement
    Library(Library&& other) noexcept;
    Library& operator=(Library&& other) noexcept;

    // Gestion du catalogue
    void AddBook(const std::string& title,
                 const std::string& author);

    Book* FindBook(const std::string& title) const;

    void DisplayCatalog() const;

    std::size_t Size() const;
};

#endif
