
#include "journal.h"

#include <iomanip>
#include <sstream>

using namespace std;

void Journal::log(EntryType type, const string& message) {
    entries.push_back({time(nullptr), type, message});
}
void Journal::log_add_book(Book& book) {
    log(EntryType::ADD_BOOK, book.toString());
}
void Journal::log_delete_book(Book& book) {
    log(EntryType::DELETE_BOOK, book.toString());
}
void Journal::log_add_user(User& user) {
    log(EntryType::ADD_USER, user.toFileFormat());
}
void Journal::log_borrow_book(Book& book, User& user) {
    log(EntryType::BORROW_BOOK, book.toString() + " - Emprunteur : " + user.getName());
}
void Journal::log_return_book(Book& book, User& user) {
    log(EntryType::RETURN_BOOK, book.toString() + " - Emprunteur : " + user.getName());
}
void Journal::log_save() {
    log(EntryType::SAVE, "Sauvegarde des donnees effectuee");
}
void Journal::log_save_backup() {
    log(EntryType::SAVE_BACKUP, "Creation de la sauvegarde effectuee");
}
void Journal::log_save_error(const string& reason) {
    log(EntryType::SAVE_ERROR, reason);
}

const vector<Entry>& Journal::getEntries() const {
    return entries;
}
string Journal::serializeEntry(const Entry& entry) {
    ostringstream output;

    const tm* localTime = localtime(&entry.time);

    if (localTime == nullptr) {
        return "";
    }

    output << put_time(localTime, "%Y-%m-%d %H:%M:%S") << " | ";

    switch (entry.type) {
        case EntryType::ADD_BOOK:    output << "ADD_BOOK";    break;
        case EntryType::DELETE_BOOK: output << "DELETE_BOOK"; break;
        case EntryType::ADD_USER:    output << "ADD_USER";    break;
        case EntryType::BORROW_BOOK: output << "BORROW_BOOK"; break;
        case EntryType::RETURN_BOOK: output << "RETURN_BOOK"; break;
        case EntryType::SAVE:        output << "SAVE";        break;
        case EntryType::SAVE_BACKUP: output << "SAVE_BACKUP"; break;
        case EntryType::SAVE_ERROR:  output << "SAVE_ERROR";  break;
    }

    output << " | " << entry.message;

    return output.str();
}
