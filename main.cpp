#include <iostream>
#include <memory>

#include "Library.hpp"
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

int main()
{
    std::cout << "Membres au depart : "
              << Member::TotalMembers() << std::endl;

    {
        Library bibliotheque;

        // Test AddMember()
        bibliotheque.AddMember(
            std::make_unique<StudentMember>(
                "Jean", "Dupont", "E001", "Informatique")
        );

        bibliotheque.AddMember(
            std::make_unique<TeacherMember>(
                "Paul", "Martin", "P001", "Mathematiques")
        );

        // Test MemberCount()
        std::cout << "Nombre de membres : "
                  << bibliotheque.MemberCount()
                  << std::endl;

        // Test GetMember()
        Member* premier = bibliotheque.GetMember(0);

        if (premier != nullptr) {
            std::cout << "Premier membre : "
                      << premier->GetMemberType()
                      << std::endl;
        }

        // Test d'indice invalide
        std::cout << "Indice invalide : "
                  << (bibliotheque.GetMember(100) == nullptr)
                  << std::endl;

        // Test DisplayMembers()
        bibliotheque.DisplayMembers();

        std::cout << "Membres vivants : "
                  << Member::TotalMembers()
                  << std::endl;
    }

    std::cout << "Membres apres destruction : "
              << Member::TotalMembers()
              << std::endl;

    return 0;
}
