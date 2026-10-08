#include "Book.hpp"

using namespace std;

Book::Book(std::string title, std::string author)
    : title(title), author(author) {}


Bookstatus Book::Status(){
    return status;
}

string Book::BorrowedBy(){
    return BorrowedBy;
}


string Book::title(){
    return title;
}