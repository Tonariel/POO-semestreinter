#include "Books/Book.hpp"

#include <iostream>

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

void Book::Destroy_Clone (Book *Copy){
    delete Copy;
}

Bookstatus Book::Status() const {
    return status;
}

void Book::BorrowedBy() const {
    for (size_t i=0; i<borrowedBy_.size(); ++i) {
        cout << borrowedBy_[i] << endl;
    }
    cout << "nobody" << endl;
}

int Book::BorrowedBy_Size(){
    return borrowedBy_.size();
}

string Book::title() const {
    return title_;
}

std::string Book::author() const {
    return author_;
}

bool Book::SpecialTest (Book* BooktoBorrow, Member* Membre){
    BooktoBorrow->AddBorrowedBy(Membre);
    BooktoBorrow->status = Bookstatus::Borrowed;
    return true;
}

bool Book::DeleteSpecialTest (Book* BooktoReturn, Member* Membre){
    BooktoReturn->setStatus(Bookstatus::Available);
    BooktoReturn->DeleteBorrowedBy(Membre);
    return true;
}

bool Book::BorrowBook (Member* Membre, Book* BooktoBorrow){
    if (Membre == nullptr || BooktoBorrow == nullptr) {
        return false;
    }
    if(Membre->CanBorrow() == false){
        cout << "Member cannot borrow more books." << endl;
        return false;
    }
    if (BooktoBorrow->SpecialTest(BooktoBorrow, Membre) == false){
        return false;
    }
    Book* Copy = BooktoBorrow->Clone();
    Membre->AddBorrowedBook(Copy);
    return true;
}

bool Book::ReturnBook (Member* Membre, Book* BooktoReturn){
    if (Membre == nullptr || BooktoReturn == nullptr) {
        return false;
    }

    Book* Copy = Membre->GetReleasedBook(BooktoReturn->title_, BooktoReturn->author_);
    if (Copy == nullptr) {
        return false;
    }

    delete Copy;
    return BooktoReturn->DeleteSpecialTest(BooktoReturn, Membre);
}

void Book::setStatus(Bookstatus newStatus) {
    status = newStatus;
}

void Book::AddBorrowedBy(Member* newBorrower) {
    borrowedBy_.push_back(newBorrower->ReturnName());
}

void Book::DeleteBorrowedBy(Member* oldBorrower) {
    for (size_t i=0; i<borrowedBy_.size(); ++i) {
        if (borrowedBy_[i] == oldBorrower->ReturnName()) {
            borrowedBy_.erase(borrowedBy_.begin() + i);
            break;
        }
    }
}

int Book::totalBooks() {
    return totalBooks_;
}