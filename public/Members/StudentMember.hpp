#ifndef STUDENTMEMBER_H
#define STUDENTMEMBER_H

#include "Members/Member.hpp"
#include <string>

class StudentMember : public Member {
private:
    // Programme d'etudes de l'etudiant
    std::string programme_;

public:
    // Constructeur
    StudentMember(std::string Name,
                  std::string Surname,
                  std::string Id,
                  std::string Programme)
        : Member(Name, Surname, Id),
          programme_(Programme)
    {
    }

    // Limite d'emprunt d'un etudiant
    std::size_t GetBorrowLimit() const override {
        return 2;
    }

    // Identification du type de membre
    std::string GetMemberType() const override {
        return "Etudiant";
    }

    void GetInfo() const override;

    // Accesseur du programme d'etudes
    std::string GetProgramme() const {
        return programme_;
    }
};

#endif
