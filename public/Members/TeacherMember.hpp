#ifndef TEACHERMEMBER_H
#define TEACHERMEMBER_H

#include "Members/Member.hpp"
#include <string>

class TeacherMember : public Member {
private:
    // Departement de l'enseignant
    std::string departement_;

public:
    // Constructeur
    TeacherMember(std::string Name,
                  std::string Surname,
                  std::string Id,
                  std::string Departement)
        : Member(Name, Surname, Id),
          departement_(Departement)
    {
    }

    // Limite d'emprunt d'un enseignant
    std::size_t GetBorrowLimit() const override {
        return 3;
    }

    // Identification du type de membre
    std::string GetMemberType() const override {
        return "Enseignant";
    }

    // Accesseur du departement
    std::string GetDepartement() const {
        return departement_;
    }
};

#endif
