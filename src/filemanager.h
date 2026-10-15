#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

#include "library.h"
#include "journal.h"

using namespace std;

class FileManager {
private:
    string booksFileName;
    string usersFileName;
    string journalFileName;

public:
    // Constructor
    FileManager(const string& booksFile, const string& usersFile, const string& journalFile);
    
    // File operations
    bool saveLibraryData(Library& library);
    bool loadLibraryData(Library& library);
    
    // Individual file operations
    bool saveBooksToFile(Library& library);
    bool saveUsersToFile(Library& library);
    bool loadBooksFromFile(Library& library);
    bool loadUsersFromFile(Library& library);

    // journal
    bool saveJournalToFile(Journal& journal);
    
    // Utility methods
    bool fileExists(const string& filename);
    void createBackup();
};

#endif
