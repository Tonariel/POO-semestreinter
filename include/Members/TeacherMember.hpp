
#ifndef TEACHERMEMBER_H
#define TEACHERMEMBER_H

#include "Members/Member.h"

class TeacherMember : public Member {
public:
    TeacherMember(std::string Name,
                  std::string Surname,
                  std::string Id)
        : Member(Name, Surname, Id)
    {
    }

    std::size_t GetBorrowLimit() const override {
        return 3;
    }
};

#endif
  