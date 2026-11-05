#include "Books/PhysicalBook.hpp"

#include <iostream>

using namespace std;

PhysicalBook::PhysicalBook(std::string title, std::string author,
                           std::string Localisation, Bookstate state)
    : Book{title, author}, Localisation_{Localisation}, state_{state} {}

PhysicalBook::PhysicalBook(const PhysicalBook& other)
    : Book(other), Localisation_(other.Localisation_), state_(other.state_) {}

PhysicalBook* PhysicalBook::Clone() const {
    return new PhysicalBook(*this);
}

void PhysicalBook::GetInfo() const {
    cout << "[Papier] " << title() << " par " << author()
         << " | rayon " << Localisation_ << " | ";

    switch (state_) {
        case Bookstate::New:
            cout << "neuf";
            break;
        case Bookstate::Good:
            cout << "bon etat";
            break;
        case Bookstate::Damaged:
            cout << "endommage";
            break;
    }
}

string PhysicalBook::Localisation() const {
    return Localisation_;
}

void PhysicalBook::SetState(Bookstate Newstate) {
    state_ = Newstate;
}

Bookstate PhysicalBook::State() const {
    return state_;
}

bool PhysicalBook::SpecialTest(Book*, Member* member) {
    if (Status() == Bookstatus::Borrowed || Status() == Bookstatus::UnAvailable) {
        cout << "the book is already borrowed" << endl;
        return false;
    }
    if (State() == Bookstate::Damaged) {
        setStatus(Bookstatus::UnAvailable);
        return false;
    }
    AddBorrowedBy(member);
    setStatus(Bookstatus::Borrowed);
    return true;
}

bool PhysicalBook::DeleteSpecialTest(Book*, Member* member) {
    DeleteBorrowedBy(member);
    setStatus(Bookstatus::Available);
    return true;
}
