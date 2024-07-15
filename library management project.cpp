#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

class Book {
private:
    string id;
    string bookName;
    string authorName;
    int copies;
    string issueDate;

public:
    void menu();
    void addBook();
    void showBooks();
    void removeBook();
    void modifyBook();
    void searchBook();
    void issueBook();
    void setIssueDate(const string& date);
    string getIssueDate() const;
};

void Book::menu()
{
    int input = 0;
    while (input != 6)
        {
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t***** LIBRARIAN PORTAL *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
        cout << "[1] Add Book\n";
        cout << "[2] Show Books\n";
        cout << "[3] Remove Book\n";
        cout << "[4] Issue Book\n";
        cout << "[5] Modify Book\n";
        cout << "[6] Exit\n";
        cout << "Enter Your Choice: ";
        cin >> input;
        system("cls");
        switch (input) {
            case 1:
                addBook();
                printf("\n\n\t\tPress any key to return main menu . . .\n");
                getch();
                system("cls");
                break;
            case 2:
                showBooks();
                printf("\n\n\t\tPress any key to return main menu . . .\n");
                getch();
                system("cls");
                break;
            case 3:
                removeBook();
                printf("\n\n\t\tPress any key to return main menu . . .\n");
                getch();
                system("cls");
                break;
            case 4:
                issueBook();
                printf("\n\n\t\tPress any key to return main menu . . .\n");
                getch();
                system("cls");
                break;
            case 5:
                modifyBook();
                printf("\n\n\t\tPress any key to return main menu . . .\n");
                getch();
                system("cls");
                break;
            case 6:
                exit(0);
            default:
                cout << "Please enter a valid option\n";
                break;
        }
    }
}

void Book::addBook()
{
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t***** INSERT BOOK *****\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout << "Enter The Book's ID: ";
    cin >> id;
    cout << "Enter Book's Name: ";
    cin.ignore();
    getline(cin, bookName);
    cout << "Enter Author's name: ";
    getline(cin, authorName);
    cout << "Enter Number Of Copies Of The Book: ";
    cin >> copies;

    ofstream file("Book1.txt", ios::app);
    if (file.is_open()) {
        file << id << " " << bookName << " " << authorName << " " << copies << "\n";
        file.close();
        cout << "\nBook Added Successfully\n";
    } else {
        cout << "Error: Unable to open file\n";
    }
}

void Book::showBooks()
{
    ifstream file("Book1.txt");
    if (file.is_open())
        {
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t***** AVAILABLE BOOKS *****\n";
        cout << "------------------------------------------------------------------------------------------------------------------------\n\n\n";
        string line;
        int total = 0;
        while (getline(file, line)) {
            cout << "Book no: " << ++total << endl;
            cout << line << endl;
        }
        if (total == 0) {
            cout << "No Data is present" << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to open file\n";
    }
}

void Book::removeBook()
{
    string idToRemove;
    cout << "Enter the ID of the book you want to remove: ";
    cin >> idToRemove;

    ifstream inFile("Book1.txt");
    ofstream outFile("temp1.txt");
    if (!inFile || !outFile)
    {
        cout << "Error: Unable to open file\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line))
    {
        if (line.find(idToRemove) != string::npos)
        {
            found = true;
            continue;
        }
        outFile << line << endl;
    }
    inFile.close();
    outFile.close();

    if (found) {
        remove("Book1.txt");
        rename("temp1.txt", "Book1.txt");
        cout << "Book removed successfully.\n";
    } else {
        cout << "Book with ID " << idToRemove << " not found.\n";
    }
}

void Book::modifyBook()
{
    string idToModify;
    cout << "Enter the ID of the book you want to modify: ";
    cin >> idToModify;

    ifstream inFile("Book1.txt");
    ofstream outFile("temp1.txt");
    if (!inFile || !outFile)
        {
        cout << "Error: Unable to open file\n";
        return;
        }

    string id, name, author;
    int copies;
    bool found = false;
    while (inFile >> id >> name >> author >> copies)
     {
        if (id == idToModify)
        {
            found = true;
            cout << "Enter new book name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new author name: ";
            getline(cin, author);
            cout << "Enter new number of copies: ";
            cin >> copies;
        }
        outFile << id << " " << name << " " << author << " " << copies << endl;
    }
    inFile.close();
    outFile.close();

    if (found)
    {
        remove("Book1.txt");
        rename("temp1.txt", "Book1.txt");
        cout << "Book modified successfully.\n";
    }
    else
    {
        cout << "Book with ID " << idToModify << " not found.\n";
    }
}

void Book::setIssueDate(const string& date)
{
    issueDate = date;
}

string Book::getIssueDate() const
{
    return issueDate;
}

void Book::issueBook()
{
    string idToIssue;
    cout << "Enter the ID of the book you want to issue: ";
    cin >> idToIssue;

    ifstream inFile("Book1.txt");
    ofstream outFile("temp1.txt");
    if (!inFile || !outFile)
    {
        cout << "Error: Unable to open file\n";
        return;
    }

    string id, name, author;
    int copies;
    bool found = false;
    while (inFile >> id >> name >> author >> copies) {
        if (id == idToIssue) {
            found = true;
            if (copies > 0)
                {
                cout << "Book '" << name << "' issued successfully.\n";
                cout << "Issue Date: ";
                time_t now = time(0);
                tm* currentTime = localtime(&now);
                cout << (currentTime->tm_year + 1900) << '-' << (currentTime->tm_mon + 1) << '-' << currentTime->tm_mday << endl;

                setIssueDate(to_string(currentTime->tm_year + 1900) + '-' + to_string(currentTime->tm_mon + 1) + '-' + to_string(currentTime->tm_mday));

                copies--;
            } else {

                cout << "Sorry, the book '" << name << "' is out of stock.\n";
            }
        }
        outFile << id << " " << name << " " << author << " " << copies << endl;
    }
    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Book with ID " << idToIssue << " not found.\n";
    } else {
        remove("Book1.txt");
        rename("temp1.txt", "Book1.txt");
    }
}

void Administratorbooks()
{
    Book book;
    book.showBooks();
}

void student1()
{
    string data1;
    ifstream file1("student1.txt");

    while (getline(file1, data1)) {
        cout << data1 << endl;
    }
    file1.close();
}

void library_of_student1()
{
    int choice;
    cout << endl << "\t  Access to library is granted.\n";
    cout << "1. Available Books\n2. My Library" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1:
            Administratorbooks();
            break;
        case 2:
            student1();
            break;
        default:
            cout << "Invalid choice\n";
            break;
    }
}

void student2() {
    string data2;
    ifstream file2("student2.txt");

    while (getline(file2, data2)) {
        cout << data2 << endl;
    }
    file2.close();
}

void library_of_student2() {
    int choice;
    cout << endl << "\t  Access to library is granted.\n";
    cout << "1. Available Books\n2. My Library" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1:
            Administratorbooks();
            break;
        case 2:
            student2();
            break;
        default:
            cout << "Invalid choice\n";
            break;
    }
}

void student3() {
    string data3;
    ifstream file3("student3.txt");

    while (getline(file3, data3)) {
        cout << data3 << endl;
    }
    file3.close();
}

void library_of_student3() {
    int choice;
    cout << endl << "\t Access to library is granted.\n";
    cout << "1. Available Books\n2. My Library" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;
    switch (choice) {
        case 1:
            Administratorbooks();
            break;
        case 2:
            student3();
            break;
        default:
            cout << "Invalid choice\n";
            break;
    }
}

class Student_login {
private:
    string ID;
    string password;

public:
    Student_login() // Constructor for input
    {
        cout << "Enter your ID: ";
        cin >> ID;
        cout << "Enter your password: ";
        cin >> password;
    }

    bool verifyAndGrantAccess()  // Function to verify login and grant access
    {
        for (int i = 1; i <= 3; ++i) {
            if (ID == "C23310" && password == "A1234") // student 1
            {
                library_of_student1();
                return true;
            }
            else if (ID == "C23311" && password == "B1234") // student 2
            {
                library_of_student2();
                return true;
            }
            else if (ID == "C23312" && password == "C1234") // student 3
            {
                library_of_student3();
                return true;
            }
            else if (i < 3) // if password or ID is wrong
            {
                cout << "Invalid ID or Password. Try again.\n";
                cout << endl << "Enter your ID: ";
                cin >> ID;
                cout << "Enter your password: ";
                cin >> password;
            }
        }
        cout << "Access Denied\n";
        return false;
    }
};

void administratorLogin() {
    Book obj;
    obj.menu();
}

int main() {
    int userType;
    cout << "1. Administrator\n2. Student\n";
    cout << endl << "Enter user type: ";
    cin >> userType;
    cout << endl;
    system("cls");
    switch (userType) {
        case 1:
            administratorLogin();
            break;
        case 2:
        {
            Student_login student;
            student.verifyAndGrantAccess();
            break;
        }
        default:
            cout << "Invalid user type\n";
            break;
    }

    return 0;
}


