
#include <iostream>
#include <memory>
#include <utility>
#include <cassert>

#include "Library.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

// ==========================================
// AFFICHAGE VIA L'INTERFACE
// ==========================================

void DisplayObject(const IDisplayable& object)
{
    object.GetInfo();
}

int main()
{
    std::cout << "=== TEST LIBRARY ===\n";

    std::cout << "Membres au depart : "
              << Member::TotalMembers() << '\n';

    std::cout << "Livres au depart : "
              << Book::totalBooks() << '\n';

    {
        Library bibliotheque;

        // ==================================
        // TEST 1 : AJOUT DES MEMBRES
        // ==================================

        std::cout << "\n=== TEST 1 : MEMBRES ===\n";

        bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Jean", "Dupont", "E001", "Informatique"
            )
        );

        bibliotheque.AddMember(
            std::make_unique<TeacherMember>(
                "Paul", "Martin", "P001", "Mathematiques"
            )
        );

        assert(bibliotheque.MemberCount() == 2);

        bibliotheque.DisplayMembers();

        // ==================================
        // TEST 2 : INTERFACE ET RECHERCHE
        // ==================================

        std::cout << "\n=== TEST 2 : INTERFACE ===\n";

        const Member* membre = bibliotheque.GetMember(0);

        assert(membre != nullptr);
        DisplayObject(*membre);

        Member* etudiant =
            bibliotheque.FindMemberById("E001");

        Member* enseignant =
            bibliotheque.FindMemberById("P001");

        assert(etudiant != nullptr);
        assert(enseignant != nullptr);

        assert(
            bibliotheque.FindMemberById("X999") == nullptr
        );

        const Library& lectureSeule = bibliotheque;

        assert(
            lectureSeule.FindMemberById("E001") != nullptr
        );

        // ==================================
        // TEST 3 : AJOUTS INVALIDES
        // ==================================

        std::cout << "\n=== TEST 3 : REFUS ===\n";

        Member* membreNul = bibliotheque.AddMember(nullptr);

        assert(membreNul == nullptr);

        Member* doublon = bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Lucas", "Bernard", "E001", "Physique"
            )
        );

        assert(doublon == nullptr);
        assert(bibliotheque.MemberCount() == 2);

        std::cout << "Ajouts invalides refuses\n";

        // ==================================
        // TEST 4 : LIMITES
        // ==================================

        std::cout << "\n=== TEST 4 : LIMITES ===\n";

        assert(etudiant->GetBorrowLimit() == 2);
        assert(enseignant->GetBorrowLimit() == 3);

        assert(etudiant->CanBorrow());
        assert(enseignant->CanBorrow());

        // ==================================
        // TEST 5 : AJOUT DES LIVRES
        // ==================================

        std::cout << "\n=== TEST 5 : LIVRES ===\n";

        bibliotheque.AddBook(
            std::make_unique<EBook>(
                "Livre numerique 1",
                "Auteur A",
                "https://exemple.com/a",
                25
            )
        );

        bibliotheque.AddBook(
            std::make_unique<PhysicalBook>(
                "Livre papier 1",
                "Auteur B",
                "Rayon A3",
                Bookstate::Good
            )
        );

        bibliotheque.AddBook(
            std::make_unique<AudioBook>(
                "Livre audio 1",
                "Auteur C",
                120,
                "Narrateur A",
                "Francais"
            )
        );

        bibliotheque.AddBook(
            std::make_unique<EBook>(
                "Livre numerique 2",
                "Auteur D",
                "https://exemple.com/d",
                30
            )
        );

        bibliotheque.AddBook(
            std::make_unique<PhysicalBook>(
                "Livre papier 2",
                "Auteur E",
                "Rayon B2",
                Bookstate::New
            )
        );

        bibliotheque.AddBook(
            std::make_unique<AudioBook>(
                "Livre audio 2",
                "Auteur F",
                90,
                "Narrateur B",
                "Francais"
            )
        );

        assert(bibliotheque.Size() == 6);

        assert(bibliotheque.GetBook(0) != nullptr);
        assert(bibliotheque.GetBook(6) == nullptr);

        assert(
            bibliotheque.FindBook("Livre papier 1") != nullptr
        );

        assert(
            bibliotheque.FindBook("Inexistant") == nullptr
        );

        bibliotheque.DisplayCatalog();

        // ==================================
        // TEST 6 : EMPRUNTS ETUDIANT
        // ==================================

        std::cout << "\n=== TEST 6 : EMPRUNTS ETUDIANT ===\n";

        Book* b1 = bibliotheque.GetBook(0);
        Book* b2 = bibliotheque.GetBook(1);
        Book* b3 = bibliotheque.GetBook(2);
        Book* b4 = bibliotheque.GetBook(3);
        Book* b5 = bibliotheque.GetBook(4);
        Book* b6 = bibliotheque.GetBook(5);

        assert(b1 != nullptr);
        assert(b2 != nullptr);
        assert(b3 != nullptr);
        assert(b4 != nullptr);
        assert(b5 != nullptr);
        assert(b6 != nullptr);

        // Premier emprunt
        bool emprunt1 = etudiant->BorrowBook(*b1);
        assert(emprunt1);

        // Deuxieme emprunt
        bool emprunt2 = etudiant->BorrowBook(*b2);
        assert(emprunt2);

        assert(etudiant->GetBorrowedCount() == 2);
        assert(!etudiant->CanBorrow());

        // Troisieme emprunt : limite atteinte
        bool refusLimiteEtudiant = etudiant->BorrowBook(*b3);

        assert(!refusLimiteEtudiant);
        assert(etudiant->GetBorrowedCount() == 2);
        assert(b3->Status() == Bookstatus::Available);

        etudiant->GetInfo();

        // ==================================
        // TEST 7 : RETOUR ETUDIANT
        // ==================================

        std::cout << "\n=== TEST 7 : RETOUR ETUDIANT ===\n";

        bool retour1 = etudiant->ReturnBook(*b1);

        assert(retour1);
        assert(etudiant->GetBorrowedCount() == 1);
        assert(etudiant->CanBorrow());
        assert(b1->Status() == Bookstatus::Available);

        // Retour invalide : ce livre a deja ete rendu
        bool retourInvalide = etudiant->ReturnBook(*b1);

        assert(!retourInvalide);

        // ==================================
        // TEST 8 : EMPRUNTS ENSEIGNANT
        // ==================================

        std::cout << "\n=== TEST 8 : EMPRUNTS ENSEIGNANT ===\n";

        bool empruntProf1 = enseignant->BorrowBook(*b1);
        bool empruntProf2 = enseignant->BorrowBook(*b4);
        bool empruntProf3 = enseignant->BorrowBook(*b5);

        assert(empruntProf1);
        assert(empruntProf2);
        assert(empruntProf3);

        assert(enseignant->GetBorrowedCount() == 3);
        assert(!enseignant->CanBorrow());

        // Quatrieme emprunt : refus
        bool refusLimiteProf = enseignant->BorrowBook(*b6);

        assert(!refusLimiteProf);
        assert(enseignant->GetBorrowedCount() == 3);
        assert(b6->Status() == Bookstatus::Available);

        enseignant->GetInfo();

        // ==================================
        // TEST 9 : LIVRE INDISPONIBLE
        // ==================================

        std::cout << "\n=== TEST 9 : LIVRE DEJA EMPRUNTE ===\n";

        // b1 est actuellement emprunte par l'enseignant.
        // L'etudiant a encore une place disponible.
        bool refusIndisponible = etudiant->BorrowBook(*b1);

        assert(!refusIndisponible);
        assert(etudiant->GetBorrowedCount() == 1);
        assert(enseignant->GetBorrowedCount() == 3);

        // ==================================
        // TEST 10 : RETOURS FINAUX
        // ==================================

        std::cout << "\n=== TEST 10 : RETOURS ===\n";

        bool retourEtudiant = etudiant->ReturnBook(*b2);

        bool retourProf1 = enseignant->ReturnBook(*b1);
        bool retourProf2 = enseignant->ReturnBook(*b4);
        bool retourProf3 = enseignant->ReturnBook(*b5);

        assert(retourEtudiant);
        assert(retourProf1);
        assert(retourProf2);
        assert(retourProf3);

        assert(etudiant->GetBorrowedCount() == 0);
        assert(enseignant->GetBorrowedCount() == 0);

        assert(etudiant->CanBorrow());
        assert(enseignant->CanBorrow());

        bibliotheque.DisplayCatalog();

        // ==================================
        // TEST 11 : CONSTRUCTEUR DE DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 11 : DEPLACEMENT ===\n";

        Library nouvelleBibliotheque(
            std::move(bibliotheque)
        );

        assert(nouvelleBibliotheque.MemberCount() == 2);
        assert(nouvelleBibliotheque.Size() == 6);

        assert(bibliotheque.MemberCount() == 0);
        assert(bibliotheque.Size() == 0);

        std::cout << "Constructeur de deplacement valide\n";

        // ==================================
        // TEST 12 : AFFECTATION PAR DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 12 : AFFECTATION ===\n";

        Library destination;

        destination.AddMember(
            std::make_unique<StudentMember>(
                "Marie", "Tremblay", "E002", "Physique"
            )
        );

        destination = std::move(nouvelleBibliotheque);

        assert(destination.MemberCount() == 2);
        assert(destination.Size() == 6);

        assert(nouvelleBibliotheque.MemberCount() == 0);
        assert(nouvelleBibliotheque.Size() == 0);

        destination.DisplayMembers();
        destination.DisplayCatalog();

        std::cout << "Affectation par deplacement valide\n";
    }

    // ==================================
    // TEST 13 : EQUILIBRE MEMOIRE
    // ==================================

    std::cout << "\n=== VERIFICATION FINALE ===\n";

    std::cout << "Membres restants : "
              << Member::TotalMembers() << '\n';

    std::cout << "Livres restants : "
              << Book::totalBooks() << '\n';

    assert(Member::TotalMembers() == 0);
    assert(Book::totalBooks() == 0);

    std::cout << "\nTOUS LES TESTS SONT VALIDES\n";

    return 0;
}
