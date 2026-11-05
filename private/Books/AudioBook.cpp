#include "Books/AudioBook.hpp"

#include <iostream>

using namespace std;

AudioBook::AudioBook(std::string title, std::string author, int Duration,
                     std::string Narator, std::string Langage)
    : Book{title, author}, Duration_{Duration}, Narator_{Narator}, Langage_{Langage} {}

AudioBook::AudioBook(const AudioBook& other)
    : Book(other), Duration_(other.Duration_), Narator_(other.Narator_),
      Langage_(other.Langage_) {}

AudioBook* AudioBook::Clone() const {
    return new AudioBook(*this);
}

void AudioBook::GetInfo() const {
    cout << "[Audio] " << title() << " par " << author()
         << " | lu par " << Narator_
         << " | " << Duration_ << " min (" << Langage_ << ")";
}

int AudioBook::Duration() const {
    return Duration_;
}

string AudioBook::Narator() const {
    return Narator_;
}

string AudioBook::Langage() const {
    return Langage_;
}

bool AudioBook::SpecialTest(Book*, Member* member) {
    constexpr int maxSimultaneousListeners = 2;
    if (BorrowedBy_Size() >= maxSimultaneousListeners) {
        cout << "the audiobook has reached its listening limit" << endl;
        return false;
    }

    AddBorrowedBy(member);
    if (BorrowedBy_Size() == maxSimultaneousListeners) {
        setStatus(Bookstatus::Borrowed);
    } else {
        setStatus(Bookstatus::Available);
    }
    return true;
}

bool AudioBook::DeleteSpecialTest(Book*, Member* member) {
    DeleteBorrowedBy(member);
    setStatus(BorrowedBy_Size() >= 2
                  ? Bookstatus::Borrowed
                  : Bookstatus::Available);
    return true;
}
