#include "Books/EBook.hpp"

#include <iostream>

using namespace std;

EBook::EBook(std::string title, std::string author, std::string url, int size)
    : Book{title, author}, downloadUrl_{url}, fileSize_{size} {}

EBook::EBook(const EBook& other)
    : Book(other), downloadUrl_(other.downloadUrl_), fileSize_(other.fileSize_) {}

EBook* EBook::Clone() const {
    return new EBook(*this);
}

void EBook::GetInfo() const {
    cout << "[Numerique] " << title() << " par " << author()
         << " | " << fileSize_ << " Mo"
         << " | " << downloadUrl_;
}

string EBook::Url() const {
    return downloadUrl_;
}

int EBook::size() const {
    return fileSize_;
}

bool EBook::SpecialTest(Book*, Member* member) {
    AddBorrowedBy(member);
    setStatus(Bookstatus::Available);
    return true;
}

bool EBook::DeleteSpecialTest(Book*, Member* member) {
    DeleteBorrowedBy(member);
    setStatus(Bookstatus::Available);
    return true;
}
