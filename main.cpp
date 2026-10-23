#include <iostream>
#include <memory>
#include <utility>

#include "Library.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

void DisplayObject(const IDisplayable& object)
{
    object.GetInfo();
}

int main()
{
    std::cout << "=== TEST LIBRARY ===" << std::endl;

    std::cout << "Membres au depart : "
              << Member::TotalMembers() << std::endl;

    {
        Library bibliotheque;

        // ==================================
        // TEST 1 : AJOUT DES MEMBRES
        // ==================================

        std::cout << "\n=== TEST 1 : AJOUT ==="
                  << std::endl;

        bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Jean", "Dupont", "E001", "Informatique")
        );

        bibliotheque.AddMember(
            std::make_unique<TeacherMember>(
                "Paul", "Martin", "P001", "Mathematiques")
        );

        std::cout << "\n=== TEST INTERFACE ===" << std::endl;

        const Member* membre = bibliotheque.GetMember(0);

        if (membre != nullptr) {
            DisplayObject(*membre);
        }

        std::cout << "Nombre de membres : "
                  << bibliotheque.MemberCount()
                  << std::endl;

        // ==================================
        // TEST 2 : RECHERCHE PAR ID
        // ==================================

        std::cout << "\n=== TEST 2 : RECHERCHE ==="
                  << std::endl;

        Member* etudiant =
            bibliotheque.FindMemberById("E001");

        if (etudiant != nullptr) {
            std::cout << "Membre E001 : "
                      << etudiant->GetMemberType()
                      << std::endl;
        }

        Member* enseignant =
            bibliotheque.FindMemberById("P001");

        if (enseignant != nullptr) {
            std::cout << "Membre P001 : "
                      << enseignant->GetMemberType()
                      << std::endl;
        }

        std::cout << "ID inexistant : "
                  << (bibliotheque.FindMemberById("X999") == nullptr)
                  << std::endl;

        // Test de la version constante
        const Library& lectureSeule = bibliotheque;

        const Member* resultatConst =
            lectureSeule.FindMemberById("E001");

        std::cout << "Recherche constante : "
                  << (resultatConst != nullptr)
                  << std::endl;

        // ==================================
        // TEST 3 : POINTEUR NUL
        // ==================================

        std::cout << "\n=== TEST 3 : POINTEUR NUL ==="
                  << std::endl;

        Member* resultat = bibliotheque.AddMember(nullptr);

        std::cout << "Ajout refuse : "
                  << (resultat == nullptr)
                  << std::endl;

        std::cout << "Nombre de membres : "
                  << bibliotheque.MemberCount()
                  << std::endl;


        std::cout << "\n=== TEST : IDENTIFIANT EN DOUBLE ==="
                << std::endl;

        // E001 existe deja dans la bibliotheque
        Member* doublon = bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Lucas", "Bernard", "E001", "Physique")
        );

        std::cout << "Doublon refuse : "
                << (doublon == nullptr)
                << std::endl;

        std::cout << "Nombre de membres : "
                << bibliotheque.MemberCount()
                << std::endl;

        std::cout << "Membres vivants : "
                << Member::TotalMembers()
                << std::endl;


        // ==================================
        // TEST 4 : CONSTRUCTEUR DE DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 4 : DEPLACEMENT ==="
                  << std::endl;

        Library nouvelleBibliotheque(std::move(bibliotheque));

        std::cout << "Nouvelle bibliotheque : "
                  << nouvelleBibliotheque.MemberCount()
                  << std::endl;

        std::cout << "Ancienne bibliotheque : "
                  << bibliotheque.MemberCount()
                  << std::endl;

        std::cout << "Membres vivants : "
                  << Member::TotalMembers()
                  << std::endl;

        // ==================================
        // TEST 5 : AFFECTATION PAR DEPLACEMENT
        // ==================================

        std::cout << "\n=== TEST 5 : AFFECTATION ==="
                  << std::endl;

        Library destination;

        destination.AddMember(
            std::make_unique<StudentMember>(
                "Marie", "Tremblay", "E002", "Physique")
        );

        std::cout << "Avant affectation : "
                  << Member::TotalMembers()
                  << " membres vivants"
                  << std::endl;

        destination = std::move(nouvelleBibliotheque);

        std::cout << "Destination : "
                  << destination.MemberCount()
                  << std::endl;

        std::cout << "Source apres affectation : "
                  << nouvelleBibliotheque.MemberCount()
                  << std::endl;

        std::cout << "Membres vivants : "
                  << Member::TotalMembers()
                  << std::endl;

        // ==================================
        // TEST 6 : AFFICHAGE FINAL
        // ==================================

        std::cout << "\n=== TEST 6 : AFFICHAGE ==="
                  << std::endl;

        destination.DisplayMembers();
    }

    // ==================================
    // TEST 7 : EQUILIBRE MEMOIRE
    // ==================================

    std::cout << "\n=== VERIFICATION FINALE ==="
              << std::endl;

    std::cout << "Membres apres destruction : "
              << Member::TotalMembers()
              << std::endl;

    return 0;
}
