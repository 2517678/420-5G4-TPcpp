#include "book.h"

#include "library.h"

#include <sstream>
#include <string>
#include <vector>


Book::Book() :
    title(""), author(""),
    isbn(""), isAvailable(true),
    borrowerId("") {}
Book::Book(const string& title, const string& author, const string& isbn) :
    title(title), author(author),
    isbn(isbn), isAvailable(true),
    borrowerId("") {}


string Book::getTitle() const {return title;}
string Book::getAuthor() const {return author;}
string Book::getISBN() const {return isbn;}
bool Book::getAvailability() const {return isAvailable;}
string Book::getBorrowerId() const {return borrowerId;}

void Book::setTitle(const string& title) {
    this->title = title;
}
void Book::setAuthor(const string& author) {
    this->author = author;
}
void Book::setISBN(const string& isbn) {
    this->isbn = isbn;
}
void Book::setAvailability(bool available) {
    this->isAvailable = available;
}
void Book::setBorrowerId(const string& id) {
    this->borrowerId = id;
}


void Book::checkOut(const string& borrowerId) {
    setBorrowerId(borrowerId);
    setAvailability(false);
}
void Book::returnBook() {
    setBorrowerId("");
    setAvailability(true);
}
string Book::toString() const {
    return title + " - " + author + " (" + isbn + ")";
}
string Book::toString(Library& library) const {
    if (isAvailable)
        return toString();

    User* borrower = library.findUserById(borrowerId);

    return toString() + " - Emprunté par : "
        + (borrower ? borrower->getName() : "Utilisateur introuvable");
}
string Book::toFileFormat() const {
    // I would have loved std::format, but we are in cpp17, so no std::format for me :(
    string line = title + '|' + author + '|' + isbn + '|';
    
    if(isAvailable)
        line += "1|";
    else
        line += "0|" + borrowerId;
    
    return line;
}
void Book::fromFileFormat(const string& line) {
    vector<string> parts;

    stringstream ss(line);
    string item;
    while(getline(ss, item, '|')) {
        parts.push_back(item);
    }

    // assert(parts.size() >= 4);

    title = parts[0];
    author = parts[1];
    isbn = parts[2];
    isAvailable = stoi(parts[3]); // 1 = true, 0 = false
    if(!isAvailable) {
        // assert(parts.size() == 5);
        borrowerId = parts[4];
    } else {
        borrowerId = "";
    }
}