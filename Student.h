#ifndef STUDENT_H
#define STUDENT_H

#include "Book.h"
#include <string>
#include <vector>

class Student {
    string Name_;
    string Surname_;
    const string ID_unique;
    vector<string> BorrowedBooks;
    bool CanBorrow_ = true;
    
public:
    Student(string Name, string Surname, string Id)
        : Name_{Name}, Surname_{Surname}, ID_unique(Id) {}


    void GetInfo()const{
        cout <<("Recherche d'info sur ") << Name_ << ("...")
        << ("\nName : ")<< Name_ 
        <<("\nSurname : ") << Surname_ 
        << ("\nId : ") << ID_unique 
        << ("\nCanBorrow : ") << (CanBorrow_ ? "Oui":"Non")
        <<("\nLivres empreintés :") << endl; 
        for (size_t i = 0 ; i < BorrowedBooks.size(); i++){
            cout << BorrowedBooks[i] << endl;
        }
    }
#endif