
#include <iostream>
#include <memory>
#include <utility>
#include <cassert>

#include "Library.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

// Affichage via l'interface polymorphe
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

        std::cout << "\n=== TEST 1 : AJOUT DES MEMBRES ===\n";

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

        // Test de l'interface
        std::cout << "\n=== TEST INTERFACE ===\n";

        const Member* membre = bibliotheque.GetMember(0);

        if (membre != nullptr) {
            DisplayObject(*membre);
        }

        // ==================================
        // TEST 2 : RECHERCHE PAR ID
        // ==================================

        std::cout << "\n=== TEST 2 : RECHERCHE ===\n";

        Member* etudiant = bibliotheque.FindMemberById("E001");
        Member* enseignant = bibliotheque.FindMemberById("P001");

        assert(etudiant != nullptr);
        assert(enseignant != nullptr);
        assert(bibliotheque.FindMemberById("X999") == nullptr);

        std::cout << "Etudiant : "
                  << etudiant->GetMemberType() << '\n';

        std::cout << "Enseignant : "
                  << enseignant->GetMemberType() << '\n';

        const Library& lectureSeule = bibliotheque;

        assert(lectureSeule.FindMemberById("E001") != nullptr);

        // ==================================
        // TEST 3 : AJOUT REFUSE
        // ==================================

        std::cout << "\n=== TEST 3 : REFUS ===\n";

        assert(bibliotheque.AddMember(nullptr) == nullptr);

        Member* doublon = bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Lucas", "Bernard", "E001", "Physique"
            )
        );

        assert(doublon == nullptr);
        assert(bibliotheque.MemberCount() == 2);

        std::cout << "Ajouts invalides refuses correctement\n";

        // ==================================
        // TEST 4 : LIMITES DES MEMBRES
        // ==================================

        std::cout << "\n=== TEST 4 : LIMITES ===\n";

        assert(etudiant->GetBorrowLimit() == 2);
        assert(enseignant->GetBorrowLimit() == 3);

        assert(etudiant->CanBorrow());
        assert(enseignant->CanBorrow());

        std::cout << "Limite etudiant : "
                  << etudiant->GetBorrowLimit() << '\n';

        std::cout << "Limite enseignant : "
                  << enseignant->GetBorrowLimit() << '\n';

        // ==================================
        // TEST 5 : CATALOGUE DES LIVRES
        // ==================================

        std::cout << "\n=== TEST 5 : LIVRES ===\n";

        bibliotheque.AddBook(
            std::make_unique<EBook>(
                "Livre numerique",
                "Auteur A",
                "https://exemple.com/livre",
                25
            )
        );

        bibliotheque.AddBook(
            std::make_unique<PhysicalBook>(
                "Livre papier",
                "Auteur B",
                "Rayon A3",
                Bookstate::Good
            )
        );

        bibliotheque.AddBook(
            std::make_unique<AudioBook>(
                "Livre audio",
                "Auteur C",
                120,
                "Narrateur A",
                "Francais"
            )
        );

        assert(bibliotheque.Size() == 3);
        assert(bibliotheque.GetBook(0) != nullptr);
        assert(bibliotheque.GetBook(3) == nullptr);

        assert(bibliotheque.FindBook("Livre papier") != nullptr);
        assert(bibliotheque.FindBook("Inexistant") == nullptr);

        bibliotheque.DisplayCatalog();

        // ==================================
        // TEST 6 : DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 6 : DEPLACEMENT ===\n";

        Library nouvelleBibliotheque(std::move(bibliotheque));

        assert(nouvelleBibliotheque.MemberCount() == 2);
        assert(nouvelleBibliotheque.Size() == 3);

        assert(bibliotheque.MemberCount() == 0);
        assert(bibliotheque.Size() == 0);

        std::cout << "Constructeur de deplacement valide\n";

        // ==================================
        // TEST 7 : AFFECTATION PAR DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 7 : AFFECTATION ===\n";

        Library destination;

        destination.AddMember(
            std::make_unique<StudentMember>(
                "Marie", "Tremblay", "E002", "Physique"
            )
        );

        destination = std::move(nouvelleBibliotheque);

        assert(destination.MemberCount() == 2);
        assert(destination.Size() == 3);

        assert(nouvelleBibliotheque.MemberCount() == 0);
        assert(nouvelleBibliotheque.Size() == 0);

        destination.DisplayMembers();
        destination.DisplayCatalog();

        std::cout << "Affectation par deplacement valide\n";
    }

    // ==================================
    // TEST 8 : EQUILIBRE MEMOIRE
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
