
#include <iostream>
#include "Members/StudentMember.hpp"
#include "Members/TeacherMember.hpp"

int main()
{
    std::cout << "Membres au depart : "
              << Member::TotalMembers() << std::endl;

    {
        StudentMember student("Jean", "Dupont", "E001");
        TeacherMember teacher("Paul", "Martin", "P001");

        Member* members[] = { &student, &teacher };

        for (Member* member : members) {
            member->GetInfo();

            std::cout << "Peut emprunter : "
                      << member->CanBorrow()
                      << std::endl;
        }

        std::cout << "Membres pendant le test : "
                  << Member::TotalMembers() << std::endl;
    }

    std::cout << "Membres apres destruction : "
              << Member::TotalMembers() << std::endl;

    return 0;
}
