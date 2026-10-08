#include "Book.hpp"

using namespace std;

int Book::totalBooks_ = 0;

Book::Book(std::string title, std::string author)
    : title_(title), author_(author) {
    totalBooks_++;
    cout << "+ Construct " << title_ << " (count=" << totalBooks_ << ")" << endl;
}

Book::Book(const Book& other)
    : title_(other.title_), author_(other.author_), status(other.status), borrowedBy_(other.borrowedBy_) {
    totalBooks_++;
    cout << "+ Copy " << title_ << " (count=" << totalBooks_ << ")" << endl;
}

Book::~Book() {
    totalBooks_--;
    cout << "- Destruct " << title_ << " (count=" << totalBooks_ << ")" << endl;
}

Bookstatus Book::Status() const {
    return status;
}

string Book::BorrowedBy() const {
    return borrowedBy_;
}

string Book::title() const {
    return title_;
}

std::string Book::author() const {
    return author_;
}

void Book::setStatus(Bookstatus newStatus) {
    status = newStatus;
}

void Book::setBorrowedBy(const std::string& newBorrower) {
    borrowedBy_ = newBorrower;
}

int Book::totalBooks() {
    return totalBooks_;
}