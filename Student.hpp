#ifndef STUDENT_H
#define STUDENT_H

#include "Book.hpp"
#include <string>
#include <vector>
#include <iostream>

class Student {
    std::string Name_;
    std::string Surname_;
    const std::string ID_unique;
    std::vector<std::string> BorrowedBooks;
    bool CanBorrow_ = true;
    
public:
    Student(std::string Name, std::string Surname, std::string Id)
        : Name_{Name}, Surname_{Surname}, ID_unique(Id) {}


    void GetInfo()const{
        std::cout <<("Recherche d'info sur ") << Name_ << ("...")
        << ("\nName : ")<< Name_ 
        <<("\nSurname : ") << Surname_ 
        << ("\nId : ") << ID_unique 
        << ("\nCanBorrow : ") << (CanBorrow_ ? "Oui":"Non")
        <<("\nLivres empreintés :") << std::endl; 
        for (size_t i = 0 ; i < BorrowedBooks.size(); i++){
            std::cout << BorrowedBooks[i] << std::endl;
        }
    }

    bool BorrowBook(Book& BookToBorrow){

        if (CanBorrow_ == false){
            std::cout << Name_ <<(" a atteint ça limite de livres, impossible d'empreinter ")<< BookToBorrow.title << std::endl;
            return false;
        }

        if (BookToBorrow.status == Bookstatus::Borrowed){
            std::cout << Name_ <<(" ne peut pas empreinter le livre ") << BookToBorrow.title <<(" le livre est deja empreinter par ")<< BookToBorrow.BorrowedBy <<std::endl;
            return false;
        }

        BorrowedBooks.push_back(BookToBorrow.title);
        BookToBorrow.status = Bookstatus::Borrowed;
        BookToBorrow.BorrowedBy = Name_;
        std::cout << Name_ <<(" a empreinter le livre ")<< BookToBorrow.title << std::endl;

        if (BorrowedBooks.size() >= 5){
            CanBorrow_ = false;
            std::cout << Name_ << (" a atteint ça limite 5/5 empreinter") << std::endl;
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

        std::cout << Name_ <<(" a rendu le livre ")<< BookToReturn.title << std::endl;
        return true;
    }
};
#endif