#include "Book.hpp"

using namespace std;

int Book::totalBooks_ = 0;

Book::Book(std::string title, std::string author)
    : title_(title), author_(author) {
    totalBooks_++;
    cout << "+ Construct " << title_ << " (count=" << totalBooks_ << ")" << endl;
}

Book::Book(const Book& other)
    : title_(other.title_), author_(other.author_), status(other.status), borrowedBy_(other.borrowedBy_) {
    totalBooks_++;
    cout << "+ Copy " << title_ << " (count=" << totalBooks_ << ")" << endl;
}

Book::~Book() {
    totalBooks_--;
    cout << "- Destruct " << title_ << " (count=" << totalBooks_ << ")" << endl;
}

void Book::Destroy_Clone (Book *Copy){
    delete Copy;
}

Bookstatus Book::Status() const {
    return status;
}

void Book::BorrowedBy() const {
    for (size_t i=0; i<borrowedBy_.size(); ++i) {
        cout << borrowedBy_[i] << endl;
    }
    cout << "nobody" << endl;
}

int Book::BorrowedBy_Size(){
    return borrowedBy_.size();
}

string Book::title() const {
    return title_;
}

std::string Book::author() const {
    return author_;
}

bool Book::SpecialTest (Book* BooktoBorrow, Member* Membre){
    BooktoBorrow->AddBorrowedBy(Membre);
    BooktoBorrow->status = Bookstatus::Borrowed;
    return true;
}

bool Book::DeleteSpecialTest (Book* BooktoReturn, Member* Membre){
    BooktoReturn->setStatus(Bookstatus::Available);
    BooktoReturn->DeleteBorrowedBy(Membre);
    return true;
}

bool Book::BorrowBook (Member* Membre, Book* BooktoBorrow){
    if (Membre == nullptr || BooktoBorrow == nullptr) {
        return false;
    }
    if(Membre->CanBorrow() == false){
        cout << "Member cannot borrow more books." << endl;
        return false;
    }
    if (BooktoBorrow->SpecialTest(BooktoBorrow, Membre) == false){
        return false;
    }
    Book* Copy = BooktoBorrow->Clone();
    Membre->AddBorrowedBook(Copy);
    return true;
}

bool Book::ReturnBook (Member* Membre, Book* BooktoReturn){
    if (Membre == nullptr || BooktoReturn == nullptr) {
        return false;
    }

    Book* Copy = Membre->GetReleasedBook(BooktoReturn->title_, BooktoReturn->author_);
    if (Copy == nullptr) {
        return false;
    }

    delete Copy;
    return BooktoReturn->DeleteSpecialTest(BooktoReturn, Membre);
}

void Book::setStatus(Bookstatus newStatus) {
    status = newStatus;
}

void Book::AddBorrowedBy(Member* newBorrower) {
    borrowedBy_.push_back(newBorrower->ReturnName());
}

void Book::DeleteBorrowedBy(Member* oldBorrower) {
    for (size_t i=0; i<borrowedBy_.size(); ++i) {
        if (borrowedBy_[i] == oldBorrower->ReturnName()) {
            borrowedBy_.erase(borrowedBy_.begin() + i);
            break;
        }
    }
}

int Book::totalBooks() {
    return totalBooks_;
}

EBook::EBook(std::string title, std::string author, std::string url, int size)
    :Book{title, author}, downloadUrl_{url}, fileSize_{size}{}

EBook::EBook(const EBook &other)
    :Book (other), downloadUrl_(other.downloadUrl_),fileSize_(other.fileSize_){}

EBook* EBook::Clone()const{
    return new EBook(*this);
}

void EBook::GetInfo() const {
    cout << "[Numerique] " << title() << " par " << author()
         << " | " << fileSize_ << " Mo"
         << " | " << downloadUrl_;
}

string EBook::Url() const{
    return downloadUrl_;
}

int EBook::size() const{
    return fileSize_;
}

bool EBook::SpecialTest(Book*, Member* Membre){
    AddBorrowedBy(Membre);
    setStatus(Bookstatus::Available);
    return true;
}

bool EBook::DeleteSpecialTest(Book*, Member* Membre){
    DeleteBorrowedBy(Membre);
    setStatus(Bookstatus::Available);
    return true;
}

PhysicalBook::PhysicalBook(std::string title, std::string author, std::string Localisation, Bookstate state)
    :Book{title, author}, Localisation_{Localisation}, state_{state}{}

PhysicalBook::PhysicalBook(const PhysicalBook &other)
    :Book(other), Localisation_(other.Localisation_), state_(other.state_){}

PhysicalBook *PhysicalBook::Clone()const{
    return new PhysicalBook(*this);
}

void PhysicalBook::GetInfo() const {
    cout << "[Papier] " << title() << " par " << author()
         << " | rayon " << Localisation_ << " | ";

    switch (state_) {
        case Bookstate::New:
            cout << "neuf";
            break;
        case Bookstate::Good:
            cout << "bon etat";
            break;
        case Bookstate::Damaged:
            cout << "endommage";
            break;
    }
}

string PhysicalBook::Localisation() const{
    return Localisation_;
}

void PhysicalBook::SetState(Bookstate Newstate){
    state_ = Newstate;
} 

Bookstate PhysicalBook::State() const{
    return state_;
}

bool PhysicalBook::SpecialTest(Book*, Member* Membre){
    if (Status() == Bookstatus::Borrowed || Status() == Bookstatus::UnAvailable){
        cout << "the book is already borrowed" << endl;
        return false;
    }
    if (State() == Bookstate::Damaged){
        setStatus(Bookstatus::UnAvailable);
        return false;
    }
    AddBorrowedBy(Membre);
    setStatus(Bookstatus::Borrowed);
    return true;
}

bool PhysicalBook::DeleteSpecialTest(Book*, Member* Membre){
    DeleteBorrowedBy(Membre);
    setStatus(Bookstatus::Available);
    return true;
}


AudioBook::AudioBook(std::string title, std::string author, int Duration, std::string Narator, std::string Langage)
    :Book{title, author}, Duration_{Duration}, Narator_{Narator}, Langage_{Langage}{}

AudioBook::AudioBook(const AudioBook &other)
    :Book(other), Duration_(other.Duration_), Narator_(other.Narator_), Langage_(other.Langage_){}

AudioBook* AudioBook::Clone()const{
    return new AudioBook(*this);
}

void AudioBook::GetInfo() const {
    cout << "[Audio] " << title() << " par " << author()
         << " | lu par " << Narator_
         << " | " << Duration_ << " min (" << Langage_ << ")";
}

int AudioBook::Duration() const{
    return Duration_;
}

string AudioBook::Narator() const{
    return Narator_;
}

string AudioBook::Langage() const{
    return Langage_;
}

bool AudioBook::SpecialTest(Book*, Member* Membre){
    constexpr int maxSimultaneousListeners = 2;
    if (BorrowedBy_Size() >= maxSimultaneousListeners){
        cout << "the audiobook has reached its listening limit" << endl;
        return false;
    }

    AddBorrowedBy(Membre);
    if (BorrowedBy_Size() == maxSimultaneousListeners){
        setStatus(Bookstatus::Borrowed);
    } else {
        setStatus(Bookstatus::Available);
    }
    return true;
}

bool AudioBook::DeleteSpecialTest(Book*, Member* Membre){
    DeleteBorrowedBy(Membre);
    setStatus(BorrowedBy_Size() >= 2
                  ? Bookstatus::Borrowed
                  : Bookstatus::Available);
    return true;
}