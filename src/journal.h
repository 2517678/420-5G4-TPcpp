
#ifndef JOURNAL_H
#define JOURNAL_H

#include "book.h"
#include "user.h"

#include <ctime>
#include <string>
#include <vector>

enum class EntryType {
    ADD_BOOK,
    DELETE_BOOK,
    ADD_USER,
    BORROW_BOOK,
    RETURN_BOOK,
    SAVE,
    SAVE_BACKUP,
    SAVE_ERROR
};

struct Entry {
    std::time_t time;
    EntryType type;
    std::string message;
};

class Journal {
private:
    std::vector<Entry> entries;

public:
    Journal() = default;
    ~Journal() = default;

    // Add a new entry
    void log(EntryType type, const std::string& message);

    void log_add_book(Book& book);
    void log_delete_book(Book& book);
    void log_add_user(User& user);
    void log_borrow_book(Book& book, User& user);
    void log_return_book(Book& book, User& user);
    void log_save();
    void log_save_backup();
    void log_save_error(const std::string& reason);

    // others
    const std::vector<Entry>& getEntries() const;
    static std::string serializeEntry(const Entry& entry);
};

#endif // JOURNAL_H
