
#include <iostream>
#include "Members/StudentMember.h"
#include "Members/TeacherMember.h"

int main()
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

    return 0;
}
