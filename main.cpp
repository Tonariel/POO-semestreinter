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

    return 0;
}
