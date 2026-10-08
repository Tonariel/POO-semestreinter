
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.hpp"
#include <string>
#include <vector>
#include <cstddef>

class Library {
private:
    std::vector<Book*> Catalog;

    void ClearCatalog() noexcept;

public:
    Library() = default;

    // Copie
    Library(const Library& other);
    Library& operator=(const Library& other);

    // Deplacement
    Library(Library&& other) noexcept;
    Library& operator=(Library&& other) noexcept;

    // Destructeur
    ~Library();

    // Gestion du catalogue
    void AddBook(const std::string& title,
                 const std::string& author);

    Book* FindBook(const std::string& title) const;

    void DisplayCatalog() const;

    std::size_t Size() const;
};

#endif
