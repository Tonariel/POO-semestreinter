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
    ::Catalog<Book> books_;
    ::Catalog<Member> members_;


public:
    Library() = default;
    ~Library();

    // Copie interdite : les catalogues possedent leurs objets
    Library(const Library& other) = delete;
    Library& operator=(const Library& other) = delete;

    // Deplacement autorise
    Library(Library&& other) noexcept;
    Library& operator=(Library&& other) noexcept;

    Book* AddBook(std::unique_ptr<Book> book);

    Book* GetBook(std::size_t index);
    const Book* GetBook(std::size_t index) const;

    Book* FindBook(const std::string& title);
    const Book* FindBook(const std::string& title) const;
    void DisplayCatalog() const;
    std::size_t Size() const;

    // Gestion des membres
    Member* AddMember(std::unique_ptr<Member> member);

    Member* GetMember(std::size_t index);
    const Member* GetMember(std::size_t index) const;
    // Recherche d'un membre par son identifiant
    Member* FindMemberById(const std::string& id);
    const Member* FindMemberById(const std::string& id) const;

    std::size_t MemberCount() const;

    void DisplayMembers() const;
};

#endif
