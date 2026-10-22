
#ifndef STUDENTMEMBER_H
#define STUDENTMEMBER_H

#include "Members/Member.h"

class StudentMember : public Member {
public:
    StudentMember(std::string Name,
                  std::string Surname,
                  std::string Id)
        : Member(Name, Surname, Id)
    {
    }

    std::size_t GetBorrowLimit() const override {
        return 2;
    }
};

#endif
  