#ifndef PHYSICALBOOK_HPP
#define PHYSICALBOOK_HPP

#include "Books/Book.hpp"

class PhysicalBook : public Book {
private:
    std::string Localisation_;
    Bookstate state_;

public:
    PhysicalBook(std::string title, std::string author,
                 std::string Localisation, Bookstate state);
    PhysicalBook(const PhysicalBook& other);
    PhysicalBook* Clone() const override;
    void GetInfo() const override;
    std::string Localisation() const;
    void SetState(Bookstate Newstate);
    Bookstate State() const;
    bool SpecialTest(Book* bookToBorrow, Member* member) override;
    bool DeleteSpecialTest(Book* bookToReturn, Member* member) override;
};

#endif
