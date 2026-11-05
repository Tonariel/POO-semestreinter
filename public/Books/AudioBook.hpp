#ifndef AUDIOBOOK_HPP
#define AUDIOBOOK_HPP

#include "Books/Book.hpp"

class AudioBook : public Book {
private:
    int Duration_;
    std::string Narator_;
    std::string Langage_;

public:
    AudioBook(std::string title, std::string author, int Duration,
              std::string Narator, std::string Langage);
    AudioBook(const AudioBook& other);
    AudioBook* Clone() const override;
    void GetInfo() const override;
    int Duration() const;
    std::string Narator() const;
    std::string Langage() const;
    bool SpecialTest(Book* bookToBorrow, Member* member) override;
    bool DeleteSpecialTest(Book* bookToReturn, Member* member) override;
};

#endif
