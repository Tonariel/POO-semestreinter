#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum class Bookstatus{
    Borrowed,
    Available
};

struct Book {
    string title;
    string author;
    Bookstatus status = Bookstatus::Available;
    string BorrowedBy = "";
};


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


}