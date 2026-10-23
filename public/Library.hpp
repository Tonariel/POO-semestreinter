#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.hpp"
#include "Catalog.hpp"
#include "Members/Member.hpp"

#include <string>
#include <vector>
#include <memory>
#include <cstddef>

class Library {
private:
    // Ancien catalogue des livres (provisoire)
    std::vector<Book*> Catalog;

    // Nouveau catalogue des membres
    Catalog<Member> members_;

    // Liberation des livres
    void ClearCatalog() noexcept;

public:
    Library() = default;
    ~Library();

    // Copie interdite : les catalogues possedent leurs objets
    Library(const Library& other) = delete;
    Library& operator=(const Library& other) = delete;

    // Deplacement autorise
    Library(Library&& other) noexcept;
    Library& operator=(Library&& other) noexcept;

    // Gestion des livres : code existant
    Book* AddBook(const std::string& title,
                  const std::string& author);

    Book* FindBook(const std::string& title) const;
    void DisplayCatalog() const;
    std::size_t Size() const;

    // Gestion des membres
    Member* AddMember(std::unique_ptr<Member> member);

    Member* GetMember(std::size_t index);
    const Member* GetMember(std::size_t index) const;

    std::size_t MemberCount() const;

    void DisplayMembers() const;
};

#endif
