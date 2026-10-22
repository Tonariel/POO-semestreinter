#ifndef STUDENTMEMBER_H
#define STUDENTMEMBER_H

#include "Members/Member.hpp"

class StudentMember : public Member {
public:
    StudentMember(std::string Name,
                  std::string Surname,
                  std::string Id)
        : Member(Name, Surname, Id)
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
};

#endif
