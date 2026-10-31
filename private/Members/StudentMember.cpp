#include "Members/StudentMember.hpp"
#include <iostream>

void StudentMember::GetInfo() const
{
    // Afficher les informations communes
    Member::GetInfo();

    // Afficher l'attribut propre a l'etudiant
    std::cout << "Programme : "
              << programme_
              << std::endl;
}
