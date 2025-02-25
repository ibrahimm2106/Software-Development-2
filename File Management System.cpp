#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    string publisher;
    int bookID;
    int totalCopies;
    int availableCopies;
    string subject;

public:
    Book() : year(0), bookID(0), totalCopies(0), availableCopies(0) {}

    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setYear(int y) { year = y; }
    void setPublisher(const string& p) { publisher = p; }
    void setBookID(int id) { bookID = id; }
    void setTotalCopies(int total) { totalCopies = total; }
    void setAvailableCopies(int available) { availableCopies = available; }
    void setSubject(const string& s) { subject = s; }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    string getPublisher() const { return publisher; }
    int getBookID() const { return bookID; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }
    string getSubject() const { return subject; }

    void display() const {
        cout << left << setw(25) << "Title: " << title << endl
            << left << setw(25) << "Author: " << author << endl
            << left << setw(25) << "Year: " << year << endl
            << left << setw(25) << "Publisher: " << publisher << endl
            << left << setw(25) << "BookID: " << bookID << endl
            << left << setw(25) << "Total Copies: " << totalCopies << endl
            << left << setw(25) << "Available Copies: " << availableCopies << endl
            << left << setw(25) << "Subject: " << subject << endl;
    }
};

class Library {
private:
    vector<Book> books;
    string booksFile = "C:\\Users\\ibrahimm23\\Documents\\books.csv";
    string borrowingFile = "C:\\Users\\ibrahimm23\\Documents\\borrowing_records.csv";
    string returnFile = "C:\\Users\\ibrahimm23\\Documents\\return_records.csv";
    string finesFile = "C:\\Users\\ibrahimm23\\Documents\\fines.csv";

public:
    Library() {
        loadBooksFromFile();
    }

    void loadBooksFromFile() {
        ifstream infile(booksFile);
        string line, title, author, publisher, subject;
        int year, bookID, totalCopies, availableCopies;
        while (getline(infile, line)) {
            stringstream ss(line);
            getline(ss, title, ',');
            getline(ss, author, ',');
            ss >> year;
            ss.ignore();
            getline(ss, publisher, ',');
            ss >> bookID >> totalCopies >> availableCopies;
            getline(ss, subject);

            Book book;
            book.setTitle(title);
            book.setAuthor(author);
            book.setYear(year);
            book.setPublisher(publisher);
            book.setBookID(bookID);
            book.setTotalCopies(totalCopies);
            book.setAvailableCopies(availableCopies);
            book.setSubject(subject);
            books.push_back(book);
        }
    }

    void saveBooksToFile() {
        ofstream outfile(booksFile);
        for (const auto& book : books) {
            outfile << book.getTitle() << ","
                << book.getAuthor() << ","
                << book.getYear() << ","
                << book.getPublisher() << ","
                << book.getBookID() << ","
                << book.getTotalCopies() << ","
                << book.getAvailableCopies() << ","
                << book.getSubject() << endl;
        }
    }

    void registerBook() {
        Book newBook;
        string input;
        int year, bookID, totalCopies, availableCopies;
        cout << "Enter the book's title: ";
        getline(cin, input);
        newBook.setTitle(input);

        cout << "Enter the author's name: ";
        getline(cin, input);
        newBook.setAuthor(input);

        cout << "Enter the publication year: ";
        cin >> year;
        newBook.setYear(year);

        cout << "Enter the publisher: ";
        cin.ignore();
        getline(cin, input);
        newBook.setPublisher(input);

        cout << "Enter the book's ID: ";
        cin >> bookID;
        newBook.setBookID(bookID); // Use the setter method

        cout << "Enter the total copies: ";
        cin >> totalCopies;
        newBook.setTotalCopies(totalCopies);

        cout << "Enter the available copies: ";
        cin >> availableCopies;
        newBook.setAvailableCopies(availableCopies);

        cout << "Enter the subject: ";
        cin.ignore();
        getline(cin, input);
        newBook.setSubject(input);

        books.push_back(newBook);
        saveBooksToFile();
    }

    void borrowBook(int bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) {
                if (book.getAvailableCopies() > 0) {
                    book.setAvailableCopies(book.getAvailableCopies() - 1);
                    ofstream outfile(borrowingFile, ios::app);
                    if (outfile) {
                        outfile << bookID << "," << getCurrentDate() << endl;
                        cout << "Book borrowed successfully." << endl;
                    }
                    else {
                        cerr << "Error: Unable to open borrowing records file." << endl;
                    }
                    saveBooksToFile();
                    return;
                }
                else {
                    cout << "No available copies left to borrow." << endl;
                    return;
                }
            }
        }
        cout << "Book not found." << endl;
    }

    void returnBook(int bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) {
                book.setAvailableCopies(book.getAvailableCopies() + 1);
                ofstream outfile(returnFile, ios::app);
                if (outfile) {
                    outfile << bookID << "," << getCurrentDate() << endl;
                    cout << "Book returned successfully." << endl;
                }
                else {
                    cerr << "Error: Unable to open return records file." << endl;
                }
                saveBooksToFile();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void calculateFines(int bookID, const string& returnDate) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) {
                string currentDate = getCurrentDate();
                struct tm tm_return {}, tm_current{};
                istringstream ss_return(returnDate);
                istringstream ss_current(currentDate);
                ss_return >> get_time(&tm_return, "%Y-%m-%d");
                ss_current >> get_time(&tm_current, "%Y-%m-%d");
                time_t time_return = mktime(&tm_return);
                time_t time_current = mktime(&tm_current);
                double seconds_diff = difftime(time_current, time_return);
                int days_diff = static_cast<int>(seconds_diff / (60 * 60 * 24));

                if (days_diff > 14) {
                    double fine = (days_diff - 14) * 1.0; // $1 per day late fee
                    ofstream outfile(finesFile, ios::app);
                    if (outfile) {
                        outfile << bookID << "," << returnDate << "," << fine << endl;
                        cout << "Fine calculated: $" << fine << endl;
                    }
                    else {
                        cerr << "Error: Unable to open fines file." << endl;
                    }
                }
                else {
                    cout << "No fines applicable." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    string getCurrentDate() const {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        struct tm buf; // create a tm struct
        char buffer[80];
        localtime_s(&buf, &now_time); // use localtime_s
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &buf); // pass a pointer to the tm struct
        return buffer;
    }

    void searchBookByTitle(const string& title) {
        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No books found with the title '" << title << "'." << endl;
        }
    }
};

int main() {

    Library library;
    int userType, choice;

    cout << "Are you a 1. Librarian or 2. Student? Enter (1/2): ";
    cin >> userType;
    cin.ignore(); // Clear the newline character left in the input buffer

    if (userType == 1) {
        // Librarian menu
        do {
            cout << "\nLibrarian Menu:\n"
                << "1. Register new book\n"
                << "2. Borrow a book\n"
                << "3. Return a book\n"
                << "4. Calculate fines\n"
                << "5. Exit\n"
                << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                library.registerBook();
                break;
            case 2: {
                int bookID;
                cout << "Enter book ID to borrow: ";
                cin >> bookID;
                library.borrowBook(bookID);
                break;
            }
            case 3: {
                int bookID;
                cout << "Enter book ID to return: ";
                cin >> bookID;
                library.returnBook(bookID);
                break;
            }
            case 4: {
                int bookID;
                string returnDate;
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter return date (YYYY-MM-DD): ";
                cin >> returnDate;
                library.calculateFines(bookID, returnDate);
                break;
            }
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            }
        } while (choice != 5);
    }
    else if (userType == 2) {
        // Student menu
        do {
            cout << "\nStudent Menu:\n"
                << "1. Search for a book by title\n"
                << "2. Borrow a book\n"
                << "3. Return a book\n"
                << "4. Calculate fines\n"
                << "5. Exit\n"
                << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1: {
                string title;
                cout << "Enter the book title to search for: ";
                getline(cin, title);
                library.searchBookByTitle(title);
                break;
            }
            case 2: {
                int bookID;
                cout << "Enter book ID to borrow: ";
                cin >> bookID;
                library.borrowBook(bookID);
                break;
            }
            case 3: {
                int bookID;
                cout << "Enter book ID to return: ";
                cin >> bookID;
                library.returnBook(bookID);
                break;
            }
            case 4: {
                int bookID;
                string returnDate;
                cout << "Enter book ID: ";
                cin >> bookID;
                cout << "Enter return date (YYYY-MM-DD): ";
                cin >> returnDate;
                library.calculateFines(bookID, returnDate);
                break;
            }
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            }
        } while (choice != 5);
    }
    else {
        cout << "Invalid user type selected. Exiting program." << endl;
    }

    return 0;
}
