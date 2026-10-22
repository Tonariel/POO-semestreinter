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

EBook::EBook(std::string title, std::string author, std::string url, int size)
    :Book{title, author}, downloadUrl_{url}, fileSize_{size}{}

string EBook::Url() const{
    return downloadUrl_;
}

int EBook::size() const{
    return fileSize_;
}

PhysicalBook::PhysicalBook(std::string title, std::string author, std::string Localisation, std::string state)
    :Book{title, author}, Localisation_{Localisation}, state_{state}{}

string PhysicalBook::Localisation() const{
    return Localisation_;
}

Bookstate PhysicalBook::SetState(string Newstate){
    state_ = Newstate;
} 

Bookstate PhysicalBook::State() const{
    return state_;
}

AudioBook::AudioBook(std::string title, std::string author, int Duration, std::string Narator, std::string Langage)
    :Book{title, author}, Duration_{Duration}, Narator_{Narator}, Language_{Language}{}

int AudioBook::Duration() const{
    return Duration_;
}

string AudioBook::Narator() const{
    return Narator_;
}

string AudioBook::Langage() const{
    return Langage_;
}
