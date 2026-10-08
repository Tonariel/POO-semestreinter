
#include "Book.hpp"
#include "Student.hpp"
#include "Library.hpp"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main() {
    bool ok = true;

    auto test = [&](const string& nom, bool resultat, bool attendu = true) {
        cout << nom << " : " << (resultat ? "True" : "False");
        cout << (resultat == attendu ? " [OK]" : " [ECHEC]") << endl;
        if (resultat != attendu) ok = false;
    };

    auto compteur = [&](const string& etape, int attendu) {
        int total = Book::totalBooks();
        cout << "[compteur] " << etape << " : " << total << endl;
        test("Compteur attendu = " + to_string(attendu),
             total == attendu);
    };

    cout << "\n=== Compteur au demarrage ===\n";
    compteur("Initial", 0);

    {
        cout << "\n=== Creation de la bibliotheque ===\n";
        Library library;

        library.AddBook("Dune", "Frank Herbert");
        library.AddBook("Fondation", "Isaac Asimov");
        library.AddBook("Le Petit Prince", "Antoine de Saint-Exupery");
        library.AddBook("1984", "George Orwell");
        library.AddBook("Les Miserables", "Victor Hugo");
        library.AddBook("L'Etranger", "Albert Camus");

        compteur("Apres creation", 6);
        test("Catalogue de 6 livres", library.Size() == 6);
        library.DisplayCatalog();

        Book* b1 = library.FindBook("Dune");
        Book* b2 = library.FindBook("Fondation");
        Book* b3 = library.FindBook("Le Petit Prince");
        Book* b4 = library.FindBook("1984");
        Book* b5 = library.FindBook("Les Miserables");
        Book* b6 = library.FindBook("L'Etranger");

        if (!b1 || !b2 || !b3 || !b4 || !b5 || !b6) {
            cerr << "Erreur : livre introuvable !" << endl;
            return 1;
        }

        test("Recherche inexistante",
             library.FindBook("Inconnu") == nullptr);

        {
            Student marie("Marie", "Tremblay", "20240001");
            Student hugo("Hugo", "Lambert", "20240002");

            cout << "\n=== Emprunts ===\n";
            test("Dune disponible",
                 b1->Status() == Bookstatus::Available);

            test("Marie emprunte Dune", marie.BorrowBook(*b1));
            compteur("Apres emprunt de Dune", 7);

            test("Dune marque emprunte",
                 b1->Status() == Bookstatus::Borrowed);

            test("Hugo emprunte Dune",
                 hugo.BorrowBook(*b1), false);

            cout << "\n=== Limite des emprunts ===\n";
            test("Fondation", marie.BorrowBook(*b2));
            test("Le Petit Prince", marie.BorrowBook(*b3));
            test("1984", marie.BorrowBook(*b4));
            test("Les Miserables", marie.BorrowBook(*b5));

            compteur("Apres 5 emprunts", 11);

            test("Sixieme emprunt", marie.BorrowBook(*b6), false);
            compteur("Apres refus", 11);

            cout << "\n=== Retours ===\n";
            test("Retour de Dune", marie.ReturnBook(*b1));
            compteur("Apres retour", 10);

            test("Dune disponible",
                 b1->Status() == Bookstatus::Available);

            test("Retour invalide", marie.ReturnBook(*b1), false);
            test("Nouvel emprunt", marie.BorrowBook(*b6));

            compteur("Apres nouvel emprunt", 11);

            cout << "\n=== Etat des etudiants ===\n";
            marie.GetInfo();
            hugo.GetInfo();

        } // Destruction des etudiants

        cout << "\n=== Destruction des emprunts ===\n";
        compteur("Apres destruction des etudiants", 6);
        test("Originaux redevenus disponibles",
             b2->Status() == Bookstatus::Available &&
             b6->Status() == Bookstatus::Available);

        cout << "\n=== Copie de Library ===\n";
        {
            Library copie(library);

            test("Copie de 6 livres", copie.Size() == 6);
            test("Adresses independantes",
                 copie.FindBook("Dune") != b1);

            compteur("Apres copie", 12);

            Library autre;
            autre = library;

            test("Affectation profonde",
                 autre.Size() == 6 &&
                 autre.FindBook("Dune") != b1);

            compteur("Apres affectation", 18);

            Library deplacee(std::move(autre));

            test("Deplacement",
                 deplacee.Size() == 6 && autre.Size() == 0);
        }

        compteur("Apres destruction des copies", 6);

    } // Destruction de Library

    cout << "\n=== Verification finale ===\n";
    compteur("Final", 0);

    cout << (ok ? "\nTOUS LES TESTS VALIDES\n"
                : "\nDES TESTS RESTENT A CORRIGER\n");

    return ok ? 0 : 1;
}
