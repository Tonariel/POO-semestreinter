#ifndef TEACHERMEMBER_H
#define TEACHERMEMBER_H

#include "Members/Member.hpp"

class TeacherMember : public Member {
public:
    TeacherMember(std::string Name,
                  std::string Surname,
                  std::string Id)
        : Member(Name, Surname, Id)
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
};

#endif
