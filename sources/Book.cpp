#include "Book.hpp"

using namespace std;

Book::Book(std::string title, std::string author)
    : title_(title), author_(author) {}


Bookstatus Book::Status() const {
    return status;
}

string Book::BorrowedBy() const {
    return borrowedBy_;
}

string Book::title() const {
    return title_;
}

void Book::setStatus(Bookstatus newStatus) {
    status = newStatus;
}

void Book::setBorrowedBy(const std::string& newBorrower) {
    borrowedBy_ = newBorrower;
}