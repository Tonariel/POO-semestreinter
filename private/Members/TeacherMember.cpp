#include "Members/TeacherMember.hpp"
#include <iostream>

void TeacherMember::GetInfo() const
{
    // Afficher les informations communes
    Member::GetInfo();

    // Afficher l'attribut propre a l'enseignant
    std::cout << "Departement : "
              << departement_
              << std::endl;
}
