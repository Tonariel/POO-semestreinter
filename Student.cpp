#include "Student.h"
#include <iostream>

using namespace std;

bool BorrowBook(Book& BookToBorrow){

        if (CanBorrow_ == false){
            cout << Name_ <<(" a atteint ça limite de livres, impossible d'empreinter ")<< BookToBorrow.title << endl;
            return false;
        }

        if (BookToBorrow.status == Bookstatus::Borrowed){
            cout << Name_ <<(" ne peut pas empreinter le livre ") << BookToBorrow.title <<(" le livre est deja empreinter par ")<< BookToBorrow.BorrowedBy <<endl;
            return false;
        }

        BorrowedBooks.push_back(BookToBorrow.title);
        BookToBorrow.status = Bookstatus::Borrowed;
        BookToBorrow.BorrowedBy = Name_;
        cout << Name_ <<(" a empreinter le livre ")<< BookToBorrow.title << endl;

        if (BorrowedBooks.size() >= 5){
            CanBorrow_ = false;
            cout << Name_ << (" a atteint ça limite 5/5 empreinter") << endl;
        }
        return true;
    }


    bool ReturnBook(Book& BookToReturn){
        
        BookToReturn.status = Bookstatus::Available;

        for(size_t i = 0 ; i < BorrowedBooks.size() ; i++){
            if (BorrowedBooks[i] == BookToReturn.title){
                BorrowedBooks.erase(BorrowedBooks.begin() + i);
            }
        }

        if (BorrowedBooks.size() < 5){
            CanBorrow_ = true;
        }

        BookToReturn.BorrowedBy="";

        cout << Name_ <<(" a rendu le livre ")<< BookToReturn.title << endl;
        return true;
    }
};