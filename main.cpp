#include "Book.hpp"
#include "Student.hpp"
#include "Library.hpp"

#include <iostream>
using namespace std;

int main(){
    cout << "=== compteur au démarage ===" << endl;
    cout << Book::totalBooks() << " Livres dans la Library"<< endl;

    Library* MyLib = new Library();
    cout << "\n=== Remplissage de la bibliothèque ===" << endl;
    Book* b1 = MyLib->AddBook("Dune", "Frank Herbert");
    Book* b2 = MyLib->AddBook("Fondation", "Isaac Asimov");
    Book* b3 = MyLib->AddBook("Le Petit Prince", "Antoine de Saint-Exupéry");
    Book* b4 = MyLib->AddBook("1984", "George Orwell");
    Book* b5 = MyLib->AddBook("Les Misérables", "Victor Hugo");
    Book* b6 = MyLib->AddBook("L'Étranger", "Albert Camus");



    cout << "\nLivres dans la bibliothèque : " << endl;
    MyLib->DisplayCatalog();


    Student* s1 = new Student("Marie","Tremblay","20240001");
    Student* s2 = new Student("Hugo","Lambert","20240002");

    cout << "\n=== Emprunts et copies ===" << endl;
    cout << "Dune avant emprunt: " << (b1->Status() == Bookstatus::Available ? "Disponible" : "Emprunte") << endl;
    s1->BorrowBook(*b1);
    s2->BorrowBook(*b1);

    cout << "\nCas Limite le 6eme emprunt" << endl;
    s1->BorrowBook(*b2);
    s1->BorrowBook(*b3);
    s1->BorrowBook(*b4);
    s1->BorrowBook(*b5);
    s1->BorrowBook(*b6);

    cout << "\n=== Retours ===" << endl;
    s1->ReturnBook(*b1);
    s2->ReturnBook(*b1);
    s2->BorrowBook(*b1);


    cout << "\n=== Etat final ===" << endl;
    s1->GetInfo();
    s2->GetInfo();

    cout << "\n=== Sortie de portee ===" << endl;
    delete (s1);
    delete (s2);
    delete (MyLib);
    


    cout << "\n=== Verification de l'équilibre ===" << endl;
    cout << Book::totalBooks() << " Livres dans la Library après destruction"<< endl;
    if (Book::totalBooks() == 0){
        cout << "EQUIBLIBRE autant de constructions que de destructions" << endl;
    }
    else{
        cout <<"probleme dans l'equilibre" << endl;
    }
    return 0;
}