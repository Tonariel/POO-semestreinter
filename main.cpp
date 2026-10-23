#include <iostream>
#include <memory>

#include "Catalog.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

int main()
{
    std::cout << "Membres au depart : "
              << Member::TotalMembers() << std::endl;

    {
        Catalog<Member> members;

        members.Add(
        std::make_unique<StudentMember>(
        "Jean", "Dupont", "E001", "Informatique")
);

        members.Add(
        std::make_unique<TeacherMember>(
        "Paul", "Martin", "P001", "Mathematiques")
);
        std::cout << "Nombr>e de membres : "
                  << members.Size() << std::endl;

        for (std::size_t i = 0; i < members.Size(); i++) {
            Member* member = members.Get(i);

            if (member != nullptr) {
                member->GetInfo();
            }
        }
    }

    std::cout << "Membres apres destruction : "
              << Member::TotalMembers() << std::endl;

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
