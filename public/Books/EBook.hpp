#ifndef EBOOK_HPP
#define EBOOK_HPP

#include "Books/Book.hpp"

class EBook : public Book {
private:
    std::string downloadUrl_;
    int fileSize_;

public:
    EBook(std::string title, std::string author, std::string url, int size);
    EBook(const EBook& other);
    EBook* Clone() const override;
    void GetInfo() const override;
    std::string Url() const;
    int size() const;
    bool SpecialTest(Book* bookToBorrow, Member* member) override;
    bool DeleteSpecialTest(Book* bookToReturn, Member* member) override;
};

#endif
