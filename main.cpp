#include "Book.hpp"
#include "Student.hpp"

#include <iostream>
using namespace std;

int main(){
    Book b1{"Dune", "Frank Herbert"}; 
    Book b2{"Fondation", "Isaac Asimov"};
    Book b3{"Le Petit Prince","Antoine de Saint-Exupéry"};
    Book b4{"1984","George Orwell"};
    Book b5{"Les Misérables","Victor Hugo"};
    Book b6{"L'Étranger","Albert Camus"};


    Student s1{"Marie","Tremblay","20240001"};
    Student s2{"Hugo","Lambert","20240002"};


    s1.BorrowBook(b1);
    s2.BorrowBook(b1);
    s1.ReturnBook(b1);
    s1.BorrowBook(b2);
    s1.BorrowBook(b3);
    s1.BorrowBook(b4);
    s1.BorrowBook(b5);
    s1.BorrowBook(b6);
    s1.BorrowBook(b1);
    s1.GetInfo();

    cout << "Total books in library: " << Book::totalBooks() << endl;

    return 0;
}