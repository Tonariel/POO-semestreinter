#include "Book.hpp"
#include "Student.hpp"

#include <iostream>
using namespace std;

int main(){
    cout << "=== compteur au démarage ===" << endl;
    cout << Book::totalBooks() << "Livres dans la Library"<< endl;

    cout << "\n=== Remplissage de la bibliothèque ===" << endl;
    Book b1{"Dune", "Frank Herbert"}; 
    Book b2{"Fondation", "Isaac Asimov"};
    Book b3{"Le Petit Prince","Antoine de Saint-Exupéry"};
    Book b4{"1984","George Orwell"};
    Book b5{"Les Misérables","Victor Hugo"};
    Book b6{"L'Étranger","Albert Camus"};


    cout << "\nLivres dans la bibliothèque : " << endl;
    cout << b1.title() << " de " << b1.author() << "status: " << b1.Status() << endl;
    cout << b2.title() << " de " << b2.author() << "status: " << b2.Status() << endl;
    cout << b3.title() << " de " << b3.author() << "status: " << b3.Status() << endl;
    cout << b4.title() << " de " << b4.author() << "status: " << b4.Status() << endl;
    cout << b5.title() << " de " << b5.author() << "status: " << b5.Status() << endl;
    cout << b6.title() << " de " << b6.author() << "status: " << b6.Status() << endl;

    Student s1{"Marie","Tremblay","20240001"};
    Student s2{"Hugo","Lambert","20240002"};

    cout << "\n=== Emprunts et copies ===" << endl;
    cout << "Dune avant emprunt: " << b1.Status() << endl;
    Book b1_copy = b1;
    s1.BorrowBook(b1);
    s2.BorrowBook(b1);

    cout << "\nCas Limite le 6eme emprunt" << endl;
    s1.BorrowBook(b2);
    s1.BorrowBook(b3);
    s1.BorrowBook(b4);
    s1.BorrowBook(b5);
    s1.BorrowBook(b6);

    cout << "\n=== Retours ===" << endl;
    ~book b1_copy;
    s1.ReturnBook(b1);
    s2.ReturnBook(b1);
    s2.BorrowBook(b1);


    cout << "\n=== Etat final ===" << endl;

    cout << "\n=== Sortie de portee ===" << endl;
    


    cout << "Total books in library: " << Book::totalBooks() << endl;

    return 0;
}