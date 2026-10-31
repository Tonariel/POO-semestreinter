#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Library.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

// ==========================================
// OUTIL DE VALIDATION
// ==========================================

int testsReussis = 0;
int testsEchoues = 0;

void Verifier(bool condition, const std::string& description)
{
    if (condition) {
        std::cout << "[OK] " << description << '\n';
        ++testsReussis;
    }
    else {
        std::cout << "[ECHEC] " << description << '\n';
        ++testsEchoues;
    }
}

// ==========================================
// AFFICHAGE VIA L'INTERFACE
// ==========================================

void DisplayObject(const IDisplayable& object)
{
    object.GetInfo();
}

// ==========================================
// PROGRAMME PRINCIPAL
// ==========================================

int main()
{
    std::cout << "\n====================================\n";
    std::cout << "   BIBLIOTHEQUE - REMISE 3\n";
    std::cout << "====================================\n";

    Verifier(Member::TotalMembers() == 0,
             "Aucun membre au depart");

    Verifier(Book::totalBooks() == 0,
             "Aucun livre au depart");

    {
        Library bibliotheque;

        // ==================================
        // TEST 1 : CREATION DES MEMBRES
        // ==================================

        std::cout << "\n=== TEST 1 : MEMBRES ===\n";

        Member* etudiant = bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Jean", "Dupont", "E001", "Informatique"
            )
        );

        Member* enseignant = bibliotheque.AddMember(
            std::make_unique<TeacherMember>(
                "Paul", "Martin", "P001", "Mathematiques"
            )
        );

        Verifier(bibliotheque.MemberCount() == 2,
                 "Deux membres dans la bibliotheque");

        Verifier(etudiant != nullptr,
                 "Etudiant cree");

        Verifier(enseignant != nullptr,
                 "Enseignant cree");

        if (etudiant == nullptr || enseignant == nullptr) {
            return 1;
        }

        Verifier(etudiant->GetBorrowLimit() == 2,
                 "Limite etudiant = 2");

        Verifier(enseignant->GetBorrowLimit() == 3,
                 "Limite enseignant = 3");

        bibliotheque.DisplayMembers();

        // ==================================
        // TEST 2 : INTERFACE POLYMORPHE
        // ==================================

        std::cout << "\n=== TEST 2 : INTERFACE ===\n";

        DisplayObject(*etudiant);
        DisplayObject(*enseignant);

        // ==================================
        // TEST 3 : RECHERCHE DES MEMBRES
        // ==================================

        std::cout << "\n=== TEST 3 : RECHERCHE ===\n";

        Verifier(
            bibliotheque.FindMemberById("E001") == etudiant,
            "Recherche etudiant par ID"
        );

        Verifier(
            bibliotheque.FindMemberById("P001") == enseignant,
            "Recherche enseignant par ID"
        );

        Verifier(
            bibliotheque.FindMemberById("X999") == nullptr,
            "Membre inexistant refuse"
        );

        const Library& lectureSeule = bibliotheque;

        Verifier(
            lectureSeule.FindMemberById("E001") != nullptr,
            "Recherche constante fonctionnelle"
        );

        // ==================================
        // TEST 4 : AJOUTS INVALIDES
        // ==================================

        std::cout << "\n=== TEST 4 : AJOUTS INVALIDES ===\n";

        Member* membreNul = bibliotheque.AddMember(nullptr);

        Verifier(membreNul == nullptr,
                 "Ajout d'un membre nul refuse");

        Member* doublon = bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Lucas", "Bernard", "E001", "Physique"
            )
        );

        Verifier(doublon == nullptr,
                 "Identifiant en double refuse");

        Verifier(bibliotheque.MemberCount() == 2,
                 "Nombre de membres inchange");

        // ==================================
        // TEST 5 : AJOUT DE SIX LIVRES
        // ==================================

        std::cout << "\n=== TEST 5 : LIVRES ===\n";

        Book* b1 = bibliotheque.AddBook(
            std::make_unique<EBook>(
                "Livre numerique 1",
                "Auteur A",
                "https://exemple.com/a",
                25
            )
        );

        Book* b2 = bibliotheque.AddBook(
            std::make_unique<PhysicalBook>(
                "Livre papier 1",
                "Auteur B",
                "Rayon A3",
                Bookstate::Good
            )
        );

        Book* b3 = bibliotheque.AddBook(
            std::make_unique<AudioBook>(
                "Livre audio 1",
                "Auteur C",
                120,
                "Narrateur A",
                "Francais"
            )
        );

        Book* b4 = bibliotheque.AddBook(
            std::make_unique<EBook>(
                "Livre numerique 2",
                "Auteur D",
                "https://exemple.com/d",
                30
            )
        );

        Book* b5 = bibliotheque.AddBook(
            std::make_unique<PhysicalBook>(
                "Livre papier 2",
                "Auteur E",
                "Rayon B2",
                Bookstate::New
            )
        );

        Book* b6 = bibliotheque.AddBook(
            std::make_unique<AudioBook>(
                "Livre audio 2",
                "Auteur F",
                90,
                "Narrateur B",
                "Francais"
            )
        );

        Verifier(bibliotheque.Size() == 6,
                 "Six livres dans le catalogue");

        Verifier(Book::totalBooks() == 6,
                 "Six objets Book vivants");

        if (!b1 || !b2 || !b3 || !b4 || !b5 || !b6) {
            std::cout << "Erreur : creation des livres\n";
            return 1;
        }

        Verifier(
            bibliotheque.FindBook("Livre papier 1") == b2,
            "Recherche d'un livre"
        );

        Verifier(
            bibliotheque.FindBook("Livre inexistant") == nullptr,
            "Livre inexistant non trouve"
        );

        Verifier(
            bibliotheque.GetBook(6) == nullptr,
            "Indice hors limites refuse"
        );

        bibliotheque.DisplayCatalog();

        // ==================================
        // TEST 6 : CLONAGE POLYMORPHE
        // ==================================

        std::cout << "\n=== TEST 6 : CLONAGE ===\n";

        {
            std::unique_ptr<Book> copie(b3->Clone());

            Verifier(copie != nullptr,
                     "Clone d'un livre audio cree");

            if (copie != nullptr) {
                Verifier(copie.get() != b3,
                         "Clone distinct de l'original");

                Verifier(copie->title() == b3->title(),
                         "Titre conserve dans le clone");

                Verifier(copie->author() == b3->author(),
                         "Auteur conserve dans le clone");
            }

            Verifier(Book::totalBooks() == 7,
                     "Compteur augmente lors du clonage");
        }

        Verifier(Book::totalBooks() == 6,
                 "Clone detruit automatiquement");

        // ==================================
        // TEST 7 : EMPRUNTS ETUDIANT
        // ==================================

        std::cout << "\n=== TEST 7 : EMPRUNTS ETUDIANT ===\n";

        bool empruntE1 = Book::BorrowBook(etudiant, b1);
        bool empruntE2 = Book::BorrowBook(etudiant, b2);

        Verifier(empruntE1,
                 "Premier emprunt etudiant");

        Verifier(empruntE2,
                 "Deuxieme emprunt etudiant");

        Verifier(etudiant->GetBorrowedCount() == 2,
                 "Etudiant possede deux copies");

        Verifier(!etudiant->CanBorrow(),
                 "Limite etudiant atteinte");

        Verifier(Book::totalBooks() == 8,
                 "Deux copies supplementaires");

        // Tentative de troisieme emprunt
        bool refusE3 = Book::BorrowBook(etudiant, b3);

        Verifier(!refusE3,
                 "Troisieme emprunt refuse");

        Verifier(etudiant->GetBorrowedCount() == 2,
                 "Nombre de copies inchange");

        bibliotheque.DisplayCatalog();

        // ==================================
        // TEST 8 : LIVRE INDISPONIBLE
        // ==================================

        std::cout << "\n=== TEST 8 : DISPONIBILITE ===\n";

        // L'etudiant a atteint sa limite.
        // On utilise l'enseignant pour isoler
        // la verification de disponibilite.
        bool refusOccupe = Book::BorrowBook(enseignant, b1);

        Verifier(!refusOccupe,
                 "Livre deja emprunte refuse");

        Verifier(enseignant->GetBorrowedCount() == 0,
                 "Aucune copie ajoutee apres refus");

        // ==================================
        // TEST 9 : RETOUR ETUDIANT
        // ==================================

        std::cout << "\n=== TEST 9 : RETOURS ETUDIANT ===\n";

        bool retourE1 = Book::ReturnBook(etudiant, b1);

        Verifier(retourE1,
                 "Premier livre rendu");

        Verifier(etudiant->GetBorrowedCount() == 1,
                 "Une copie restante");

        Verifier(etudiant->CanBorrow(),
                 "L'etudiant peut emprunter de nouveau");

        Verifier(b1->Status() == Bookstatus::Available,
                 "Livre rendu disponible");

        bool doubleRetour = Book::ReturnBook(etudiant, b1);

        Verifier(!doubleRetour,
                 "Double retour refuse");

        // ==================================
        // TEST 10 : EMPRUNTS ENSEIGNANT
        // ==================================

        std::cout << "\n=== TEST 10 : EMPRUNTS ENSEIGNANT ===\n";

        bool empruntP1 = Book::BorrowBook(enseignant, b1);
        bool empruntP2 = Book::BorrowBook(enseignant, b4);
        bool empruntP3 = Book::BorrowBook(enseignant, b5);

        Verifier(empruntP1 && empruntP2 && empruntP3,
                 "Trois emprunts enseignant");

        Verifier(enseignant->GetBorrowedCount() == 3,
                 "Trois copies chez l'enseignant");

        Verifier(!enseignant->CanBorrow(),
                 "Limite enseignant atteinte");

        bool refusP4 = Book::BorrowBook(enseignant, b6);

        Verifier(!refusP4,
                 "Quatrieme emprunt refuse");

        enseignant->GetInfo();

        // ==================================
        // TEST 11 : RETOURS FINAUX
        // ==================================

        std::cout << "\n=== TEST 11 : RETOURS FINAUX ===\n";

        bool retourE2 = Book::ReturnBook(etudiant, b2);

        bool retourP1 = Book::ReturnBook(enseignant, b1);
        bool retourP2 = Book::ReturnBook(enseignant, b4);
        bool retourP3 = Book::ReturnBook(enseignant, b5);

        Verifier(
            retourE2 && retourP1 && retourP2 && retourP3,
            "Tous les livres rendus"
        );

        Verifier(etudiant->GetBorrowedCount() == 0,
                 "Etudiant sans emprunt");

        Verifier(enseignant->GetBorrowedCount() == 0,
                 "Enseignant sans emprunt");

        Verifier(Book::totalBooks() == 6,
                 "Toutes les copies liberees");

        Verifier(
            b1->Status() == Bookstatus::Available &&
            b2->Status() == Bookstatus::Available &&
            b4->Status() == Bookstatus::Available &&
            b5->Status() == Bookstatus::Available,
            "Livres rendus disponibles"
        );

        bibliotheque.DisplayCatalog();

        // ==================================
        // TEST 12 : DEPLACEMENT LIBRARY
        // ==================================

        std::cout << "\n=== TEST 12 : DEPLACEMENT ===\n";

        Library nouvelleBibliotheque(
            std::move(bibliotheque)
        );

        Verifier(nouvelleBibliotheque.Size() == 6,
                 "Livres transferes");

        Verifier(nouvelleBibliotheque.MemberCount() == 2,
                 "Membres transferes");

        Verifier(bibliotheque.Size() == 0,
                 "Ancien catalogue vide");

        Verifier(bibliotheque.MemberCount() == 0,
                 "Ancien catalogue membres vide");

        // ==================================
        // TEST 13 : AFFECTATION DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 13 : AFFECTATION ===\n";

        Library destination;

        destination.AddMember(
            std::make_unique<StudentMember>(
                "Marie", "Tremblay", "E002", "Physique"
            )
        );

        destination = std::move(nouvelleBibliotheque);

        Verifier(destination.Size() == 6,
                 "Livres conserves apres affectation");

        Verifier(destination.MemberCount() == 2,
                 "Membres conserves apres affectation");

        Verifier(nouvelleBibliotheque.Size() == 0,
                 "Source vide apres affectation");

        destination.DisplayMembers();
        destination.DisplayCatalog();
    }

    // ==================================
    // TEST 14 : EQUILIBRE FINAL
    // ==================================

    std::cout << "\n=== TEST 14 : EQUILIBRE FINAL ===\n";

    Verifier(Member::TotalMembers() == 0,
             "Aucun membre restant");

    Verifier(Book::totalBooks() == 0,
             "Aucun livre restant");

    // ==================================
    // BILAN
    // ==================================

    std::cout << "\n====================================\n";
    std::cout << "           BILAN DES TESTS\n";
    std::cout << "====================================\n";

    std::cout << "Tests reussis : "
              << testsReussis << '\n';

    std::cout << "Tests echoues : "
              << testsEchoues << '\n';

    if (testsEchoues == 0) {
        std::cout << "\nTOUS LES TESTS SONT VALIDES\n";
        return 0;
    }

    std::cout << "\nCERTAINS TESTS ONT ECHOUE\n";
    return 1;
}
